#pragma once

#include "cocos2d.h"

class PlayerGauge : public cocos2d::ProgressTimer{
public:
	static PlayerGauge *create();
	
protected:
	virtual bool init();
	virtual void update(
		float dt);
};