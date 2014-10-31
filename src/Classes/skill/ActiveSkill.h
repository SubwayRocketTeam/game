#pragma once

#include "cocos2d.h"

#include "objects/Unit.h"
#include "Skill.h"

class ActiveSkill : public Skill{
public:
	static float duration;
	static float cooltime;
	static float cost;

public:
	virtual void use(
		Unit *u,
		cocos2d::Vec2 pos);

protected:
	virtual bool initExternalData(
		const std::string &dataPath);
};
