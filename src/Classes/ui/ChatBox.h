#pragma once

#include "cocos2d.h"

#include "objects/KeyboardEventListener.h"

class InputBox;

class ChatBox : public cocos2d::ClippingRectangleNode,
	public KeyboardEventListener{
public:
	static const int MaxLines = 5;
	static const int LineSize = 30;

public:
	static ChatBox *create();
	static ChatBox *getInstance();

	void output(
		const std::string &msg);

protected:
	ChatBox();
	virtual ~ChatBox();

	virtual bool init();

	void shift();
	void addLine(
		const std::string &msg);

	virtual void onKeyboardDown(
		cocos2d::EventKeyboard::KeyCode key);
	virtual void onKeyboardUp(
		cocos2d::EventKeyboard::KeyCode key);

	virtual void onExit();

private:
	std::list<cocos2d::LabelTTF*> lines;

	cocos2d::Sprite *bgi;
	InputBox *input;
};