#pragma once

#include "Vec2.h"
class Unit;

struct AttackData{
	AttackData(){}
	AttackData(float damage):damage(damage){}

	///# 님하.. 초기화..

	Unit* user;
	Unit* object;
	Unit* target;

	float damage;
	float aggro;

	Vec2 postion;
	float radius;
};