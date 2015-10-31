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

namespace DataManagement
{
	class DataManager
	{
	public:
		static void Publish(const std::string& type, void* data, std::size_t len);

		static void Subscribe(const std::string& type, void(void*, std::size_t));
	};
}

#endif // DATAMANAGER_H