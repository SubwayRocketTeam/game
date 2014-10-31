#pragma once

#include "cocos2d.h"

#include "Skill.h"
#include "Attribute.h"

#include <map>
#include <string>

class PassiveSkill : public Skill{
public:
	static std::map<std::string,Attribute> bonus;

protected:
	virtual bool initExternalData(
		const std::string &dataPath);
};
