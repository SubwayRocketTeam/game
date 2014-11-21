#pragma once

#include "cocos2d.h"

#include <map>

class MouseEventListener{
private:
	struct MouseData;

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

	virtual void onMousePressed(
		int btn, float x,float y);

protected:
	void processMouseTurbo(float dt);

private:
	cocos2d::Node *target;
	cocos2d::EventListenerMouse *mouseListener;
	
	std::map<int,MouseData> pressed;
};
