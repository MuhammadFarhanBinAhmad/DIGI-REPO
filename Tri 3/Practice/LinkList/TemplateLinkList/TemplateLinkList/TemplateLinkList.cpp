// TemplateLinkList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DoubleLinkList.h"


int main()
{ 

	DLL List({ 1,2,3,4,5,6 });

	DLL List2(List);

	std::cout << "Index 3 = " << List.RetriveData(3) << std::endl;
	List.ChangeData(3, 8);
	std::cout << "Index 3 = " << List.RetriveData(3) << std::endl;
	List.PushFront(9);
	std::cout << "PushFront\n";
	std::cout << "Index 0 = " << List.RetriveData(0) << std::endl;
	List.RemoveFront();
	std::cout << "RemoveFront\n";
	std::cout << "Index 0 = " << List.RetriveData(0) << std::endl;
	std::cout << "Remove Index 2\n";
	std::cout << "Index 2 = " << List.RetriveData(2) << std::endl ;
	List.Remove(0);
	std::cout << "Index 0 = " << List.RetriveData(0) << std::endl;
	std::cout << "Remove Last\n";

	std::cout << "Last index =" << List.RetriveData(List.Size()-1) << std::endl;
	List.RemoveLast();
	std::cout << "Last index =" << List.RetriveData(List.Size()-1) << std::endl;

	std::cout << "Index 1 = " << List.RetriveData(1) << std::endl;
	List.Add(9, 1);
	std::cout << "Index 1 = " << List.RetriveData(1) << std::endl;

	List.Clear();
	List2.Clear();

	//   MY BEST FRIEND AND WORST ENEMY :)
//Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
}

