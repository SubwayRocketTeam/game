#pragma once

#include "cocos2d.h"

#include "skill/Attribute.h"
#include "skill/AttributeName.h"

// Enemy Info .json �ۼ��Ѱ͵� ����ִ� ����
struct EnemyInfo {
	std::string name;
	std::map<std::string, Attribute> attrs;
	std::vector<ActiveSkill*> skills;
};