#include "stdafx.h"
#include "Bullet.h"
#include "Stage.h"
#include "Ally.h"

#include "common/resource.h"

Bullet::Bullet(){
	type = UT_BULLET;
	init();
}
Bullet::~Bullet(){
}

bool Bullet::init(){
	if (!Unit::init())
		return false;

	attackData.user = nullptr;
	attackData.target = nullptr;
	attackData.radius = 0;
	attackData.aggro = 0;
	attackData.damage = 0;
	attackData.object = this;

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

void Bullet::fire(const Vec2 &direction, float speed){
	velocity = direction.getNormalized() * speed; ///< 마찬가지로 Unit멤버 변수 이름과 인자 이름이 direction으로 같은 경우... 지양!
}

void Bullet::update(
	float dt){
	attackData.postion = position;
	stage->ally[_OPPOSITE(ally)]->processAttack(attackData);
}