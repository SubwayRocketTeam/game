#pragma once

#include "cocos2d.h"

class Unit;

enum AttackType {
	Pan,
	Line,
	Target
};

struct AttackData{
	AttackData(){}
	AttackData(
		float damage)
		:damage(damage){
	}

	Unit* user = nullptr;
	Unit* object = nullptr;
	Unit* target = nullptr;

	AttackType type = Pan;
	float damage = 0;

	cocos2d::Vec2 postion;

	float radius = 0;

	float aggro = 0;
};