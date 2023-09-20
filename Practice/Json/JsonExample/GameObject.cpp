#include "GameObject.h"

Gameobject::Gameobject()
{
	pos.x = 0;
	pos.y = 0;
	health = 0;
	name = "NULL";
}
Gameobject::Gameobject(Vec2D pos, int health, std::string name)
{
	this->pos = pos;
	this->health = health;
	this->name = name;
}

Gameobject& Gameobject::operator= (const Gameobject& GO)
{
	this->pos = GO.pos;
	this->health = GO.health;
	this->name = GO.name;

	return *this;
}
void Gameobject::SetVec2D(Vec2D pos) { this->pos = pos; }
void Gameobject::SetHealth(int health) { this->health = health; }
void Gameobject::SetName(std::string name) { this->name = name; }
std::string  Gameobject::GetName() { return this->name; }
Vec2D  Gameobject::GetVec2D() { return this->pos; }
int  Gameobject::GetHealth() { return this->health; }
