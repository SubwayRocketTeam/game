#pragma once

#include "shared/skill/PassiveSkill.h"

class Repair : public PassiveSkill{
protected:
	virtual bool update(
		Unit *user, float remaining);
};
