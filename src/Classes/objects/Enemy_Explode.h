#pragma once

#include "Enemy.h"

#include "common/max.h"

class Enemy_Explode : public Enemy{
public:
	static Enemy_Explode *create();

protected:
	Enemy_Explode();
	virtual ~Enemy_Explode();

	virtual bool init();

	virtual bool onDeath();

protected:
};
