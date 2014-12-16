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

	///# 웬만하면 초기화는 습관적으로 좀 해라
	Unit* user;
	Unit* object;
	Unit* target;

	AttackType type;
	float damage;

	cocos2d::Vec2 postion;

	float radius;

	float aggro;
};