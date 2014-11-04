#pragma once

#include "cocos2d.h"

#include "objects/MouseEventListener.h"

class Minimap : public cocos2d::Sprite,
	public MouseEventListener{
public:
	static Minimap *create();
	static Minimap *getInstance();

protected:
	virtual bool init();
	virtual void update(
		float dt);

	virtual void onMouseMove(
		int btn, float x,float y);

protected:
	cocos2d::DrawNode *drawnode;
};