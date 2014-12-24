#pragma once

#include "cocos2d.h"

#include "objects/KeyboardEventListener.h"

class UpgradeItem;

class UpgradeBar : public cocos2d::Node,
	public KeyboardEventListener{
private:
	enum SlideDirection;

public:
	static UpgradeBar *create();
	static UpgradeBar *getInstance();

	void upgradeOver();

protected:
	UpgradeBar();
	~UpgradeBar();

	virtual bool init();
	virtual void update(
		float dt);

	void slide(
		SlideDirection direction);

	virtual void onKeyboardDown(
		cocos2d::EventKeyboard::KeyCode key);
	virtual void onKeyboardUp(
		cocos2d::EventKeyboard::KeyCode key);

protected:
	std::map<int, UpgradeItem*> items;
	float itemHeight;

	float cost;
	bool upgradeTrying;

};