#pragma once

#include "cocos2d.h"

class TrashTank : public cocos2d::Sprite{
public:
	static TrashTank *create();
	static TrashTank *getInstance();

	void show();
	void hide();

	void blink(
		float cost);
	void stopBlink();

	float getCostX(
		float _cost);

protected:
	TrashTank();
	virtual ~TrashTank();

	virtual bool init();
	virtual void update(
		float dt);

private:
	cocos2d::ProgressTimer *gauge;
	cocos2d::Sprite *overlay;

	float cost;
};