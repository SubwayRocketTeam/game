#pragma once

#include "cocos2d.h"

#include "objects/MouseEventListener.h"

class Cursor : public cocos2d::CCSprite,
	public MouseEventListener{
private:
	Cursor();
	virtual ~Cursor();

	static Cursor* create();

	static Cursor* instance;
public:

	static Cursor* getInstance();
	static Cursor* getInstance(const char* filename); // image°¡ ¹Ù²ï´Ù

	void update(float dt);

protected:
	virtual bool init();
	virtual void onMouseMove(
		int btn, float x,float y);
};