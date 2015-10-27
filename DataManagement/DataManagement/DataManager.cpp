// Project: Data Management
// File: DataManager.cpp
// Contributors: Iniyavan Sathiamurthi, Jason Watkins, Kelly Ho, Kyle Lam
// Created: 10/27/2015
// Last Modified: 10/27/2015

#include <map>
#include <vector>

#include "DataManager.h"

namespace DataManagement
{
	// map to store key/vector pairs
	static std::map < const std::string&, std::vector<void(void*, std::size_t)> > subscribers;

	// publish called by components with new data
	static void Publish(const std::string& type, void* data, std::size_t len)
	{
		std::pair < const std::string&, std::vector<void(void*, std::size_t)> > tempPair;
		std::vector < void(void*, std::size_t) > tempVect;
		tempVect.push_back(void(*, len));
		tempPair = std::make_pair(type, )
		std::vector<void<void*, std::size_t>>
		subscribers.insert((type, ));
		// TODO needs lots of work
	}

	// subscribe called by components who want certain data
	static void Subscribe(const std::string& type, void(void*, std::size_t))
	{

	}
}