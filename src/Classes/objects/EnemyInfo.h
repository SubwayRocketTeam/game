#pragma once

#include "cocos2d.h"

#include "skill/Attribute.h"
#include "skill/AttributeName.h"

// Enemy Info .json 작성한것들 집어넣는 뼈대
struct EnemyInfo {
	std::string name;
	std::map<std::string, Attribute> attrs;
	std::vector<ActiveSkill*> skills;
	int cost;
	float cooltime;
};