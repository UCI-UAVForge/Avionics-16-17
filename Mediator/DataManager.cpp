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

#include <map>
#include <vector>

#include "DataManager.h"

// map to store key/vector pairs
static std::map<String, std::vector<DataManager::DataCallback>> subscribers;

// publish called by components with new data
void DataManager::Publish(const String& key, void* data, std::size_t len)
{
	// Note: This will create an empty vector if there are no subscribers yet.
	//   This would be wasteful if no one ever subscribed, but there should be
	//   few if any cases where we are publishing data that no one ever
	//   subscribes to.
	std::vector<DataCallback>& value = subscribers[key];
	for (auto it = value.begin(), end = value.end(); it != end; ++it)
	{
		(*it)(data, len);
	}
}

// subscribe called by components who want certain data
void DataManager::Subscribe(const String& key, DataCallback callback)
{
	// Note: The map accessor will automatically create and empty vector if
	//   the key does not exist, so we don't need to create the vector
	//   explicitly.
	subscribers[key].push_back(callback);
}