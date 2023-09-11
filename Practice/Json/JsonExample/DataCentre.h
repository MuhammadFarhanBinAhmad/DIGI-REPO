#pragma once

#include <iostream>

#include "GameObject.h"
#include "DataCentre.h"

class DataCentre
{
public:
	void SetDefaultGameObjectData(Gameobject& GO);
	void GrabDefaultGameObjectData();
private:
	Gameobject defaultGameObject;

};
