#include "pch.h"
#include "Bullet.h"
#include "PartedBody.h"

#include "common/resource.h"
#include "common/PhysicsFactory.h"

using namespace cocos2d;

Bullet::Bullet(){
}
Bullet::~Bullet(){
}

Bullet *Bullet::create(){
	Bullet *e = new Bullet();

	if(e && e->init()){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return nullptr;
}
bool Bullet::init(){
	if (!Unit::init(R::Bullet))
		return false;

	setScale(0.1);

	return true;
}
bool Bullet::initPhysics(){
	auto factory = PhysicsFactory::getInstance();
	auto pbody = factory->make("bullet");

	if(pbody){
		return true;
	}

	return false;
}

void Bullet::fire(
	float x,float y, float speed){
	
	auto pos = getPosition();
	auto deltaNorm =
		(Vec2(x,y) - pos).getNormalized();

	runAction(
		Sequence::create(
			MoveBy::create(1, deltaNorm * 800),
			RemoveSelf::create(),
			nullptr));
}