#pragma once

#include "json/json.h"

#include <string>

class SkillPool;

class Skill{
	friend SkillPool;
public:
	const static int Infinite = 0;

public:
	int id;
	std::string tooltip;
	std::string name;
	float duration;

protected:
	virtual bool init(
		const std::string &dataPath);
	virtual bool initExternalData(
		const std::string &dataPath);

protected:
	Json::Value json;
};
