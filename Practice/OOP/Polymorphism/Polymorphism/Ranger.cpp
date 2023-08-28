#include "Ranger.h"

void Ranger::SetStats()
{
	Name = "Aragorn";
	Role = "Ranger";
	strength = 8;
	wisdom = 15;
	intelligence = 10;
	charisma = 8;
	agility = 15;
}
void Ranger::SetSkills()
{
	Skills.push_back("Natural Explorer");
	Skills.push_back("Blind Fighting");
	Skills.push_back("Dueling");
	Skills.push_back("Primeval Awareness");
	Skills.push_back("LandÅfs Stride");
}