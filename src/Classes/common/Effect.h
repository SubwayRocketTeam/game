#pragma once

#include "cocos2d.h"

#include <string>

class Effect : public cocos2d::Sprite{
public:
	static Effect *create(
		const std::string &name,
		bool repeat = false);

protected:
	Effect();
	virtual ~Effect();

	virtual bool init(
		const std::string &name,
		bool repeat);
	virtual bool initAction(
		const std::string &name,
		bool repeat);

private:
	cocos2d::Action *action;
};