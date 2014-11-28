#pragma once

#include "cocos2d.h"

class Attribute : public cocos2d::Ref{
public:
	Attribute();
	Attribute(
		float bonusValue, float bonusRate);
	virtual ~Attribute();

	/* value와 maxValue를 한번에 설정 */
	void set(
		float value);

	float increase(
		float plus);
	float upgrade(
		float plus);

	float get();

	float &getMaxValue();
	float &getValue();
	float &getBonusRate();
	float &getBonusValue();

private:
	float value, maxValue;
	float bonusValue, bonusRate;
};