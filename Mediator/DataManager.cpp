// Project: Data Management
// File: DataManager.cpp
// Contributors: Iniyavan Sathiamurthi, Jason Watkins, Kelly Ho, Kyle Lam
// Created: 10/27/2015
// Last Modified: 11/14/2015

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