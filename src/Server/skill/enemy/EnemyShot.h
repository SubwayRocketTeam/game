#pragma once

#include "shared/skill/ActiveSkill.h"

class EnemyShot : public ActiveSkill{
public:
	virtual void use(
		Unit *u,
		Vec2 pos);
};
