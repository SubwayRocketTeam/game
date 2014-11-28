#pragma once

#include "cocos2d.h"

#include "MouseEventListener.h"
#include "KeyboardEventListener.h"

class CollisionDetector;

class Stage : public cocos2d::Node,
	public MouseEventListener{
public:
	static bool create();
	static Stage *getInstance(
		int id);

	CollisionDetector* getCollisionDetector();

protected:
	virtual bool init();
	virtual bool initExternalData();
	virtual bool initObject(
		const std::string &name,
		int x,int y);
	virtual void update(
		float dt);

	virtual void onMouseMove(
		int btn, float x,float y);

protected:
	Stage();
	virtual ~Stage();

protected:
	int id;

	cocos2d::Sprite *floor;
	cocos2d::Vec2 mousePos;
	CollisionDetector *collisionDetector;
};
