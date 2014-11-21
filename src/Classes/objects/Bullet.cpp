#include "pch.h"
#include "Bullet.h"

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

	attackData.user = nullptr;
	attackData.target = nullptr;
	attackData.radius = 0;
	attackData.type = AttackType::Pan;
	attackData.aggro = 0;

	attackData.postion = getPosition();
	attackData.damage = attackData.user->getAttribute(Attr::attack).get();

	scheduleUpdate();

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

void Bullet::update(float dt){
	attackData.postion = getPosition();
	attackData.damage = attackData.user->getAttribute(Attr::attack).get();
	Ally::getInstance(_OPPOSITE(attackData.user->getAllyID()))->processAttack(attackData);
}

void Bullet::setUser(
	Unit* user){

	attackData.user = user;
}
Unit* Bullet::getUser(){
	return attackData.user;
}

void Bullet::setRadius(
	float radius){

	attackData.radius = radius;
}
float Bullet::getRadius(){
	return attackData.radius;
}
