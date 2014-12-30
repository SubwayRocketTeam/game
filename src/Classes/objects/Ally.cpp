#include "pch.h"
#include "Ally.h"
#include "Unit.h"
#include "AttackData.h"

using namespace cocos2d;

Ally* Ally::create(){
	auto e = new Ally();

	if(e && e->init()){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return e;

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

	for (auto it = members.begin(); it != members.end();){
		auto member = *it;
		auto memberPosition = member->getPosition();
		float r = member->radius + data.radius;
		Vec2 delta = memberPosition - data.position;

		if(data.position.getDistance(memberPosition) <= r){
			if (data.user != object)
				object->damage(AttackData(1));
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