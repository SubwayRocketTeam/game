#pragma once

#include "cocos2d.h"

#include "json/json.h"

#include <string>

class SkillPool;

class Skill : public cocos2d::Ref{
	friend SkillPool;
public:
	int id;
	std::string tooltip;
	std::string name;

protected:
	virtual bool init(
		const std::string &dataPath);
	virtual bool initExternalData(
		const std::string &dataPath);

protected:
	Json::Value json;
};
