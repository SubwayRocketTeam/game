#include "pch.h"
#include "Bullet.h"

#include "EffectFactory.h"

#include "common/resource.h"
#include "common/PhysicsFactory.h"

using namespace cocos2d;

Bullet::Bullet():fired(false), range(100){
}
Bullet::~Bullet(){
}

Bullet *Bullet::create(
	int id){

	Bullet *e = new Bullet();

	if(e && e->init(id)){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return nullptr;
}
bool Bullet::init(
	int id){

	/* TODO : id에 따른 총알 데이터 변경 */
	if (!Unit::init(
		_MAKE_PATH("bullet%d", id)))
		return false;

	attackData.user = nullptr;
	attackData.target = nullptr;
	attackData.radius = 0;
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
	return true;
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


/* TODO : 두개 하나로 합치기 */
void Bullet::fire(
	float x,float y, float speed){
	
	auto pos = getPosition();
	fire(Vec2(x, y) - pos, speed);
}
void Bullet::fire(
	const Vec2 &direction, float speed){
	auto norm = direction.getNormalized();
	fireStart = getPosition();
	fired = true;
	setRotation(-CC_RADIANS_TO_DEGREES(norm.getAngle()));
	velocity = norm * speed;
	/*
	runAction(
		Sequence::create(
			MoveBy::create(1, norm * 800),
			RemoveSelf::create(),
			nullptr));
	*/
}

void Bullet::update(
	float dt){

	if (fired && getPosition().getDistance(fireStart) >= range)
		remove();
	else
	{
		attackData.position = getPosition();

		Ally::getInstance(_OPPOSITE(allyID))
			->processAttack(attackData);
	}
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
void Bullet::setRange(
	float range_) {
	range = range_;
}
float Bullet::getRange() {
	return range;
}

void Bullet::setAllyID(
	Ally::Type id)
{
	allyID = id;
}
