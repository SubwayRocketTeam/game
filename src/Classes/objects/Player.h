#pragma once

#include "cocos2d.h"

#include <map>
#include <string>

#include "Unit.h"
#include "MouseEventListener.h"
#include "KeyboardEventListener.h"

class PassiveSkill;
class ActiveSkill;
class Cursor;
class Gauge;
class UserResources;

class Player : public Unit,
	public MouseEventListener, public KeyboardEventListener{
public:
	enum SKillIndex{
		skillMouseLeft =0,
		skillMouseRight,
		skillKeyboardQ,
		skillKeyboardW,
		skillKeyboardE,
		skillKeyboardR,
	};

public:
	static Player *create(
		const std::string &dataPath);
	static Player *getInstance();

	virtual bool useSkill(
		SKillIndex id,
		float x,float y);

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

	void processRotation(
		float x,float y);
	void processEyeline(
		float x,float y);
	void processMove(
		cocos2d::EventKeyboard::KeyCode keycode);
	void processAttack(
		int btn, float x,float y);

	virtual void onKeyboardDown(
		cocos2d::EventKeyboard::KeyCode keycode);
	virtual void onKeyboardUp(
		cocos2d::EventKeyboard::KeyCode keycode);
	virtual void onKeyboardPressed(
		cocos2d::EventKeyboard::KeyCode keycode);

	virtual void onMouseMove(
		int btn, float x,float y);
	virtual void onMouseDown(
		int btn, float x,float y);
	virtual void onMouseUp(
		int btn, float x,float y);

	virtual void onMousePressed(
		int btn, float x,float y);

protected:
	Player();
	virtual ~Player();

protected:
	std::vector<ActiveSkill*> skills;

	int moveCounter;
	int moveSwitchVertical;
	int moveSwitchHorizontal;

	float immortal;
	float stiff;
	float speedFactor;
	std::vector<float> cooltimes;

	cocos2d::DrawNode *lay;
	cocos2d::Vec2 cursor;

	Gauge* hp;
	Gauge* mp;

	Cursor* mouseCursor;

	// 현재 경험치
	int exp;
	// 레벨업 기준 경험치
	int expLimit;
	int level;
};
