#pragma once

#include "cocos2d.h"

#include <set>

#include "skill/Attribute.h"
#include "skill/AttributeName.h"
#include "objects/AttackData.h"
#include "objects/Ally.h"

#define _ATTR(name) (attrs[Attr::##name].get())
#define _ATTR_VALUE(name) (attrs[Attr::##name].getValue())
#define _ATTR_MAX(name) (attrs[Attr::##name].getMax())
#define _INIT_ATTR(name, value) (attrs[Attr::##name].set(value))

class Gauge;
class PartedBody;
class PassiveSkill;

class Unit : public cocos2d::Sprite{
public:
	static const int BodyParts = 6;

	enum ActionType{
		actionMove,
		actionAttack,
		actionFocus,
	};
	enum CollisionChannel{
		channelPlayer = 0x0000000F,
		channelBullet = 0x000000F0,
		channelEnemy = 0x00000F00,
	};

public:
	static Unit *create();
	static Unit *create(
		const std::string &image);
	static Unit *create(
		const std::string &image, const int part);

	static Unit *getInstanceByID(
		int id);

	// return true if die
	bool damage(
		const AttackData& attackData);

	virtual bool useSkill(
		int id,
		float x,float y);

	void addPassive(
		int id);
	void removePassive(
		int id);

	void enableDebug();

	void setID(
		int id);
	int getID();
	PartedBody *getBody();
	Attribute &getAttribute(
		const std::string &name);
	Ally::Type getAllyID();

protected:
	Unit();
	virtual ~Unit();

	virtual bool init();
	virtual bool init(
		const std::string &imageName, const int part = 0);

	virtual bool initAttrs();
	virtual bool initPhysics();

	/* post-damage */
	virtual void onDamage(
		const AttackData &attackData);
	/* pre-death */
	virtual bool onDeath();

	virtual void updateGauge(float dt);

	void updateDebug(
		float dt);

protected:
	int id;
	Ally::Type allyID;

	PartedBody *body;
	cocos2d::Sprite* weapon;
	Gauge* gauge;

	std::set<PassiveSkill*> passives;
	std::map<std::string,Attribute> attrs;

	cocos2d::LabelTTF *dbgAngle;
};
