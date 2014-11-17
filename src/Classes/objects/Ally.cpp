#include "pch.h"
#include "Ally.h"

#include "Unit.h"

#include "common/World.h"

using namespace cocos2d;

static Ally *instances[2] =
	{nullptr, nullptr};

bool Ally::create(){
	for(int i=0;i<_countof(instances);i++){
		instances[i] = new Ally();

		if(instances[i] && instances[i]->init()){
		}
		else{
			CC_SAFE_DELETE(instances[i]);
			return false;
		}
	}

	return true;
}
Ally *Ally::getInstance(
	Type type){

	switch(type){
	case allyPlayer:
		return instances[allyPlayer];
	case allyEnemy:
		return instances[allyEnemy];
	default:
		cocos2d::log("invalid ally type");
		return nullptr;
	}
}

bool Ally::init(){
	
	return true;
}

void Ally::push(
	Unit *u){

	members.pushBack(u);
}
void Ally::remove(
	Unit *u){
	
	members.eraseObject(u);
}

void Ally::processAttack(
	Unit *u,
	AttackData& data){

	auto senderPosition = u->getPosition();
	Vec2 attackDirection = data.targetPostion - data.startPostion;

	/* TODO : 공격 타입에 따른 분기 */
	for (auto it = members.begin(); it != members.end();){
		auto& member = *it;
		auto memberPosition = member->getPosition();

		// fixture list를 돌면서 마지막 shape를 가져옴. 이거그냥 맨처음 fixture로 써도 될듯
		float r;
		b2Fixture* fixture = member->getPhysicsBody()->GetFixtureList();
		while (fixture != nullptr) {
			switch (fixture->GetType()) {
			case b2Shape::e_circle:
				b2CircleShape* circle = (b2CircleShape*)fixture->GetShape();
				r = circle->m_radius * PTM_RATIO + data.radius;
				break;
			}
			fixture = fixture->GetNext();
		}

		Vec2 delta = memberPosition - data.startPostion;
		float angle = CC_RADIANS_TO_DEGREES(attackDirection.getAngle(delta));

		if(senderPosition.getDistance(memberPosition) <= r && abs(angle) <= data.halfAngle){
			if (member->damage(data)){
				World::getInstance()->destroy(member);
				it = members.erase(it);
				continue;
			}
		}
		++it;
	}
}

Vector<Unit*>::iterator Ally::begin(){
	return members.begin();
}
Vector<Unit*>::iterator Ally::end(){
	return members.end();
}