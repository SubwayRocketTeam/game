#pragma once

#include "cocos2d.h"

class Unit;

enum AttackType {
	PAN,
	LINE,
	TARGET
};

struct AttackData{
	Unit* user;
	Unit* target;

	AttackType type;
	float damage;

	cocos2d::Vec2 startPostion;
	cocos2d::Vec2 targetPostion;

	float radius;
	float halfAngle;
};