#pragma once

#include "cocos2d.h"

class Unit;

enum AttackType {
	Pan,
	Line,
	Target
};

struct AttackData{
	AttackData() :
		user(nullptr), object(nullptr), target(nullptr),
		type(AttackType::Pan),
		damage(0), radius(0.0f), aggro(0.0f)
	{
	}
	AttackData(
		float damage)
		:damage(damage){
	}

	Unit* user;
	Unit* object;
	Unit* target;

	AttackType type;
	float damage;

	cocos2d::Vec2 postion;

	float radius;

	float aggro;
};