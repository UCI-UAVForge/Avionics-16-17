#ifndef MEDIATOR_NETWORK_H
#define MEDIATOR_NETWORK_H

#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

namespace Network
{
	void ProcessNext();

	size_t Receive(uint8_t buffer[], size_t len, IPAddress* source, uint16_t* port);

	void Send(const uint8_t buffer[], size_t len, IPAddress& dest, uint16_t port);

	void Setup();
}

#endif

