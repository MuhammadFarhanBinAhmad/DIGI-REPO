#pragma once
#include "Class.h"

class Wizard: public Class
{
public:
	void SetStats() override;
	void SetSkills() override;
};
