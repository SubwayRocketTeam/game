#pragma once

#include "cocos2d.h"
#include "skill/Attribute.h"

#define _ATTR(name) (attrs[Attr::##name].get())

class PartedBody;

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

	void damage(
		int dmg);

	void enableDebug();

	PartedBody *getBody();

protected:
	Unit();
	virtual ~Unit();

	virtual bool init();
	virtual bool init(
		const std::string &image);
	virtual bool init(
		const std::string &prefix, const int part);

	virtual bool initPhysics();
	void updateDebug(
		float dt);

protected:
	PartedBody *body;

	cocos2d::LabelTTF *dbgAngle;

	std::map<std::string,Attribute> attrs;
};
