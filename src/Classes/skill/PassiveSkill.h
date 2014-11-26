#pragma once

#include "cocos2d.h"

#include "Skill.h"
#include "Attribute.h"

#include <map>
#include <string>

class Unit;

class PassiveSkill : public Skill{
	friend Unit;
public:
	std::map<std::string,Attribute> bonusList;
	float interval;

protected:
	virtual bool initExternalData(
		const std::string &dataPath);

	virtual bool update(
		Unit *user, float remaining);
};
