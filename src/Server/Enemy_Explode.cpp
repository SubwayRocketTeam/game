#include "stdafx.h"
#include "Enemy_Explode.h"
#include "Ally.h"

#include "shared/skill/id.h"

Enemy_Explode::Enemy_Explode()
	:Enemy(){
}
Enemy_Explode::~Enemy_Explode(){
}

bool Enemy_Explode::init(){
	if (!Enemy::init())
		return false;

	return true;
}

bool Enemy_Explode::onDeath(){
	if (!Enemy::onDeath())
		return false;
	useSkill(skillExplosion, position);
	return true;
}