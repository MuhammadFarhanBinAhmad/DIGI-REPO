// TemplateLinkList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "DoubleLinkList.h"


int main()
{ 
	std::cout << "***************************************************\n";
	std::cout << "Testing List with List \n";
	DLL<double> List({ 1.4f,4.54f,3.9f,2.12f,5.345f,6.2145f });
	DLL<double> List2(List);

	std::cout << List;
	std::cout << "ChangeData at index 3\n";
	List.ChangeData(3, 8.734);
	std::cout << List;


	std::cout << "PushFront\n";
	List.PushFront(9.245);
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
	List.Add(9.1234, 1);
	std::cout << List;
	
	std::cout << "Find Node with Value 44 = " << List.FindNode(44) << std::endl;

	std::cout << "List Size\n";
	std::cout << "List Size = " << List.Size() << '\n';

	std::cout << "Test += Operator\n";
	List += List2;

	std::cout << "Test << Operator\n";
	std::cout << List;

	std::cout << "Test [] Operator\n";
	std::cout << List2[2] << '\n';

	std::cout << "***************************************************\n";

	std::cout << "Testing List Operator\n";
	DLL<std::string> StringList1({ "cat","dog","pussy","Meow","Lol", "Jew" });
	std::cout << "Test = Operator\n";
	DLL<std::string> StringList2 = StringList1;
	DLL<std::string> StringList3({ "Long","Hes","Mess","Guess","Less", "Pest" });
	DLL<std::string> StringList4;

	std::cout << StringList2;

	std::cout << "Test += Operator\n";
	StringList4 += StringList3;
	StringList4 += StringList1;

	std::cout << StringList4;

	std::cout << "***************************************************\n";

	//Test Initializer List
	std::cout << "Testing List with Initializer List \n";

	std::initializer_list<int> IniListInt1{ 44,52,2123,65,123 };
	std::initializer_list<int> IniListInt2{ 6734,123,512,741,112 };

	DLL<int> List3(IniListInt1);
	std::cout << "Testing DLL(std::initializer_list<T>) \n";
	std::cout << List3;

	DLL<int> List4 = IniListInt2;
	std::cout << "Testing operator=(std::initializer_list<T>) \n";
	std::cout << List4;

	std::cout << "Testing operator+= \n";
	List3 += List4;
	std::cout << List3;

	std::cout << "Testing Swap \n";
	List3.Swap(List4);
	std::cout << List3;

	std::cout << "Testing Swapvalue \n";
	List3.SwapValue(0, 4);
	std::cout << List3;

	std::cout << "Testing ReverseList \n";
	List3.ReverseList();
	std::cout << List3;

	std::cout << "***************************************************\n";

	//   MY BEST FRIEND AND WORST ENEMY :)
//Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
}

