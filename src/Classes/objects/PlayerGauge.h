#pragma once

#include "cocos2d.h"

class PlayerGauge : public cocos2d::ProgressTimer{
public:
	static const float FadeDuration;

public:
	static PlayerGauge *create(
		float hp, float hpMax);
	
protected:
	PlayerGauge();
	virtual ~PlayerGauge();

	virtual bool init(
		float hp, float hpMax);
	virtual void update(
		float dt);

private:
	float hp, hpMax;
};