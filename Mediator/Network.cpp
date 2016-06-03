// Copyright (c) 2015:
// Jason Watkins <watkins1@uci.edu>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#include "Network.h"

/// The MAC address of the Arduino's ethernet adapter.
static byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x4D, 0x09 };

/// The IP address of the Arduino
static IPAddress ip(192, 168, 1, 177);

/// The port the Arduino will listen on.
static uint16_t localPort = 8888;

/// The size of the buffer used by \c ProcessNext
const size_t BUF_SIZE = 1024;

/// The buffer used by \c ProcessNext
uint8_t buffer[BUF_SIZE];

/// Instance of \c EthernetUDP used for network communication.
EthernetUDP udp;

/// Outputs some timing information to the serial port.
static void printMetrics(size_t len, uint32_t uStart, uint32_t uEnd, const String& action)
{
	Serial.print("Packet ");
	Serial.print(action);
	Serial.print(" with size: ");
	Serial.println(len);
	Serial.print("Processed in ");
	Serial.print((uEnd - uStart)/1000.0);
	Serial.println("ms.");
	Serial.println();
}

void Network::Setup()
{
	Ethernet.begin(mac, ip);
	udp.begin(localPort);

	// TODO: For some reason reading a packet always takes at least one timeout duration, even when the read succeeds
	udp.setTimeout(100);
}

void Network::Send(const uint8_t buffer[], size_t len, const IPAddress& dest, uint16_t port)
{
	uint32_t us = micros();
	udp.beginPacket(dest, port);
	udp.write(buffer, len);
	udp.endPacket();
	uint32_t ue = micros();
	printMetrics(len, us, ue, "sent");
}

size_t Network::Receive(uint8_t buffer[], size_t len, IPAddress& source, uint16_t& port)
{
	uint32_t us = micros();
	int size = udp.parsePacket();
	if (size)
	{
		size_t bytesRead = udp.readBytes(buffer, len);
		source = udp.remoteIP();
		port = udp.remotePort();
		uint32_t ue = micros();
		printMetrics(bytesRead, us, ue, "received");
		return bytesRead;
	}
	else
	{
		return 0;
	}
}

void Network::ProcessNext()
{
	uint32_t us = micros();
	IPAddress remoteIP;
	uint16_t remotePort;
	int size = Receive(buffer, BUF_SIZE, remoteIP, remotePort);
	if (size != 0)
	{
		Send(buffer, size, remoteIP, remotePort);
		uint32_t ue = micros();
		printMetrics(size, us, ue, "processed");
	}
}
