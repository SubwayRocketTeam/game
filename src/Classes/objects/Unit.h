#pragma once

#include "cocos2d.h"

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

	virtual bool init();
	virtual bool init(
		const std::string &image);
	virtual bool init(
		const std::string &prefix, const int part);

	void enableDebug();

protected:
	Unit();
	virtual ~Unit();

	virtual bool initPhysics();
	void updateDebug(
		float dt);

protected:
	PartedBody *body;

	cocos2d::LabelTTF *dbgAngle;
};
