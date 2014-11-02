#pragma once

#include "cocos2d.h"

class BodyAnimation;

class AnimationPool :public cocos2d::Ref
{
public:
	static AnimationPool* create();
	static AnimationPool* getInstance();

	bool loadFromFile(const std::string& filename);
	BodyAnimation* getBodyAnimation(const std::string& name);

private:
	bool init();

private:
	std::map<std::string, BodyAnimation*> pool;
};