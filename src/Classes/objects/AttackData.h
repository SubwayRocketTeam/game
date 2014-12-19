#pragma once

#include "cocos2d.h"

class Unit;

struct AttackData{
	AttackData() :
		user(nullptr), object(nullptr), target(nullptr),
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

	float damage;	/* 데미지 */

	cocos2d::Vec2 position; /* 공격 중심 */

	float radius;	/* 공격 범위 반지름 */

	float aggro;	/* 공격이 적중할 경우 상승시킬 어그로 수치 */
};