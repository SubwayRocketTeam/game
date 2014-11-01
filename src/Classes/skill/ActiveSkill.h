#pragma once

#include "cocos2d.h"

#include "Skill.h"

class Unit;

class ActiveSkill : public Skill{
public:
	float duration;
	float cooltime;
	float cost;

public:
	virtual void use(
		Unit *u,
		cocos2d::Vec2 pos);

protected:
	virtual bool initExternalData(
		const std::string &dataPath);
};
