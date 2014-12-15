#pragma once

#include "shared/skill/ActiveSkill.h"

class Spiral : public ActiveSkill{
public:
	virtual void use(
		Unit *u,
		Vec2 pos);
protected:
	void circleShot(
		Unit* sender,
		Unit *u,
		float angle);
};
