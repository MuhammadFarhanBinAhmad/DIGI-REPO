#include "Elevator.h"

void Elevator::MoveDown()
{
	currentfloor++;
}
void Elevator::Moveup()
{
	currentfloor--;
}
//Check all people in vector and see if they have reach their desired level
void Elevator::OpenDoors()
{
	for (Person p : peopleWaiting)
	{
		auto it = std::remove_if(peopleWaiting.begin(), peopleWaiting.end(),
			[this](const Person& p) { return currentfloor == p.DesiredFloor; });

		peopleWaiting.erase(it, peopleWaiting.end());
	}
}
