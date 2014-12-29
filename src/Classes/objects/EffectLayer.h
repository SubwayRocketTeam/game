#pragma once

#include "cocos2d.h"

class EffectLayer : public cocos2d::Layer{
public:
	static bool create();
	static EffectLayer *getInstance(
		int stage);
};