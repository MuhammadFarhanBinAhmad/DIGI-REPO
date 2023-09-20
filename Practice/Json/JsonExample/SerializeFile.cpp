

//TODO
//STREAM LINE THIS 
//In-Memory Serialization
//Think like Library of alexandria
//TLDR:Everytime a traveller come to Alexandria, they're search for books, copy book and return book 
//Should use this philosophy. No need to grab from file. Just one shot store someone in game where user can grab.
//Will need function to export edited data
#include "SerializeFile.h"

void SerializeFile(std::string file_Name,DataCentre& DC)
{
	std::ifstream json_file(file_Name);

	if (!json_file.is_open())
	{
		std::cout << "Failed to open data.json" << std::endl;
		return;
	}
	//get data from json file
	rapidjson::IStreamWrapper json_stream(json_file);
	rapidjson::Document json_Document;

	json_Document.ParseStream(json_stream);

	json_file.close();

	// Check if the parsing was successful
	if (json_Document.HasParseError()) {
		std::cerr << "Error parsing JSON: " << rapidjson::GetParseErrorFunc(json_Document.GetParseError()) << std::endl;
		return;
	}

	if (json_Document.HasMember("ID") && json_Document["ID"].IsArray())
	{
		const rapidjson::Value& ID_ = json_Document["ID"];//Grab GAMEOBJECT
		for (rapidjson::SizeType i = 0; i < ID_.Size(); i++)
		{
			const rapidjson::Value& content_ID = ID_[i];

			//SET GAMEOBJECT DEFAULT VARIABLE
			//Set one first. Then later can set multiple gameobject :)
			if (content_ID.HasMember("GAMEOBJECT") && content_ID["GAMEOBJECT"].IsArray())
			{
				const rapidjson::Value& GO_ = content_ID["GAMEOBJECT"];//Grab GAMEOBJECT
				Gameobject tempGameObject;
				std::cout << GO_.Size() << std::endl;

				for (rapidjson::SizeType i = 0; i < GO_.Size(); i++)
				{
					const rapidjson::Value& content = GO_[i];

					if (content.HasMember("Type"))
					{
						std::string type = content["Type"].GetString();
					}
					else
					{
						std::cout << "Type can't be found " << std::endl;
					}
					if (content.HasMember("Name"))
					{
						std::string name = content["Name"].GetString();
						tempGameObject.SetName(name);
					}
					else
					{
						std::cout << "Name can't be found " << std::endl;
					}
					if (content.HasMember("Health"))
					{
						int health = content["Health"].GetInt();
						tempGameObject.SetHealth(health);
					}
					else
					{
						std::cout << "Health can't be found " << std::endl;
					}
					if (content.HasMember("x") && content.HasMember("y"))
					{
						Vec2D pos;
						pos.x = content["x"].GetInt();
						pos.y = content["y"].GetInt();
						tempGameObject.SetVec2D(pos);
					}
				}
			}
		}
	}
	else
	{
		std::cout << "JSON structure is missing the 'ID' array" << std::endl;
	}
}