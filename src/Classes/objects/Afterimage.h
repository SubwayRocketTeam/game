#pragma once

#include "cocos2d.h"

class PartedBody;

class Afterimage : public cocos2d::Sprite{
public:
	static Afterimage *create(
		cocos2d::Node *world,
		cocos2d::Sprite *target, float duration);

protected:
	Afterimage();
	virtual ~Afterimage();

	virtual bool init(
		cocos2d::Node *world,
		cocos2d::Sprite *target, float duration);

	virtual void update(
		float dt);

	void addAfterimage(
		cocos2d::Sprite *target,
		cocos2d::Vec2 pos, float angle, float scale,
		int opacity);

private:
	cocos2d::Node *world;
	cocos2d::Sprite *target;
	float duration;
};
