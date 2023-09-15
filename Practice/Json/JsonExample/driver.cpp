#include <iostream>
#include "SerializeFile.h"
#include "DataCentre.h"

int main()
{
	DataCentre dataCentre;
	dataCentre.GrabTotalIDSize("ID_File.json");
	//SerializeFile("Data/data.json",dataCentre);
	//dataCentre.GrabDefaultGameObjectData();

}
