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

// Note: Arduino needs all includes at the top of the ino file as well as in
// the .h/.cpp files. This is a pain, but I don't know of any way around it.

// Data Manager Includes
#include <map>
#include <vector>

// Networking Includes
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


#include "Network.h"
#include "PacketHandler.h"

/// The IP address of the Arduino
static IPAddress localIP(192, 168, 1, 100);
/// The port the Arduino will listen on.
static uint16_t localPort = 50000;

/// The IP address of the ground station
static IPAddress remoteIP(192, 168, 1, 200);
/// The port the Arduino will send to.
static uint16_t remotePort = 60000;

void setup()
{
	Network::Setup(localIP, localPort);
	Protocol::Setup(remoteIP, remotePort);

	Serial.begin(115200);
}

void loop()
{
	Protocol::Packet* p = Protocol::ReadPacket();
	Protocol::HandlePacket(p);
	delay(5);
}