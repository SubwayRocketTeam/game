#pragma once

#include "cocos2d.h"
#include "Unit.h"

#include "EnemyType.h"

class Enemy;

class EnemySpawner : public Unit{
public:
	static EnemySpawner *create();

	void spawn(
		EnemyType type);

protected:
	EnemySpawner();
	virtual ~EnemySpawner();

	virtual bool init();
	virtual void update(
		float dt);
};
