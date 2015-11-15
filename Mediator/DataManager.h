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

	void Publish(const String& key, void* data, std::size_t len);

	void Subscribe(const String& key, DataCallback callback);
}

#endif // DATAMANAGER_H