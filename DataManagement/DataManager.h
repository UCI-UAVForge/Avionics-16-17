// Project: Data Management
// File: DataManager.h
// Contributors: Iniyavan Sathiamurthi, Jason Watkins, Kelly Ho, Kyle Lam
// Created: 10/27/2015
// Last Modified: 10/27/2015

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>

#include <iostream>
#include <stdlib.h>

//! DataManagement own namesapace.
/*!
	DataManagement has its own namespace so that the variables that 
	are declared in this namspace are not interfered with any other 
	variables names outside of the namespace. 
*/
namespace DataManagement
{
//! DataManager class.
/*!
	The DataManager class contains the publish and subscribe 
	pattern that is implemented in this class. The whole purpose
	of this class is for publishers like autopilot can send data to
	the publish class and subscribers like radio comms and ground
	station will be able to retreive that data if they are subsribed 
	to the data. 
*/
	class DataManager
	{
	public:
		/*!
			Publish method is takes in a string type which is a key,
			pointer to the data, and the size of that data. Using the 
			pointer data, Publish method looks up the key in the map 
			and passes the data to the functions pointers that are 
			subscribed. 
		*/
		static void Publish(const std::string& type, void* data, std::size_t len);
		
		/*!
			Subscribe method takes in the string type whcih is a key.
			If the key does not exist in the map then Publish mehtod
			creates the key and ignores the other paramenter. If the 
			key already exists, then the Subscribe method appends the
			funtion pointer(2nd parameter) to the value of the map which
			is an array of function pointers.
		*/
		static void Subscribe(const std::string& type, void(void*, std::size_t));
	};
}

#endif // DATAMANAGER_H