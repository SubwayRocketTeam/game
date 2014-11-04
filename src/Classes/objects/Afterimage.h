#pragma once

#include "cocos2d.h"

class PartedBody;

class Afterimage : public cocos2d::Sprite{
public:
	static Afterimage *create(
		cocos2d::Node *world,
		cocos2d::Sprite *target, float duration);
	static Afterimage *createWithPartedBody(
		cocos2d::Node *world,
		PartedBody *target, float duration);
    virtual bool init(
		cocos2d::Node *world,
		cocos2d::Sprite *target, float duration);
    virtual bool initWithPartedBody(
		cocos2d::Node *world,
		PartedBody *target, float duration);

protected:
	Afterimage();
	virtual ~Afterimage();

	void addAfterimage(
		cocos2d::Sprite *target,
		cocos2d::Vec2 pos, float angle, float scale,
		int opacity);

	virtual void update(
		float dt);

private:
	cocos2d::Node *world;
	cocos2d::Sprite *target;
	float duration;
	bool partedBody;
};
