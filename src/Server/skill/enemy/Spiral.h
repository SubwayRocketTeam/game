#pragma once

#include "shared/skill/ActiveSkill.h"

class Spiral : public ActiveSkill{
public:
	virtual void use(
		Unit *u,
		Vec2 pos);
	virtual void update(
		Unit *u,
		float dt);

protected:
	void circleShot(
		Unit *u,
		float angle);
};
