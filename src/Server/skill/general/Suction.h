#pragma once

#include "shared/skill/PassiveSkill.h"

class Suction : public PassiveSkill{
protected:
	virtual bool update(
		Unit *user, float remaining);
};
