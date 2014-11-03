#pragma once

#include "cocos2d.h"

class Unit;

class Ally : public cocos2d::Ref{
public:
	enum Type{
		allyPlayer=0,
		allyEnemy
	};

public:
	static bool create();
	static Ally *getInstance(
		Type type);

	virtual bool init();

	void push(
		Unit *u);
	void remove(
		Unit *u);

protected:
	cocos2d::Vector<Unit*> members;
};