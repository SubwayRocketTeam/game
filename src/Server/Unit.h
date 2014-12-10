#pragma once

#include "IDDispenser.h"
#include "Vec2.h"
#include "shared/skill/Attribute.h"
#include "shared/skill/AttributeName.h"

#define __ATTR(name) getAttribute(Attr::##name)
#define _ATTR(name) __ATTR(name).get()
#define _ATTR_VALUE(name) __ATTR(name).getValue()
#define _ATTR_MAX(name) __ATTR(name).getMaxValue()
#define _INIT_ATTR(name, value) attrs[Attr::##name].set(value)	 

struct AttackData;
class GameRoom;
class Stage;

enum UnitType {
	UT_NONE,

	UT_PLAYER,
	UT_ENEMY,
	UT_BULLET,
	UT_TRASH,

	UT_MAX
};

class Unit{
	struct PassiveData;

public:
	Unit();

	virtual ~Unit();

	virtual bool useSkill(int id, Vec2 dest);

	void addPassive(int id);
	void removePassive(int id);

	virtual bool init();
	virtual bool initAttrs();
	virtual bool initPhysics();

	bool damage(const AttackData& attackData);
	/* pre-damage */
	virtual bool onDamage(const AttackData& attackData);
	/* pre-death */
	virtual bool onDeath();

	// 충돌했을 때
	// delta: 충돌되어 밀어내어지는 크기와 방향
	virtual void collide(Vec2 delta, Unit* other);

	virtual void update(float dt);
	virtual void updateGen(float dt);
	virtual void updatePassives(float dt);
	virtual void updatePhysics(float dt);

	Attribute &getAttribute(
		const std::string &name);

public:
	Stage* stage;

	id_t id;
	int type;
	int ally;
	
	Vec2 position;
	Vec2 direction;

	Vec2 velocity;
	Vec2 acceleration;
	float friction;
	float radius;

	std::map<int, PassiveData> passives;
	std::map<std::string, Attribute> attrs;

};