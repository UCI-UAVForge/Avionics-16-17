// Project: Data Management
// File: DataManager.cpp
// Contributors: Iniyavan Sathiamurthi, Jason Watkins, Kelly Ho, Kyle Lam
// Created: 10/27/2015
// Last Modified: 10/31/2015

#include <map>
#include <vector>

#include "DataManager.h"

namespace DataManagement
{
	/*! map stores the key has a string and an array of function pointers*/
	static std::map < const std::string&, std::vector<void(*)(void*, std::size_t)> > subscribers;

	/*Publish method, publishes data to the subscribers*/
	static void Publish(const std::string& type, void* data, std::size_t len)
	{
		/*!
			If key is not found error messages displays to call the 
			subscribe fucnction first. 
		*/
		if (subscribers.count(type) == 0)
		{
			std::cerr << "Please run Subscriber function first before Publish";
		}

		/*!
			If key exists, then send the data to all the fucntion pointers
			that are subscribed to that key. 
		*/
		else
		{
			
			std::vector< void(*)(void*, std::size_t) > value;
			value = subscribers[type];
			
			/*! 
				Loops through all the pointers and sends the pointer
				to the data and the size to all the fucntion pointers.
			*/				
			for (int i = 0; i < value.size(); i++)
			{
				value[i](data, len); /*! Function pointer at each index of the array*/
			}
		}
	}

	/*! Subscribe method adds either an new key or function pointers*/ 
	static void Subscribe(const std::string& type, void(*ptr)(void*, std::size_t))
	{
		/*! If key does not exist then add it to the map*/
		if (subscribers.count(type) == 0)
		{
			/*! Makes a pair to be stored in the vector*/
			std::pair<const std::string&, std::vector<void(*)(void*, std::size_t)>> tempPair;
			/*! Initializes a new vector for that particualr key*/
			std::vector<void(*)(void*, std::size_t)>* emptyVect = new std::vector<void(*)(void*, std::size_t)>();
			/*! Makes a pair and stores into the tempPair*/
			tempPair = std::make_pair(type, emptyVect);
			/*! Appends it the map*/
			subscribers.insert(tempPair);
		}

		
		std::vector<void(*)(void*, std::size_t)> tempVect;
		tempVect = subscribers[type];
		tempVect.push_back(ptr);
	}
}