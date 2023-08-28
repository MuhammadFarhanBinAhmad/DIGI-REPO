// TemplateLinkList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DoubleLinkList.h"


int main()
{

	DLL List({ 1,2,3,4,5,6 });

	DLL List2(List);

	std::cout << List;
	std::cout << "ChangeData at index 4\n";
	List.ChangeData(3, 8);
	std::cout << List;


	std::cout << "PushFront\n";
	List.PushFront(9);
	std::cout << List;

	std::cout << "RemoveFront\n";
	List.RemoveFront();
	std::cout << List;

	std::cout << "Remove index 0\n";
	List.Remove(0);
	std::cout << List;

	std::cout << "RemoveLast\n";
	List.RemoveLast();
	std::cout << List;

	std::cout << "Add 9 at index 1\n";
	List.Add(9, 1);
	std::cout << List;

	std::cout << "Find Node with Value 44 = " << List.FindNode(44) << std::endl;


	List = List2;


	std::cout << List;

	std::cout << List2[2];

	//   MY BEST FRIEND AND WORST ENEMY :)
//Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
}

