#pragma once

#include "cocos2d.h"

#include <map>
#include <string>

#include "skill/Attribute.h"
#include "skill/Skill.h"

#include "Unit.h"
#include "PartedBody.h"
#include "Scarf.h"
#include "MouseEventListener.h"
#include "KeyboardEventListener.h"

class Player : public Unit,
	public MouseEventListener, public KeyboardEventListener{
public:
	static Player *create();
	static Player *getInstance();
    virtual bool init();

protected:
	virtual bool initPhysics();

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
	std::map<int,Skill*> skills;

	float speed;

	Scarf *scarf;

	cocos2d::DrawNode *lay;
	cocos2d::Vec2 cursor;
};
