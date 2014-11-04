#include "pch.h"
#include "Afterimage.h"

#include "objects/PartedBody.h"

using namespace cocos2d;

Afterimage::Afterimage() :
	target(nullptr),
	duration(0), partedBody(false){
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
Afterimage *Afterimage::createWithPartedBody(
	Node *world,
	PartedBody *target, float duration){

	Afterimage *e = new Afterimage();

	if(e && e->initWithPartedBody(world, target, duration)){
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

bool Afterimage::initWithPartedBody(
	Node *_world,
	PartedBody *_target, float _duration){

	if (!Afterimage::init(_world, _target, _duration))
        return false;

	partedBody = true;

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
			FadeOut::create(0.2),
			RemoveSelf::create(),
			nullptr
		));
}
void Afterimage::update(
	float dt){

	duration -= dt;
	if(duration <= 0.0f)
		target->removeChild(this, true);
	else if(partedBody){
		auto partedBody = (PartedBody*)target;
		auto unit = target->getParent();

		for(auto part : *partedBody){
			addAfterimage(
				part,
				unit->getPosition(),
				part->getRotation(),
				unit->getScale(),
				128);
		}
	}
	else{
		addAfterimage(
			target,
			target->getPosition(),
			target->getRotation(),
			target->getScale(),
			128);
	}
}