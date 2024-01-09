#pragma once
/*
Properties:
Current floor
Direction (up, down, or stationary)
A vector to store the requests (list of floors where passengers want to go)
Methods:
moveUp(): Move the elevator up by one floor.
moveDown(): Move the elevator down by one floor.
openDoors(): Open the elevator doors and handle passenger entry/exit.
closeDoors(): Close the elevator doors.
*/
#include <vector>
struct Person
{
	int DesiredFloor;
	bool ReachFloor;
};
class Elevator
{
public:
	void Moveup();
	void MoveDown();
	void OpenDoors();

	int currentfloor; 
	std::vector<Person> peopleWaiting;

};
