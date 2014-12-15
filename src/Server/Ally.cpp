#include "stdafx.h"
#include "Ally.h"
#include "Unit.h"
#include "AttackData.h"

void Ally::init(){
}

void Ally::push(Unit *u){
	members.push_back(u);
}

void Ally::remove(Unit *u){
	auto it = std::find(members.begin(), members.end(), u);
	if (it != members.end())
		members.erase(it);
}

void Ally::processAttack(
	const AttackData& data){

	Unit* object = data.object;

	for (auto it = members.begin(); it != members.end();){
		bool flag = true;
		auto& member = *it;
		auto memberPosition = member->position;
		float r = member->radius + data.radius;
		Vec2 delta = memberPosition - data.postion;

		if (data.postion.getDistance(memberPosition) <= r){
			if (member->damage(data)){
//				it = members.erase(it);
				flag = false;
			}
			if (data.user != object)
				object->damage(AttackData(1));
		}
		if (flag) ++it;
	}
}

std::vector<Unit*>::iterator Ally::begin(){
	return members.begin();
}
std::vector<Unit*>::iterator Ally::end(){
	return members.end();
}