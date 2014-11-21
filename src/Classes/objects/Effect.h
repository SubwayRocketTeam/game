#pragma once

#include "cocos2d.h"

#include <string>

class Effect : public cocos2d::Sprite{
public:
	static Effect *create(
		const std::string &name,
		bool repeat = false);
	static Effect *createWithAnimation(
		cocos2d::Animation *animation,
		bool repeat = false);

protected:
	Effect();
	virtual ~Effect();

	virtual bool init(
		const std::string &name,
		bool repeat);
	virtual bool initWithAnimation(
		cocos2d::Animation *animation,
		bool repeat);

	virtual cocos2d::Animation *initAnimation(
		const std::string &name);
	virtual cocos2d::Action *initAction(
		cocos2d::Animation *animation,
		bool repeat);
};