#include "stdafx.h"
#include "EnemyDup.h"
#include "Stage.h"
#include "EnemySpawner.h"

#include "shared/skill/id.h"

EnemyDup::EnemyDup()
:Enemy(){
}
EnemyDup::~EnemyDup(){
}

bool EnemyDup::init(){
	if (!Enemy::init())
		return false;

	return true;
}

bool EnemyDup::onDeath(){
	if (!Enemy::onDeath())
		return false;
	for (int i = 0; i < 4; ++i)
		stage->spawner->spawn(enemyFollow, position);
	return true;
}