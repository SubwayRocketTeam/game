#pragma once

#include "cocos2d.h"

class EffectLayer : public cocos2d::Layer{
public:
	static EffectLayer *create();
	static EffectLayer *getInstance();
};