#pragma once

#include "Enemy.h"

///# CamelCase ¾²´Ù°¡ snake_style?
class Enemy_Explode : public Enemy{
public:
	Enemy_Explode();
	virtual ~Enemy_Explode();

	virtual bool init();

	virtual bool onDeath();
};
