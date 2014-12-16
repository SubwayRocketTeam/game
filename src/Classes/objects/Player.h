#pragma once

#include "cocos2d.h"

#include <map>
#include <string>

#include "Unit.h"

class PassiveSkill;
class ActiveSkill;
class Cursor;
class Gauge;
class UserResources;

class Player : public Unit {
public:
	static Player *create(
		const std::string &dataPath);
	static Player *getInstance();

protected:
	virtual bool init(
		const std::string &dataPath);
	virtual bool initAttrs();
	virtual bool initPhysics();
	virtual bool initExternalData(
		const std::string &dataPath);

	virtual bool onDamage(const AttackData& attackData);
	virtual bool onDeath();

	virtual void update(
		float dt);
	void updateConditions(
		float dt);
	void updateRotation(
		float dt);

protected:
	Player();
	virtual ~Player();

protected:
	std::vector<ActiveSkill*> skills;

	int moveCounter;
	int moveSwitchVertical;
	int moveSwitchHorizontal;
	cocos2d::Vec2 speed;

	float immortal;
	float stiff;
	float speedFactor;
	std::vector<float> cooltimes;

	cocos2d::DrawNode *lay;
};
