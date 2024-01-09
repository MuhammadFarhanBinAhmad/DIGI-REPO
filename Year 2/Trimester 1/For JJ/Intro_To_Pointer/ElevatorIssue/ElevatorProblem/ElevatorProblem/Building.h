#pragma once
#include <vector>
#include "Building.h"
#include "Elevator.h"
/*
Properties:
Number of floors in the building
A vector to store the status of each floor (whether there are people waiting)
Methods:
requestElevator(int floor): Register a request from a floor for the elevator.
*/
class Building
{
private:
public:
	int NumberOfFloors;
	Elevator buildingElevator;
};
