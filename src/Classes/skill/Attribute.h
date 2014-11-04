#pragma once

#include "cocos2d.h"

class Attribute : public cocos2d::Ref{
public:
	Attribute();
	Attribute(
		float bonusValue, float bonusRate);
	virtual ~Attribute();

	float get();

	float &getMaxValue();
	float &getValue();
	float &getBonusRate();
	float &getBonusValue();

private:
	float value, maxValue;
	float bonusValue, bonusRate;
};