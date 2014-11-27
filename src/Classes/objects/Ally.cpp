#include "pch.h"
#include "Ally.h"
#include "Unit.h"
#include "AttackData.h"

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
	const AttackData& data){

	Unit* object = data.object;

	/* TODO : 공격 타입에 따른 분기 */
	for (auto it = members.begin(); it != members.end();){
		bool flag = true;
		auto& member = *it;
		auto memberPosition = member->getPosition();
//		float r = ((PhysicsShapeCircle*)member->getPhysicsBody()->getFirstShape())->getRadius()
//			+ data.radius;
		float r = member->radius + data.radius;
		Vec2 delta = memberPosition - data.postion;

		if(data.postion.getDistance(memberPosition) <= r){
			if (member->getAllyID() != Ally::Type::allyPlayer) {
				member->hit();
			}
			if (member->damage(data)){
				it = members.erase(it);
				flag = false;
			}
			if (data.user != object)
				object->damage(AttackData(1));
		}
		if (flag) ++it;
	}
}

Vector<Unit*>::iterator Ally::begin(){
	return members.begin();
}
Vector<Unit*>::iterator Ally::end(){
	return members.end();
}