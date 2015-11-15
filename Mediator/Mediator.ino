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