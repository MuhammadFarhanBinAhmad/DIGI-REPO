#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>


#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "GameObject.h"

class DataCentre
{
public:
	
	void GrabTotalIDSize(std::string FileName);
	void SetDefaultGameObjectData(Gameobject& GO);
	void GrabDefaultGameObjectData();
private:
	int totalFile;
	Gameobject defaultGameObject;
	std::vector<std::string> fileNameList;

};
