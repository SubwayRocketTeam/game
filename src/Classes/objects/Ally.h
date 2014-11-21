#pragma once

#include "cocos2d.h"

#include "AttackData.h"

#define _OPPOSITE(id) \
	((Ally::Type) (((int)id) ^ 1))

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

	void push(
		Unit *u);
	void remove(
		Unit *u);

	void processAttack(
		AttackData& data);

	cocos2d::Vector<Unit*>::iterator begin();
	cocos2d::Vector<Unit*>::iterator end();

protected:
	virtual bool init();

protected:
	cocos2d::Vector<Unit*> members;
};