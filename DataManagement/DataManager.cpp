// Project: Data Management
// File: DataManager.cpp
// Contributors: Iniyavan Sathiamurthi, Jason Watkins, Kelly Ho, Kyle Lam
// Created: 10/27/2015
// Last Modified: 11/14/2015

#include <map>
#include <vector>

#include "DataManager.h"

namespace DataManagement
{
	// map to store key/vector pairs
	static std::map < std::string, std::vector<void(*)(void*, std::size_t)> > subscribers;

	// publish called by components with new data
	void DataManager::Publish(std::string type, void* data, std::size_t len)
	{
		// key not found, send error message to publisher
		if (subscribers.count(type) == 0)
		{
			std::cerr << "Please run Subscriber function first before Publish";
		}

		// iterate through associated vector
		else
		{
			std::vector< void(*)(void*, std::size_t) > value;
			value = subscribers[type];

			for (int i = 0; i < value.size(); i++)
			{
				value[i](data, len);
			}
		}
	}

	// subscribe called by components who want certain data
	void DataManager::Subscribe(std::string type, void(*ptr)(void*, std::size_t))
	{
		// if key does not exist, add to map with empty vector
		if (subscribers.count(type) == 0)
		{
			std::pair<std::string, std::vector<void(*)(void*, std::size_t)>> tempPair;
			std::vector<void(*)(void*, std::size_t)> emptyVect;
			tempPair = std::make_pair(type, emptyVect);
			subscribers.insert(tempPair);
		}

		// add the pointer into the vector
		std::vector<void(*)(void*, std::size_t)>& tempVect = subscribers[type];
		tempVect.push_back(ptr);
	}
}