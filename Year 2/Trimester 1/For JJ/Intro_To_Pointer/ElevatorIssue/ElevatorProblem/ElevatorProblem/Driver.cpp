// ElevatorProblem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Elevator.h"
#include "Building.h"
#include <iostream>
int main()
{
	Elevator ElevatorOne;
	Person p_1, p_2, p_3, p_4, p_5, p_6, p_7, p_8, p_9, p_10 ;
	int totalFloor = 6;
	p_1.DesiredFloor = 2;
	p_2.DesiredFloor = 3;
	p_3.DesiredFloor = 5;
	p_4.DesiredFloor = 2;
	p_5.DesiredFloor = 2;
	p_6.DesiredFloor = 3;
	p_7.DesiredFloor = 5;
	p_8.DesiredFloor = 2;
	p_9.DesiredFloor = 5;
	p_10.DesiredFloor = 2;

	ElevatorOne.peopleWaiting.push_back(p_1);
	ElevatorOne.peopleWaiting.push_back(p_2);
	ElevatorOne.peopleWaiting.push_back(p_3);
	ElevatorOne.peopleWaiting.push_back(p_4);
	ElevatorOne.peopleWaiting.push_back(p_5);
	ElevatorOne.peopleWaiting.push_back(p_6);
	ElevatorOne.peopleWaiting.push_back(p_7);
	ElevatorOne.peopleWaiting.push_back(p_8);
	ElevatorOne.peopleWaiting.push_back(p_9);
	ElevatorOne.peopleWaiting.push_back(p_10);


	for (int i = 0; i < totalFloor; i++)
	{
		ElevatorOne.OpenDoors();
		ElevatorOne.Moveup();
		std::cout << ElevatorOne.peopleWaiting.size() << '\n';
	}

}
