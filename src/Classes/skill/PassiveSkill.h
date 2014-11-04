#pragma once

#include "cocos2d.h"

#include "Skill.h"
#include "Attribute.h"

#include <map>
#include <string>

class PassiveSkill : public Skill{
public:
	std::map<std::string,Attribute> bonusList;

protected:
	virtual bool initExternalData(
		const std::string &dataPath);
};
