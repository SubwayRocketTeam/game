#pragma once

#include "cocos2d.h"

#include <map>

class KeyboardEventListener{
protected:
	KeyboardEventListener();
	virtual ~KeyboardEventListener();

	void enableKeyboardInput(
		cocos2d::Node *target);
	void disableKeyboardInput();

	virtual void onKeyboardDown(
		cocos2d::EventKeyboard::KeyCode keycode);
	virtual void onKeyboardUp(
		cocos2d::EventKeyboard::KeyCode keycode);

	/* onKeyboardPressed
	 *   Ű�� ������ ���� ��� ȣ��Ǵ� �̺�Ʈ �ڵ鷯. */
	virtual void onKeyboardPressed(
		cocos2d::EventKeyboard::KeyCode keycode);

private:
	void processKeyTurbo(float dt);

private:
	cocos2d::Node *target;
	cocos2d::EventListenerKeyboard *keyboardListener;

	std::map<
		cocos2d::EventKeyboard::KeyCode, bool> keymap;
};
