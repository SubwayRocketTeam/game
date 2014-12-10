#include "stdafx.h"
#include "CollisionDetector.h"

#include "Unit.h"

void CollisionDetector::init(){
}

void CollisionDetector::update(float dt){

	for (auto it = unitVector.begin(); it != unitVector.end(); ++it){
		Unit* me = *it;
		Vec2 pos = me->position;
		// 다른 Unit과의 충돌
		for (auto itt = it + 1; itt != unitVector.end(); ++itt){
			Unit* other = *itt;
			Vec2 other2me = pos - other->position;
			float distance = other2me.getLength();
			float radius = me->radius + other->radius;
			if (distance < radius){
				float deltaSize = radius - distance;
				if (distance == 0)
					other2me = Vec2::UNIT_X;
				Vec2 delta = other2me.getNormalized() * deltaSize;
				me->collide(delta, other);
				other->collide(-delta, me);
			}
		}

		// 벽과의 충돌
		// TODO: 상하좌우 벽의 위치를 외부에서 가져오기.
		if (pos.x < -800)
			me->collide(Vec2(-(pos.x + 800), 0), nullptr);
		if (pos.x > 800)
			me->collide(Vec2(-(pos.x - 800), 0), nullptr);
		if (pos.y < -600)
			me->collide(Vec2(0, -(pos.y + 600)), nullptr);
		if (pos.y > 600)
			me->collide(Vec2(0, -(pos.y - 600)), nullptr);
	}
}


void CollisionDetector::addUnit(Unit* unit){
	unitVector.push_back(unit);
}

void CollisionDetector::removeUnit(Unit* unit){
	auto it = std::find(unitVector.begin(), unitVector.end(), unit);
	if (it != unitVector.end())
		unitVector.erase(it);
}


