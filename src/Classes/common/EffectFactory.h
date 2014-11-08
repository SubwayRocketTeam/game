#pragma once

#include "cocos2d.h"

#include <string>
#include <map>

class Effect;

class EffectFactory : public cocos2d::Ref{
	friend Effect;

public:
	static EffectFactory *create();
	static EffectFactory *getInstance();

	Effect *make(
		const std::string &name,
		bool repeat);

protected:
	EffectFactory();
	virtual ~EffectFactory();

	cocos2d::Animation *loadAnimation(
		const std::string &name);

protected:
	std::map<std::string,cocos2d::Animation*> cache;
};