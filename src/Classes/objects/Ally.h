#pragma once

#include "cocos2d.h"

class Unit;

class Ally : public cocos2d::Ref{
public:
	static Ally *create();
	virtual bool init();

	void push(
		Unit *u);
	void remove(
		Unit *u);

protected:
	cocos2d::Vector<Unit*> members;
};