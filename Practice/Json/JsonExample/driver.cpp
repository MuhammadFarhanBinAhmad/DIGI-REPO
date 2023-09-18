#include <iostream>
#include "SerializeFile.h"
#include "DataCentre.h"

int main()
{
	DataCentre dataCentre;
	dataCentre.SerializeData();
	//SerializeFile("Data/data.json",dataCentre);
	//dataCentre.GrabDefaultGameObjectData();
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
}
