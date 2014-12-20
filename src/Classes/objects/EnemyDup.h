#pragma once

#include "Enemy.h"

#include "common/max.h"

class EnemyDup : public Enemy{
public:
	static EnemyDup *create();

protected:
	EnemyDup();
	virtual ~EnemyDup();

	virtual bool init();

	virtual bool onDeath();

protected:
};
