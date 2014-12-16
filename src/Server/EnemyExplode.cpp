#include "stdafx.h"
#include "EnemyExplode.h"
#include "Ally.h"

#include "shared/skill/id.h"

EnemyExplode::EnemyExplode()
	:Enemy(){
}
EnemyExplode::~EnemyExplode(){
}

bool EnemyExplode::init(){
	if (!Enemy::init())
		return false;

	return true;
}

bool EnemyExplode::onDeath(){
	if (!Enemy::onDeath())
		return false;
	useSkill(skillExplosion, position);
	return true;
}