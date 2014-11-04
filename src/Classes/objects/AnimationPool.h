#pragma once

#include "cocos2d.h"

class BodyAnimation;

class AnimationPool :public cocos2d::Node
{
public:
	static AnimationPool* create();
	static AnimationPool* getInstance();

	bool loadFromFile(const std::string& filename);

	void add(BodyAnimation* const animation, const std::string& name);

	BodyAnimation* getBodyAnimation(const std::string& name);

private:
	bool init();

private:
	std::map<std::string, BodyAnimation*> pool;
};