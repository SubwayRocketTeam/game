#pragma once

#include "cocos2d.h"

#include "EnemyType.h"

class Enemy;

class EnemyFactory {
public:
	static Enemy* createEnemy(EnemyType type);
};