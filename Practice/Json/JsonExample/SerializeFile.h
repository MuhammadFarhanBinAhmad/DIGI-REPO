#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "GameObject.h"
#include "DataCentre.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

void SerializeFile(std::string file_Name,DataCentre& DC);
