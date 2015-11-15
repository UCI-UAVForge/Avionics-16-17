// Project: Data Management
// File: DataManager.h
// Contributors: Iniyavan Sathiamurthi, Jason Watkins, Kelly Ho, Kyle Lam
// Created: 10/27/2015
// Last Modified: 10/27/2015

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "Arduino.h"

namespace DataManager
{
	typedef void(*DataCallback)(void*, size_t);

	void Publish(String type, void* data, std::size_t len);

	void Subscribe(String type, DataCallback);
}

#endif // DATAMANAGER_H