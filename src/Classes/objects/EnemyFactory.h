#pragma once

#include "cocos2d.h"

class Enemy;

class EnemyFactory {
public:
	static Enemy* createEnemy(EnemyType type);
};