#include "Wizard.h"

void Wizard::SetStats()
{
	Name = "Gandalf";
	Role = "Wizard";
	strength = 8;
	wisdom = 12;
	intelligence = 15;
	charisma = 8;
	agility = 15;
}

void Wizard::SetSkills()
{
	Skills.push_back("Artificer Initiate");
	Skills.push_back("Alert");
	Skills.push_back("Fey Touched");
	Skills.push_back("Gift of the Metallic Dragon");
	Skills.push_back("Keen Mind");
}

