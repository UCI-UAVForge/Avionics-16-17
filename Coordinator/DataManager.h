// Copyright (c) 2015:
// Jason Watkins <watkins1@uci.edu>
// Iniyavan Sathiamurthi <isathiam@uci.edu>
// Kelly Ho <doankhah@uci.edu>
// Kyle Lam <kylehl1@uci.edu>
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

#ifndef COORDINATOR_DATAMANAGER_H
#define COORDINATOR_DATAMANAGER_H

#include "Arduino.h"

/// Contains functions related to Data Management System
///
/// \author Jason Watkins
/// \author Kelly Ho 
/// \author Kyle Lam 
/// \author Iniyavan Sathiamurthi 
/// \date 2015-11-16
namespace DataManager
{
	/// Defines a pointer-to-function type for call back function.
	/// Pointer of void function with arguments of a void-type pointer
	/// and the maximum number of bytes to publish.
	///
	/// \author Jason Watkins
	/// \author Kelly Ho 
	/// \author Kyle Lam 
	/// \author Iniyavan Sathiamurthi 
	/// \date 2015-11-16
	typedef void(*DataCallback)(void*, size_t);

	/// Publishes all the data to the function pointers. 
	///
	/// Publish method takes in a string type which is a key,
	///	pointer to the data, and the size of that data. Using the 
	///	pointer data, Publish method looks up the key in the map 
	///	and passes the data to the functions pointers that are 
	///	subscribed.  
	///
	/// \author Jason Watkins
	/// \author Kelly Ho 
	/// \author Kyle Lam 
	/// \author Iniyavan Sathiamurthi 
	/// \date 2015-11-16
	///
	/// \param key[in] Key to find the subscriber in the map container.
	/// \param data[in] The data that will be passed to the function pointers. 
	/// \param len[in] The size of the data pointer. 
	void Publish(const String& key, void* data, std::size_t len);

	/// Creates a new key for the subscriber if the key does not exists and adds
	/// values to the subscriber.
	///
	/// Subscribe method takes in the string type which is a key.
	///	If the key does not exist in the map then Publish method
	///	creates the key and ignores the other parameter. If the 
	///	key already exists, then the Subscribe method appends the
	///	function pointer to the value of the map which
	///	is an array of function pointers.
	///
	/// \author Jason Watkins
	/// \author Kelly Ho 
	/// \author Kyle Lam 
	/// \author Iniyavan Sathiamurthi 
	/// \date 2015-11-16
	///
	/// \param key[in] The key is the index of the subscriber where all the 
    /// subscribed function pointers will be stored. 
	/// \param callback[in] The callback is a function pointer that will be stored
	/// to the appropriate key.
	void Subscribe(const String& key, DataCallback callback);
}

#endif