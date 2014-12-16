#pragma once

#include "Enemy.h"

#include "common/max.h"

class EnemyExplode : public Enemy{
public:
	static EnemyExplode *create();

protected:
	EnemyExplode();
	virtual ~EnemyExplode();

	virtual bool init();

	virtual bool onDeath();

protected:
};
