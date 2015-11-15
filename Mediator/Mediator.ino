// Copyright (c) 2015:
// Jason Watkins <watkins1@udi.edu>
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