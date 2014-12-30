#pragma once

#include "cocos2d.h"

class DamageLabel : public cocos2d::LabelTTF{
public:
	static const int FontSize = 40;
	
public:
	static DamageLabel *create();

	void active(
		int value =0);

protected:
	DamageLabel();
	virtual ~DamageLabel();

	virtual bool init();
	virtual void update(
		float dt);

	void fadeOut(
		float dt);

protected:
	int counter;
};
