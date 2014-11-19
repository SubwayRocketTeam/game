#pragma once

#include "cocos2d.h"

#include "KeyboardEventListener.h"

class StageLayer : public cocos2d::Layer,
	public KeyboardEventListener{
public:
	static StageLayer *create();

protected:
	StageLayer();
	virtual ~StageLayer();

	virtual bool init();

	void switchStage();

	virtual void onKeyboardDown(
		cocos2d::EventKeyboard::KeyCode keycode);
	virtual void onKeyboardUp(
		cocos2d::EventKeyboard::KeyCode keycode);

private:
	int activeStageID;
};