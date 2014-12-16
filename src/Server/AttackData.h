#pragma once

#include "Vec2.h"
class Unit;

struct AttackData{
	AttackData(){}
	AttackData(float damage):damage(damage){}

	Unit* user = nullptr;
	Unit* object = nullptr;
	Unit* target = nullptr;

	float damage = 0;
	float aggro = 0;

	Vec2 postion;
	float radius = 0;
};