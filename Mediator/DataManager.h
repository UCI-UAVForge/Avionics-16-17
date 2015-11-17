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

#ifndef MEDIATOR_DATAMANAGER_H
#define MEDIATOR_DATAMANAGER_H

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
	
	/// Publishes and executes the function stored in the subcriber with passed data
	///
	/// Creates a new subcriber if there is no subcriber 
	///
	/// \author Jason Watkins
	/// \author Kelly Ho 
	/// \author Kyle Lam 
	/// \author Iniyavan Sathiamurthi 
	/// \date 2015-11-16
	///
	/// \param key[in] Key to find the subcriber
	/// \param data[in] The new data to pass to the subcriber
	/// \param len[in] The maximum number of bytes to publish
	void Publish(const String& key, void* data, std::size_t len);
	
	/// Subcribes the passed function pointer to passed key
	///
	/// \author Jason Watkins
	/// \author Kelly Ho 
	/// \author Kyle Lam 
	/// \author Iniyavan Sathiamurthi 
	/// \date 2015-11-16
	///
	/// \param key[in] Key for the subcriber
	/// \param callback[in] The function to call when the key is published
	void Subscribe(const String& key, DataCallback callback);
}

#endif