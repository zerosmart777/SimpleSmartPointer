// SimpleSmartPointer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>


class Monster
{
	int mId;
	char* pName;

public:
	Monster() : pName(0), mId(0)
	{
	}
	Monster(char* pName, int mId) : pName(pName), mId(mId)
	{
	}
	~Monster()
	{
	}

	void Display()
	{
		printf("Name = %s ID = %d \n", pName, mId);
	}
	void Shout()
	{
		printf("Slimmmmuuuuiu");
	}
};

class RC
{
private:
	int count; 

public:
	void AddRef()
	{
		count++;
	}

	int Release()
	{
		return --count;
	}
};

template < typename T > class SP
{
private:
	T*    pData;      
	RC* reference; 

public:
	SP() : pData(0), reference(0)
	{
		reference = new RC();
		reference->AddRef();
	}

	SP(T* pValue) : pData(pValue), reference(0)
	{
		reference = new RC();
		reference->AddRef();
	}

	SP(const SP<T>& sp) : pData(sp.pData), reference(sp.reference)
	{
		reference->AddRef();
	}

	~SP()
	{
		if (reference->Release() == 0)
		{
			delete pData;
			delete reference;
		}
	}

	T& operator* ()
	{
		return *pData;
	}

	T* operator-> ()
	{
		return pData;
	}

	SP<T>& operator = (const SP<T>& sp)
	{
		if (this != &sp) 
		{
			if (reference->Release() == 0)
			{
				delete pData;
				delete reference;
			}
			pData = sp.pData;
			reference = sp.reference;
			reference->AddRef();
		}
		return *this;
	}
};

int main()
{
	SP<Monster> p(new Monster((char*)"Slime", 325));
	p->Display();
	{
		SP<Monster> q = p;
		q->Display();

		SP<Monster> r;
		r = p;
		r->Display();

	}
	p->Display();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
