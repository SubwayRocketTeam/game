#include "pch.h"
#include "Ally.h"

#include "Unit.h"

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
	AttackData data){

	auto senderPosition = u->getPosition();
	for(auto member : members){
		auto memberPosition = member->getPosition();

		if(senderPosition.getDistance(memberPosition) <= 100){
			member->damage(1);
		}
	}
}

Vector<Unit*>::iterator Ally::begin(){
	return members.begin();
}
Vector<Unit*>::iterator Ally::end(){
	return members.end();
}