#pragma once

#include "shared/skill/ActiveSkill.h"

class FrontDash : public ActiveSkill{
public:
	virtual void use(
		Unit *u,
		Vec2 pos);

protected:
	virtual bool initExternalData(
		const std::string &dstPath);

protected:
	float distance;
};
