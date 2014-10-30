#pragma once

#include "Unit.h"

class Bullet : public Unit{
public:
	static Bullet *create();
	
    virtual bool init();

	void fire(
		float x,float y, float speed);

protected:
	Bullet();
	virtual ~Bullet();

	virtual bool initPhysics();
};
