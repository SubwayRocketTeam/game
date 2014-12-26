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
class Trash;

class Player : public Unit {
public:
	static Player *create(
		const std::string &dataPath);

	bool upgrade(
		const std::string& attr_name);
	void vacuume(
		Trash* trash);

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
	void updatePhysics(
		float dt);

protected:
	Player();
	virtual ~Player();

protected:
	std::map<std::string, float> maxAttrs;
	std::map<std::string, int> upgradeTimes;
	std::vector<ActiveSkill*> skills;

	std::vector<Trash*> vacuumingTrashs;

	int moveCounter; 
	int moveSwitchVertical;
	int moveSwitchHorizontal;

	cocos2d::Vec2 speed;

	float immortal;
	float stiff;
	float speedFactor;
	std::vector<float> cooltimes;

	cocos2d::Sprite *shadow;
};
