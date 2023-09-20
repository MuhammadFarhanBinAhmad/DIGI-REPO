#include "DataCentre.h"

namespace fs = std::filesystem;

void DataCentre::GrabTotalIDSize(std::string FileName)
{
	std::ifstream IDFile(FileName);

	if (!IDFile.is_open())
	{
		std::cout << "File fail to open\n";
	}

	rapidjson::IStreamWrapper doc_stream(IDFile);
	rapidjson::Document json_Document;

	json_Document.ParseStream(doc_stream);
	IDFile.close();

	if (json_Document.HasParseError())
	{
		std::cerr << "Error parsing JSON: " << rapidjson::GetParseErrorFunc(json_Document.GetParseError()) << std::endl;
	}

	if (json_Document.HasMember("ID") && json_Document["ID"].IsArray())
	{
		const rapidjson::Value& ID_ = json_Document["ID"];//Grab GAMEOBJECT
		//Grab object string
		for (size_t i = 0; i < ID_.Size(); i++)
		{
			//Grab type name and place them inside ID vector string
			if (ID_[i].IsObject() && ID_[i].HasMember("Type") && ID_[i]["Type"].IsString())
			{
				IDNameList.push_back(ID_[i]["Type"].GetString());
			}
			else
			{
				std::cerr << "Invalid structure for element " << i << " in the 'ID' array." << std::endl;
				return;
			}
		}
	}
	//TODO: Need find link to connect ID and data folder content
	//		Call the function via json file.
	std::string currentDirectory = "./Data";  // Use the current working directory

	try {
		for (const auto& entry : fs::directory_iterator(currentDirectory)) 
		{
			if (entry.is_regular_file()) 
			{
				std::cout << "File: " << entry.path().filename() << std::endl;
			}
		}
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Error accessing current directory: " << e.what() << std::endl;
	}
}
void DataCentre::SerializeData()
{
	GrabTotalIDSize("Data/ID_File.json");
	SetEnemyGameObjectData("Data/EnemyData.json");
	SetStaticGameObjectData("Data/StaticObjectData.json");
	SetWindowConfiguration("Data/WindowConfig.json");
	Test();
}


void DataCentre::SetEnemyGameObjectData(std::string FileName)
{
	std::ifstream json_file(FileName);

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
	if (json_Document.HasParseError()) 
	{
		std::cerr << "Error parsing JSON: " << rapidjson::GetParseErrorFunc(json_Document.GetParseError()) << std::endl;
		return;
	}

	if (json_Document.HasMember("ObjectStats") && json_Document["ObjectStats"].IsArray())
	{
		const rapidjson::Value& objectStatsArray = json_Document["ObjectStats"];

		// Iterate through the objects in the array
		for (size_t i = 0; i < objectStatsArray.Size(); i++) {
			const rapidjson::Value& object = objectStatsArray[i];

			// Print all members of the object
			std::cout << "Object " << i + 1 << " Members:" << std::endl;

			for (rapidjson::Value::ConstMemberIterator iter = object.MemberBegin(); iter != object.MemberEnd(); ++iter) 
			{
				std::cout << "Member Name: " << iter->name.GetString() << ", ";
				if (iter->value.IsString()) {
					std::cout << "Value(string): " << iter->value.GetString() << '\n';
					std::string name = iter->name.GetString();
					if (name.find_first_of("0123456789") != std::string::npos)
					{
						std::string name = iter->name.GetString();
						std::string numericPart = name.substr(name.find_first_of("0123456789"));
						int num = std::stoi(numericPart);
						std::cout << "num found: " << num << std::endl;
					}

				}
				else if (iter->value.IsInt()) {
					std::cout << "Value(int): " << iter->value.GetInt() << '\n';
				}
				std::cout << std::endl;
			}
		}
	}
}
void DataCentre::SetStaticGameObjectData(std::string FileName)
{
	std::ifstream json_file(FileName);

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
	if (json_Document.HasParseError())
	{
		std::cerr << "Error parsing JSON: " << rapidjson::GetParseErrorFunc(json_Document.GetParseError()) << std::endl;
		return;
	}

	if (json_Document.HasMember("ObjectStats") && json_Document["ObjectStats"].IsArray())
	{
		const rapidjson::Value& OS_ = json_Document["ObjectStats"];//Grab GAMEOBJECT

		for (size_t i = 0; i < OS_.Size(); i++)
		{
			const rapidjson::Value& content = OS_[i];
			Gameobject temp;
			if (content.HasMember("Name"))
			{
				temp.SetName(content["Name"].GetString());
			}
			if (content.HasMember("x") && content.HasMember("y"))
			{
				Vec2D pos;
				pos.x = content["x"].GetInt();
				pos.y = content["y"].GetInt();

				temp.SetVec2D(pos);
			}

			EnemyGameObject.push_back(temp);
		}
	}
}
void DataCentre::SetWindowConfiguration(std::string FileName)
{
	std::ifstream json_file(FileName);

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
	if (json_Document.HasParseError())
	{
		std::cerr << "Error parsing JSON: " << rapidjson::GetParseErrorFunc(json_Document.GetParseError()) << std::endl;
		return;
	}

	if (json_Document.HasMember("WindowWidth"))
	{
		WindowWidth = json_Document["WindowWidth"].GetInt();
	}
	if (json_Document.HasMember("WindowHeight"))
	{
		WindowHeight = json_Document["WindowHeight"].GetInt();
	}

}
void DataCentre::Test()
{
	for (int i = 0; i < EnemyGameObject.size(); i++)
	{
		std::cout << EnemyGameObject[i].GetName() << std::endl;
	}
	for (int i = 0; i < StaticGameObject.size(); i++)
	{
		std::cout << StaticGameObject[i].GetName() << std::endl;
	}
	std::cout << WindowHeight << '\n';
}
void DataCentre::GrabDefaultEnemyGameObjectData()
{
	//std::cout << this->defaultGameObject.GetName() << "\n";
	//std::cout << this->defaultGameObject.GetHealth() << "\n";
	//std::cout << GO.GetVec2D() << "\n";//set operator for this fella

}