#pragma once

#include <string>
#include "Vector2d.h"

class Gameobject
{
public:

	Gameobject();
	Gameobject(Vec2D pos,int health, std::string name);
	void SetVec2D(Vec2D pos);
	void SetHealth(int health);
	void SetName(std::string name);
	std::string GetName();
	Vec2D GetVec2D();
	int GetHealth();

	Gameobject& operator= (const Gameobject& GO);
private:

	Vec2D pos;
	int health;
	std::string name;

};
