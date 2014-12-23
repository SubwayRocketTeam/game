#pragma once

#include "cocos2d.h"

#include <map>
#include <string>

#include "Player.h"
#include "MouseEventListener.h"
#include "KeyboardEventListener.h"

class ControlablePlayer : public Player,
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
	static ControlablePlayer *create(
		const std::string &dataPath);
	static ControlablePlayer *getInstance();

	virtual bool useSkill(
		SKillIndex id,
		float x,float y);

protected:
	virtual bool init(
		const std::string &dataPath);

	void updateRotation(
		float dt);

	void processRotation(
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
	ControlablePlayer();
	virtual ~ControlablePlayer();

protected:
	cocos2d::Vec2 cursor;
};
