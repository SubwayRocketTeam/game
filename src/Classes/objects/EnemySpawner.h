#pragma once

#include "cocos2d.h"
#include "Unit.h"

class Enemy;

class EnemySpawner : public Unit{
public:
	static EnemySpawner *create();

	void spawn();

protected:
	EnemySpawner();
	virtual ~EnemySpawner();

	virtual bool init();
};
