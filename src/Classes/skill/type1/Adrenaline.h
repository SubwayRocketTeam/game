#pragma once

#include "cocos2d.h"

#include "skill/PassiveSkill.h"

class Adrenaline : public PassiveSkill{
protected:
	void update(
		Unit *user, float remaining);
};
