//NEED SET DEFAULT SET HERE
#include "DataCentre.h"

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