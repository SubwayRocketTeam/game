#include "pch.h"
#include "EffectFactory.h"

#include "Effect.h"

using namespace std;
using namespace cocos2d;

static EffectFactory *instance = nullptr;

EffectFactory::EffectFactory(){
}
EffectFactory::~EffectFactory(){
}

EffectFactory *EffectFactory::create(){
	instance = new EffectFactory();

	if(instance)
		return instance;
	CC_SAFE_DELETE(instance);
	return nullptr;
}
EffectFactory *EffectFactory::getInstance(){
	return instance;
}

Effect *EffectFactory::make(
	const string &name,
	bool repeat){

	auto pair = cache.find(name);

	if(pair == cache.end()){
		auto animation = loadAnimation(name);
		animation->retain();
		cache[name] = animation;
		pair = cache.find(name);
	}

	auto effect = Effect::createWithAnimation(
		pair->second, repeat);

	return effect;
}

Animation *EffectFactory::loadAnimation(
	const string &name){

	auto cache = SpriteFrameCache::getInstance();

	auto animation = Animation::create();
	animation->setDelayPerUnit(1.0 / Global::fps);
	
	for(int i=0;;i++){
		char path[128];
		sprintf(path, "%s_%d%d%d.png",
			name.c_str(),
			i/100, i/100%10, i%10);

		auto frame = cache->getSpriteFrameByName(path);
		if(frame == nullptr)
			break;

		animation->addSpriteFrame(frame);
	}

	return animation;
}