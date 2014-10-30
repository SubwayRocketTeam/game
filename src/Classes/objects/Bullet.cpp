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
	if (!Unit::init(R::EnemyBody))
        return false;

	body->setScale(0.1);

    return true;
}
bool Bullet::initPhysics(){
	auto factory = PhysicsFactory::getInstance();
	auto pbody = factory->make("bullet");

	if(pbody){
		setPhysicsBody(pbody);
		return true;
	}

	return false;
}

void Bullet::fire(
	float x,float y, float speed){

	auto body = getPhysicsBody();

	body->applyImpulse(Vec2(x,y) * speed);
}