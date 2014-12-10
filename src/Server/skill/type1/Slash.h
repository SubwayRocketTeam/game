#pragma once

#include <string>

#include "shared/skill/ActiveSkill.h"

class Slash : public ActiveSkill{
public:
	virtual void use(
		Unit *u,
		Vec2 pos);
};
