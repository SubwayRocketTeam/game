#pragma once

#include "cocos2d.h"
#include "Unit.h"

#include "EnemyType.h"

class Enemy;

class EnemySpawner : public cocos2d::Node{
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
