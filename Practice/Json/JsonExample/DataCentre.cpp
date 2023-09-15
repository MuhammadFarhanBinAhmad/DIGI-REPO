//NEED SET DEFAULT SET HERE
#include "DataCentre.h"

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

	if (json_Document.HasMember("GAMEOBJECT") && json_Document["GAMEOBJECT"].IsArray())
	{
		const rapidjson::Value& ID_ = json_Document["GAMEOBJECT"];//Grab GAMEOBJECT
		std::cout <<  ID_.Size();
	}



}
void DataCentre::SetDefaultGameObjectData(Gameobject& GO)
{
	defaultGameObject = GO;
}
void DataCentre::GrabDefaultGameObjectData()
{
	std::cout << this->defaultGameObject.GetName() << "\n";
	std::cout << this->defaultGameObject.GetHealth() << "\n";
	//std::cout << GO.GetVec2D() << "\n";//set operator for this fella

}