#pragma once

#include "Unit.h"
#include "AttackData.h"
#include "Vec2.h"

class Bullet : public Unit{
public:
	Bullet();
	virtual ~Bullet();

	virtual bool init();
	virtual bool initAttrs();
	virtual bool initPhysics();

	void fire(const Vec2 &direction, float speed);

	virtual void update(float dt);

public:
	AttackData attackData;

};
