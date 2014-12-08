#pragma once

#include "cocos2d.h"
#include "skill/ActiveSkill.h"

class Explosion : public ActiveSkill{
public:
	virtual void use(
		Unit *u,
		cocos2d::Vec2 pos);
protected:
	void circleShot(
		cocos2d::Ref* sender,
		Unit *u,
		float angle);
};
