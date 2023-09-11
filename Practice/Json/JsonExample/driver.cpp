#include <iostream>
#include "SerializeFile.h"
#include "DataCentre.h"

int main()
{
	DataCentre dataCentre;
	SerializeFile("data.json",dataCentre);
	dataCentre.GrabDefaultGameObjectData();

}
