#include "stdafx.h"
#include "Ally.h"
#include "Unit.h"
#include "Stage.h"
#include "GameRoom.h"
#include "AttackData.h"
#include "PacketType.h"

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

	for (auto it = members.begin(); it != members.end(); ++it){
//		bool flag = true;
		auto member = *it;
		auto memberPosition = member->position;
		float r = member->radius + data.radius;
		Vec2 delta = memberPosition - data.position;

		if (data.position.getDistance(memberPosition) <= r){
			member->damage(data);
			if (data.user != object)
				object->damage(AttackData(1));

			Attack noti;
			noti.attacker_id = data.user->id;
			noti.target_id = member->id;
			noti.attack_position_x = data.position.x;
			noti.attack_position_y = data.position.y;
			noti.damage = data.damage;
			noti.aggro = data.aggro;
			member->stage->gameroom->sendPacket(noti);
		}
//		if (flag) ++it;
	}
}

std::vector<Unit*>::iterator Ally::begin(){
	return members.begin();
}
std::vector<Unit*>::iterator Ally::end(){
	return members.end();
}