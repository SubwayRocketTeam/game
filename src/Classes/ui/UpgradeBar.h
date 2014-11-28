#pragma once

#include "cocos2d.h"

#include "objects/KeyboardEventListener.h"

class UpgradeBar : public cocos2d::Sprite,
	public KeyboardEventListener{
private:
	enum SlideDirection;

public:
	static UpgradeBar *create();
	static UpgradeBar *getInstance();

protected:
	virtual bool init();
	virtual void update(
		float dt);

	void slide(
		SlideDirection direction);

	virtual void onKeyboardDown(
		cocos2d::EventKeyboard::KeyCode key);
	virtual void onKeyboardUp(
		cocos2d::EventKeyboard::KeyCode key);
};