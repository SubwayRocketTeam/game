#pragma once

#include "cocos2d.h"

#include <string>
#include <map>

#include "Skill.h"

class SkillPool : public cocos2d::Ref{
public:
	static SkillPool *create();
	static SkillPool *getInstance();

	Skill *get(
		int id);

protected:
	virtual bool init();
	virtual bool initSkill(
		int id, const std::string &dataPath);
	virtual void release();

protected:
	std::map<int, Skill*> skills;
};
