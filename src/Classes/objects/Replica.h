#pragma once

#include "cocos2d.h"

#include "ControlablePlayer.h"

class Replica : public ControlablePlayer{
public:
	static Replica *create();

protected:
	virtual bool init();

	virtual void onKeyboardDown(
		cocos2d::EventKeyboard::KeyCode keycode);
	virtual void onKeyboardUp(
		cocos2d::EventKeyboard::KeyCode keycode);
	virtual void onKeyboardPressed(
		cocos2d::EventKeyboard::KeyCode keycode);

	virtual void onMouseMove(
		int btn, float x,float y);
	virtual void onMousePressed(
		int btn, float x,float y);

protected:
	Replica();
	virtual ~Replica();
};
