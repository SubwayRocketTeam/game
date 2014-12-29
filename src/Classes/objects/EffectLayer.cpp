#include "pch.h"
#include "EffectLayer.h"

static EffectLayer *instance[2] = {nullptr, };

bool EffectLayer::create(){
	for (int i = 0; i < 2; ++i) {
		instance[i] = new EffectLayer();

		if(instance[i] && instance[i]->init()){
			instance[i]->autorelease();
			continue;
		}
		CC_SAFE_DELETE(instance[i]);
		return false;
	}
	return true;
}
EffectLayer *EffectLayer::getInstance(
	int stage){
	return instance[stage];
}