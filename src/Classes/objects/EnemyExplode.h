#pragma once

#include "Enemy.h"

#include "common/max.h"

class EnemyExplode : public Enemy{
public:
	static EnemyExplode *create(
		int stage);

protected:
	EnemyExplode();
	virtual ~EnemyExplode();

	virtual bool init(
		int stage);

	virtual bool onDeath();

protected:
};
