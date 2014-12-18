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

	Unit* user;		/* 공격자 */
	Unit* object;	/* 공격 오브젝트 (총알) */
	Unit* target;	/* 타게팅 공격일경우 타겟 오브젝트 */

	AttackType type;	/* 공격 타입 */
	float damage;

	cocos2d::Vec2 postion;

	float radius;	/* 공격 범위 반지름 */

	float aggro;	/* 공격이 적중할 경우 상승시킬 어그로 수치 */
};