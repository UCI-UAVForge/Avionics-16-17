#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include "Network.h"

void setup()
{
	Network::Setup();

	Serial.begin(115200);
}

void loop()
{
	Network::ProcessNext();
	delay(5);
}