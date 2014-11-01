#pragma once

#include "cocos2d.h"

#include "skill/ActiveSkill.h"

class Slash : public ActiveSkill{
public:
	virtual void use(
		Unit *u,
		cocos2d::Vec2 pos);
};
