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
void DataManager::Publish(String type, void* data, std::size_t len)
{
	// key not found, send error message to publisher
	if (subscribers.count(type) == 0)
	{
		return;
	}

	// iterate through associated vector
	else
	{
		std::vector<DataCallback> value;
		value = subscribers[type];

		for (int i = 0; i < value.size(); i++)
		{
			value[i](data, len);
		}
	}
}

// subscribe called by components who want certain data
void DataManager::Subscribe(String type, DataCallback ptr)
{
	// if key does not exist, add to map with empty vector
	if (subscribers.count(type) == 0)
	{
		std::pair<String, std::vector<DataCallback>> tempPair;
		std::vector<DataCallback> emptyVect;
		tempPair = std::make_pair(type, emptyVect);
		subscribers.insert(tempPair);
	}

	// add the pointer into the vector
	std::vector<DataCallback>& tempVect = subscribers[type];
	tempVect.push_back(ptr);
}