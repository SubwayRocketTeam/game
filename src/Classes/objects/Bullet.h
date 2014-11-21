#pragma once

#include "Unit.h"

class Bullet : public Unit{
public:
	static Bullet *create();
	
	virtual bool init();

	void fire(
		float x,float y, float speed);
	void update(
		float dt);

	void setUser(
		Unit* user);
	Unit* getUser();

	void setRadius(
		float radius);
	float getRadius();

	void setDamage(
		float damage);
	float getDamage();

	void setAllyID(
		Ally::Type id);


protected:
	Bullet();
	virtual ~Bullet();

	virtual bool initPhysics();

protected:
	AttackData attackData;
	
};
