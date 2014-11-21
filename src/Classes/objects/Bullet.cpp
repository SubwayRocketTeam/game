#include "pch.h"
#include "Bullet.h"

#include "EffectFactory.h"

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

	attackData.user = nullptr;
	attackData.target = nullptr;
	attackData.radius = 0;
	attackData.type = AttackType::Pan;
	attackData.aggro = 0;
	attackData.damage = 0;
	attackData.object = this;

	scheduleUpdate();

	return true;
}
bool Bullet::initAttrs(){
	if (!Unit::initAttrs())
		return false;

	_INIT_ATTR(hp, 1);
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

bool Bullet::onDamage(
	const AttackData& attack){

	auto factory = EffectFactory::getInstance();
	auto worldPos = 
		getParent()->convertToWorldSpace(getPosition());

	factory->add(
		worldPos, R::Hit1, false);

	return true;
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
	Ally::getInstance(_OPPOSITE(allyID))->processAttack(attackData);
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
void Bullet::setDamage(
	float damage){

	attackData.damage = damage;
}
float Bullet::getDamage(){
	return attackData.damage;
}
void Bullet::setAllyID(
	Ally::Type id)
{
	allyID = id;
}
