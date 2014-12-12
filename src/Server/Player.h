#pragma once

#include "Unit.h"
#include "Vec2.h"

class PassiveSkill;
class ActiveSkill;
class Cursor;
class Gauge;
class UserResources;

class Player : public Unit{
public:
	enum SKillIndex{
		skillMouseLeft = 0,
		skillMouseRight,
		skillKeyboardQ,
		skillKeyboardW,
		skillKeyboardE,
		skillKeyboardR,
	};

public:
	Player();
	virtual ~Player();

	virtual bool init(
		const std::string &dataPath);
	virtual bool initAttrs();
	virtual bool initPhysics();
	virtual bool initExternalData(
		const std::string &dataPath);

	virtual void update(float dt);
	virtual void updatePhysics(float dt);
	void updateConditions(float dt);

	virtual bool onDamage(const AttackData& attackData);
	virtual bool onDeath();

	virtual bool useSkill(
		SKillIndex id,
		float x, float y);

	bool isTankFull() const;
	int getTrash() const;
	void addTrash(const int amount);

public:
	Vec2 moveDirection;

protected:
	std::vector<ActiveSkill*> skills;
	std::vector<float> cooltimes;

	float immortal;
	float stiff;
	float speedFactor;

	int trash;
};
