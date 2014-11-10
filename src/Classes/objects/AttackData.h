#pragma once

#include "cocos2d.h"

class Unit;

enum AttackType {
	PAN,
	LINE,
};

struct AttackData{
	Unit* user;
	AttackType type;
	float damage;

	cocos2d::Vec2 startPostion;
	cocos2d::Vec2 targetPostion;

	float radius;
	float halfAngle;
};