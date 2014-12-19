#include "stdafx.h"
#include "Bullet.h"
#include "Stage.h"
#include "Ally.h"

#include "common/resource.h"

Bullet::Bullet()
	:fired(false){
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

void Bullet::fire(const Vec2 &dir, float speed){
	fireStart = position;
	velocity = dir.getNormalized() * speed;
	fired = true;
}

void Bullet::update(
	float dt){
	Unit::update(dt);
	attackData.position = position;
	stage->ally[_OPPOSITE(ally)]->processAttack(attackData);
	// TODO: 최대 발사 거리 따로 빼기
	if (fired && position.getDistance(fireStart) >= 800)
		stage->removeUnit(this);
}