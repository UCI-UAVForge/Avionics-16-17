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

#ifndef COORDINATOR_NETWORK_H
#define COORDINATOR_NETWORK_H

#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

/// Contains functions related to ground station communications.
///
/// \author Jason Watkins
/// \date 2015-11-14
namespace Network
{
	/// Reads and processes the next incoming packet from the ground station.
	///
	/// \author Jason Watkins
	/// \date 2015-11-14
	void ProcessNext();

	/// Trys to read a packet from the network link.
	///
	/// Trys to read a packet from the network link, storing the source
	/// endpoint if a packet is read.
	///
	/// \author Jason Watkins
	/// \date 2015-11-14
	///
	/// \param buffer[out] Any array in which the packet will be stored.
	/// \param len[in]     The maximun number of bytes to write to \p buffer.
	/// \param source[out] If a packet is read, the source ip will be stored here.
	/// \param port[out]   If a packet is read, the source port will be stored here.
	/// \returns           The number of bytes copied into \p buffer.
	size_t Receive(uint8_t buffer[], size_t len, IPAddress& source, uint16_t& port);

	/// Sends a packet over the network link to the specified endpoint.
	///
	/// \author Jason Watkins
	/// \date 2015-11-14
	///
	/// \param buffer[in] An array containing the data to send.
	/// \param len[in]    The number of bytes to send from \p buffer.
	/// \param source[in] The destination IP address.
	/// \param port[in]   The destination port.
	void Send(const uint8_t buffer[], size_t len, const IPAddress& dest, uint16_t port);

	/// Performs initial actions required to initialize the network link.
	///
	/// \author Jason Watkins
	/// \date 2015-11-14
	void Setup();
}

#endif

