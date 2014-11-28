#include "pch.h"
#include "EffectLayer.h"

static EffectLayer *instance = nullptr;

EffectLayer *EffectLayer::create(){
	instance = new EffectLayer();

	if(instance && instance->init()){
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return nullptr;
}
EffectLayer *EffectLayer::getInstance(){
	return instance;
}