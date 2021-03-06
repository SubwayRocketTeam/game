﻿#pragma once

#include "cocos2d.h"

#include "objects/MouseEventListener.h"

class Cursor : public cocos2d::Sprite,
	public MouseEventListener{
public:
	enum Type{
		cursorNormal,
		cursorPressed
	};

public:
	static Cursor* create();
	static Cursor* getInstance();

private:
	Cursor();
	virtual ~Cursor();

protected:
	virtual bool init();
	virtual void update(
		float dt);

	virtual void onMouseMove(
		int btn, float x,float y);

	void processRotation(
		float x,float y);

private:
	cocos2d::Vec2 mouse;
};