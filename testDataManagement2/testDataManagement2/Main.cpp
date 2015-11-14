// Project: Data Management
// File: Main.cpp
// Contributors: Iniyavan Sathiamurthi, Jason Watkins, Kelly Ho, Kyle Lam
// Created: 10/31/2015
// Last Modified: 11/14/2015

#include "DataManager.h"

namespace DataManagement
{
	void testPublish(int num);
	void testSubscribe();
	void print(void* i, size_t len);

	void testPublish(int num)
	{
		DataManager::Publish("a", (void*)num, 0);
	}

	void testSubscribe()
	{
		DataManager::Subscribe("a", &print);
	}

	void print(void* i, size_t len)
	{
		std::cout << i << std::endl;
	}
}

int main()
{
	DataManagement::testSubscribe();
	
	for (int i = 0; i < 10; i++)
	{
		DataManagement::testPublish(i);
	}
	int x;
	std::cin >> x;
	return 0;
}