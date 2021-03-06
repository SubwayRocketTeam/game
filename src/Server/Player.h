﻿#pragma once

#include "Unit.h"
#include "Vec2.h"

class PassiveSkill;
class ActiveSkill;
class Cursor;
class Gauge;
class UserResources;

class Player : public Unit{
public:
	Player();
	virtual ~Player();

	virtual bool init(
		const int player_type);
	virtual bool initAttrs();
	virtual bool initPhysics();
	virtual bool initExternalData(
		const int player_type);

	virtual void update(float dt);
	void updateConditions(float dt);

	bool upgrade(
		const std::string& attr_name);

	virtual bool onDamage(const AttackData& attackData);
	virtual bool onDeath();

	bool isTankFull() const;
	int getTrash() const;
	void addTrash(const int amount);

	int getPlayerType();

public:
	Vec2 moveDirection;

protected:
	int playerType;

	std::map<std::string, float> maxAttrs;
	std::map<std::string, int> upgradeTimes;
	std::vector<ActiveSkill*> skills;
	std::vector<float> cooltimes;

	float immortal;
	float stiff;

	int trash;
	int upgradeCost;
};
