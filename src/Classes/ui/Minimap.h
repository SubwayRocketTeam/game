#pragma once

#include "cocos2d.h"

class Minimap : public cocos2d::Sprite{
public:
	static Minimap *create();
	static Minimap *getInstance();

protected:
	virtual bool init();
	virtual void update(
		float dt);

protected:
	cocos2d::DrawNode *drawnode;
};