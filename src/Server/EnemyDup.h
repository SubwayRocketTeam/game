#pragma once

#include "Enemy.h"

class EnemyDup : public Enemy{
public:
	EnemyDup();
	virtual ~EnemyDup();

	virtual bool init();
	virtual bool onDeath();

protected:
};
