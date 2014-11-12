#pragma once

#include "cocos2d.h"

#include <string>

#include "skill/ActiveSkill.h"

class Snake : public ActiveSkill{
public:
	virtual void use(
		Unit *u,
		cocos2d::Vec2 pos);
};
