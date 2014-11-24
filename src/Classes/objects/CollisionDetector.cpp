#include "pch.h"
#include "CollisionDetector.h"

#include "Unit.h"

USING_NS_CC;

CollisionDetector* CollisionDetector::create(){
	auto o = new CollisionDetector();
	if (o && o->init())
	{
		o->autorelease();
		return o;
	}
	CC_SAFE_DELETE(o);
	return nullptr;
}


bool CollisionDetector::init(){
	if (!Node::init())
		return false;

	scheduleUpdate();

	return true;
}

void CollisionDetector::update(
	float dt){

	for (auto it = unitVector.begin(); it != unitVector.end(); ++it){
		Unit* me = *it;
		Vec2 pos = me->getPosition();
		// 다른 Unit과의 충돌
		for (auto itt = ++it; itt != unitVector.end(); ++itt){
			Unit* other = *itt;
			Vec2 other2me = pos - other->getPosition();
			float distance = other2me.getLength();
			float radius = me->radius + other->radius;
			if (distance < radius){
				Vec2 delta = other2me.getNormalized() * (radius - distance);
				me->collide(delta);
				other->collide(-delta);
			}
		}

		// 벽과의 충돌
		// TODO: 상하좌우 벽의 위치를 외부에서 가져오기.
		if (pos.x < -800)
			me->collide(Vec2(-(pos.x + 800), 0));
		if (pos.x < 800)
			me->collide(Vec2(-(pos.x - 800), 0));
		if (pos.y < -600)
			me->collide(Vec2(0, -(pos.y + 600)));
		if (pos.y < 600)
			me->collide(Vec2(0, -(pos.y - 600)));
	}
}


void CollisionDetector::addUnit(
	Unit* unit){
	unitVector.pushBack(unit);
}

void CollisionDetector::removeUnit(
	Unit* unit){
	unitVector.eraseObject(unit, true);
}


