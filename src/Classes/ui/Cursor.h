#pragma once

#include "cocos2d.h"

class Cursor : public cocos2d::CCSprite {
private:
	Cursor();
	virtual ~Cursor();

	static Cursor* create();

	static Cursor* instance;
public:

	static Cursor* getInstance();
	static Cursor* getInstance(const char* filename); // image�� �ٲ��

	void update(float dt);
};