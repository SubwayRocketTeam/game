#pragma once

#include "cocos2d.h"

#include "json/json.h"

#include <string>

class Skill : public cocos2d::Ref{
public:
	static int id;
	static std::string tooltip;
	static std::string name;

protected:
	virtual bool init(
		const std::string &dataPath);
	virtual bool initExternalData(
		const std::string &dataPath);

protected:
	Json::Value json;
};
