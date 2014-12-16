#pragma once

#include "Enemy.h"

///# CamelCase ¾²´Ù°¡ snake_style?
class EnemyExplode : public Enemy{
public:
	EnemyExplode();
	virtual ~EnemyExplode();

	virtual bool init();

	virtual bool onDeath();
};
