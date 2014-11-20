#pragma once

#include "cocos2d.h"

class AnimationPool :public cocos2d::Node
{
public:
	static AnimationPool* create();
	static AnimationPool* getInstance();

	bool loadFromFile(const std::string& filename);

	void add(cocos2d::Animation* const animation, const std::string& name);

	cocos2d::Animation* getAnimation(const std::string& name);

private:
	bool init();

private:
	std::map<std::string, cocos2d::Animation*> pool;
};