#include "pch.h"
#include "Effect.h"

using namespace std;
using namespace cocos2d;

Effect::Effect(){
}
Effect::~Effect(){
}

Effect *Effect::create(
	const string &name,
	bool repeat){

	Effect *e = new Effect();

	if(e && e->init(name, repeat)){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return e;
}
bool Effect::init(
	const string &name,
	bool repeat){

	if(!Sprite::init())
		return false;
	if(!initAction(name, repeat))
		return false;

	if(!repeat){
		runAction(
			Sequence::create(
				(FiniteTimeAction*)action,
				RemoveSelf::create()));
	}
	else
		runAction(action);

	return true;
}
bool Effect::initAction(
	const string &name,
	bool repeat){

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

	action = Animate::create(animation);
	if(repeat)
		action = RepeatForever::create((ActionInterval*)action);

	return true;
}