// Project: Data Management
// File: Main.cpp
// Contributors: Iniyavan Sathiamurthi, Jason Watkins, Kelly Ho, Kyle Lam
// Created: 10/31/2015
// Last Modified: 10/31/2015

#include "DataManager.h"

namespace DataManagement
{
	void testPublish(int* num);
	void testSubscribe();
	void print(void* i, size_t len);
	// trying different fixes for LNK1561 error
	// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
	int main()
	{
		testSubscribe();
		int testNum = 1;
		int* num = &testNum;
		for (int i = 0; i < 10; i++)
		{
			testPublish(num);
		}
		return 0;
	}

	void testPublish(int* num)
	{
		DataManager::Publish("a", num, 0);
	}

	void testSubscribe()
	{
		DataManager::Subscribe("a", &print);
	}

	void print(void* i, size_t len)
	{
		std::cout << i;
	}
}