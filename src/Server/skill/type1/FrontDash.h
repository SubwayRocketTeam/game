#pragma once

#include "shared/skill/ActiveSkill.h"

class FrontDash : public ActiveSkill{
public:
	virtual void use(
		Unit *u,
		Vec2 pos);
	virtual void update(
		Unit* u,
		float dt);

protected:
	virtual bool initExternalData(
		const std::string &dstPath);

protected:
	float distance;
};
