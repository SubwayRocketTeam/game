#pragma once

#include "cocos2d.h"

#include <map>

#include "common/IterLock.h"

#include "skill/Attribute.h"
#include "skill/AttributeName.h"
#include "objects/AttackData.h"
#include "objects/Ally.h"

#define __ATTR(name) getAttribute(Attr::##name)
#define _ATTR(name) __ATTR(name).get()
#define _ATTR_VALUE(name) __ATTR(name).getValue()
#define _ATTR_MAX(name) __ATTR(name).getMaxValue()
#define _INIT_ATTR(name, value) attrs[Attr::##name].set(value)	 

class Gauge;
class PartedBody;
class PassiveSkill;
class DamageLabel;

class Unit : public cocos2d::Sprite{
public:
	struct PassiveData;

public:
	static Unit *create();
	static Unit *create(
		const std::string &image);
	static Unit *create(
		const std::string &image, const int part);

	static Unit *getInstanceByID(
		int id);

	void blink();

	// return true if die
	bool damage(
		const AttackData& attackData);

	virtual bool useSkill(
		int id,
		cocos2d::Vec2 pos);

	void remove();

	void addPassive(
		int id);
	void removePassive(
		int id);

	void setID(
		int id);
	int getID();
	void setStageID(
		int id);
	int getStageID();

	Attribute &getAttribute(
		const std::string &name);
	void setAllyID(
		Ally::Type id);
	Ally::Type getAllyID();

	// 충돌했을 때
	// delta: 충돌되어 밀어내어지는 크기와 방향
	virtual void collide(
		cocos2d::Vec2 delta,
		Unit* other);

public:
	cocos2d::Vec2 velocity;
	cocos2d::Vec2 acceleration;
	float friction;
	float radius;

protected:
	Unit();
	virtual ~Unit();

	virtual bool init();
	virtual bool init(
		const std::string &imageName, const int part = 0);

	virtual bool initAttrs();
	virtual bool initPhysics();

	virtual void onExit();

	/* pre-damage */
	virtual bool onDamage(
		const AttackData &attackData);
	/* pre-death */
	virtual bool onDeath();
	
	virtual void updateGen(
		float dt);
	virtual void updatePassives(
		float dt);
	void updatePhysics(
		float dt);

protected:
	int id;
	int stageID;
	Ally::Type allyID;

	Gauge* gauge;
	DamageLabel *damageLabel;

	IterLock passivesLock;
	std::map<int, PassiveData> passives;
	std::map<std::string,Attribute> attrs;

	float tick;
};
