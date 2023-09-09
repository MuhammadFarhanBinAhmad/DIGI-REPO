#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"


int main()
{
	std::ifstream json_file("data.json");

	if (!json_file.is_open())
	{
		std::cout << "Failed to open data.json" << std::endl;
		return 0;
	}

    //std::string json_str((std::istreambuf_iterator<char>(json_file)), std::istreambuf_iterator<char>());

	//get data from json file
	rapidjson::IStreamWrapper json_stream(json_file);
	rapidjson::Document json_Document;

	json_Document.ParseStream(json_stream);

	json_file.close();

	// Check if the parsing was successful
	if (json_Document.HasParseError()) {
		std::cerr << "Error parsing JSON: " << rapidjson::GetParseErrorFunc(json_Document.GetParseError()) << std::endl;
		return 1;
	}
	//if (json_Document.HasMember("OBJECTID") && json_Document["OBJECTID"].IsArray())
	//{

	//}
	if (json_Document.HasMember("GAMEOBJECT") && json_Document["GAMEOBJECT"].IsArray())
	{
		const rapidjson::Value& GO_ = json_Document["GAMEOBJECT"];//Grab GAMEOBJECT

		for (rapidjson::SizeType i = 0; i < GO_.Size(); i++)
		{
			const rapidjson::Value& content = GO_[i];

			if (content.HasMember("Type"))
			{
				std::string type = content["Type"].GetString();
				std::cout << "Type: " << type << std::endl;
			}
			else
			{
				std::cout << "Type can't be found "<< std::endl;
			}
			if (content.HasMember("Name"))
			{
				std::string name = content["Name"].GetString();
				std::cout << "Name: " << name << std::endl;
			}
			else
			{
				std::cout << "Name can't be found " << std::endl;
			}
			if (content.HasMember("Health"))
			{
				int health = content["Health"].GetInt();
				std::cout << "Health: " << health << std::endl;
			}
			else
			{
				std::cout << "Health can't be found " << std::endl;
			}
		}
	}
	else
	{
		std::cout << "JSON structure is missing the 'GAMEOBJECT' array" << std::endl;
	}

}