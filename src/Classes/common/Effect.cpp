#include "pch.h"
#include "Effect.h"

#include "EffectFactory.h"

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
Effect *Effect::createWithAnimation(
	Animation *animation,
	bool repeat){

	Effect *e = new Effect();

	if(e && e->initWithAnimation(animation, repeat)){
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

	auto animation = initAnimation(name);
	auto action = initAction(animation, repeat);

	runAction(action);

	scheduleUpdate();

	return true;
}
bool Effect::initWithAnimation(
	Animation *animation,
	bool repeat){

	if(!Sprite::init())
		return false;
	
	auto action = initAction(animation, repeat);

	runAction(action);

	scheduleUpdate();

	return true;
}
Animation *Effect::initAnimation(
	const string &name){

	auto factory = EffectFactory::getInstance();

	return factory->loadAnimation(name);
}
Action *Effect::initAction(
	cocos2d::Animation *animation,
	bool repeat){

	Action *action = Animate::create(animation);
	if(repeat)
		action = RepeatForever::create((ActionInterval*)action);
	else{
		action = Sequence::create(
			(FiniteTimeAction*)action,
			RemoveSelf::create(),
			nullptr);
	}

	return action;
}

void Effect::update(
	float dt){
	
	ccBlendFunc add;
	add.src = GL_SRC_ALPHA;
	add.dst = GL_ONE;
	setBlendFunc(add);
}