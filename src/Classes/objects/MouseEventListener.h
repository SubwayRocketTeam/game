#pragma once

#include "cocos2d.h"

class MouseEventListener{
protected:
	MouseEventListener();
	virtual ~MouseEventListener();

	void enableMouseInput(
		cocos2d::Node *target);
	void disableMouseInput();

	virtual void onMouseMove(
		int btn, float x,float y);
	virtual void onMouseDown(
		int btn, float x,float y);
	virtual void onMouseUp(
		int btn, float x,float y);

private:
	cocos2d::Node *target;
	cocos2d::EventListenerMouse *mouseListener;
};
