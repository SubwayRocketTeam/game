#pragma once

#include "Unit.h"

class Bullet : public Unit{
public:
	static Bullet *create(
		int id =1);

	void fire(
		float x,float y, float speed);
	void fire(
		const cocos2d::Vec2 &direction, float speed);

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

	void setRange(
		float range_);
	float getRange();

	void setAllyID(
		Ally::Type id);


protected:
	Bullet();
	virtual ~Bullet();

	virtual bool init(
		int id);
	virtual bool initAttrs();
	virtual bool initPhysics();

	virtual bool onDamage(
		const AttackData& attack);

protected:
	AttackData attackData;
	bool fired;
	cocos2d::Vec2 fireStart;
	float range;
};
