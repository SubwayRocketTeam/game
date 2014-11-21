#include "pch.h"
#include "Afterimage.h"

using namespace cocos2d;

Afterimage::Afterimage() :
	target(nullptr),
	duration(0){
}
Afterimage::~Afterimage(){
}

Afterimage *Afterimage::create(
	Node *world,
	Sprite *target, float duration){

	Afterimage *e = new Afterimage();

	if(e && e->init(world, target, duration)){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return nullptr;
}

bool Afterimage::init(
	Node *_world,
	Sprite *_target, float _duration){

	if (!Sprite::init())
		return false;

	world = _world;
	target = _target;
	duration = _duration;

	scheduleUpdate();

	return true;
}

void Afterimage::addAfterimage(
	Sprite *target,
	Vec2 pos, float angle, float scale, int opacity){

	Sprite *afterimage =
		Sprite::createWithSpriteFrame(target->getSpriteFrame());

	afterimage->setPosition(pos);
	afterimage->setRotation(angle);
	afterimage->setScale(scale);
	afterimage->setOpacity(opacity);

	world->addChild(afterimage);

	afterimage->runAction(
		Sequence::create(
			FadeOut::create(0.2f),
			RemoveSelf::create(),
			nullptr
		));
}
void Afterimage::update(
	float dt){

	duration -= dt;
	if (duration <= 0.0f)
	{
		target->removeChild(this, true);
		return;
	}

	addAfterimage(
		target,
		target->getPosition(),
		target->getRotation(),
		target->getScale(),
		128);
}