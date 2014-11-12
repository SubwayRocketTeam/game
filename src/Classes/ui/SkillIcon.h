#pragma once

#include "cocos2d.h"

class SkillIcon : public cocos2d::Sprite{
public:
	static SkillIcon *create(
		int id);

	void use();

protected:
	virtual bool init(
		int id);

	virtual void update(
		float dt);

private:
	int id;
	cocos2d::ProgressTimer *overlay;
};