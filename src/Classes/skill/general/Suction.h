#pragma once

#include "cocos2d.h"

#include "skill/PassiveSkill.h"

class Unit;

class Suction : public PassiveSkill{
protected:
	virtual void update(
		Unit *user, float remaining);
};
