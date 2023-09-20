#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>


#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "GameObject.h"

class DataCentre
{
public:
	
	void GrabTotalIDSize(std::string FileName);

	//Need find way to sorta combine all into 1 function. Probelm is just different data type
	//Use union to make main game object
	void SetEnemyGameObjectData(std::string FileName);
	void SetStaticGameObjectData(std::string FileName);
	void SetWindowConfiguration(std::string FileName);

	void GrabDefaultEnemyGameObjectData();


	void Test();
	void SerializeData();
private:
	int totalFile;
	std::vector<Gameobject> EnemyGameObject;
	std::vector<Gameobject> StaticGameObject;
	int WindowHeight,WindowWidth;
	std::vector<std::string> IDNameList;

};
