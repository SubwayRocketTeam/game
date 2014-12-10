#pragma once

#include "IDDispenser.h"
#include "Vec2.h"
#include "Attribute.h"

struct AttackData;
class GameRoom;

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
	Unit(const id_t id, const int type, GameRoom* gameroom);

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

	// ������ ��
	virtual void hit();
	// �浹���� ��
	// delta: �浹�Ǿ� �о������ ũ��� ����
	virtual void collide(Vec2 delta, Unit* other);

	void update(float dt);
	virtual void updateGen(float dt);
	virtual void updatePassives(float dt);
	void updatePhysics(float dt);

public:
	GameRoom* gameRoom;

	id_t id;
	int type;
	
	Vec2 position;
	Vec2 direction;

	Vec2 velocity;
	Vec2 acceleration;
	float friction;
	float radius;

	std::map<int, PassiveData> passives;
	std::map<std::string, Attribute> attrs;

};