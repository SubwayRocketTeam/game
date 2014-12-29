#pragma once

#include "Enemy.h"

#include "common/max.h"

class EnemyDup : public Enemy{
public:
	static EnemyDup *create(
		int stage);

protected:
	EnemyDup();
	virtual ~EnemyDup();

	virtual bool init(
		int stage);

	virtual bool onDeath();

protected:
};
