#pragma once

#include "cocos2d.h"

#include <map>
#include <string>

#include "skill/Attribute.h"

#include "Unit.h"
#include "PartedBody.h"
#include "Scarf.h"
#include "MouseEventListener.h"
#include "KeyboardEventListener.h"

class PassiveSkill;
class ActiveSkill;
class Cursor;

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
    virtual bool init(
		const std::string &dataPath);

protected:
	virtual bool initPhysics();
	virtual bool initExternalData(
		const std::string &dataPath);

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

protected:
	Player();
	virtual ~Player();

protected:
	std::map<std::string,Attribute> attrs;
	std::vector<ActiveSkill*> skills;
	std::vector<PassiveSkill*> passives;

	float speed;

	Scarf *scarf;

	cocos2d::DrawNode *lay;
	cocos2d::Vec2 cursor;

	Cursor* mouseCursor;
};
