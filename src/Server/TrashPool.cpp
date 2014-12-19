#include "stdafx.h"
#include "TrashPool.h"
#include "Trash.h"
#include "Player.h"

#include "Stage.h"
#include "GameRoom.h"
#include "Ally.h"

#include "PacketType.h"

TrashPool::TrashPool(Stage* const stage)
	:stage(stage){
}
TrashPool::~TrashPool(){
}

void TrashPool::init(){
}

void TrashPool::push(Trash *trash){
	_ASSERT(trash->type == UT_TRASH);
	trashes.push_back(trash);
}
void TrashPool::remove(Trash *trash){
	auto it = std::find(trashes.begin(), trashes.end(), trash);
	if (it != trashes.end())
		trashes.erase(it);
}

void TrashPool::spawn(int count){
	for (int i = 0; i < count; ++i){
		auto trash = new Trash();
		trash->position =
			Vec2(rand() % 1600 - 800.f, rand() % 1200 - 600.f);
		stage->addUnit(trash);

		push(trash);

		SpawnUnit noti;
		noti.id = trash->id;
		noti.stage = stage->id;
		noti.unit_type = UNIT_TRASH;
		noti.x = trash->position.x;
		noti.y = trash->position.y;
		stage->gameroom->sendPacket(noti);
	}
}
void TrashPool::spawn(const Vec2 &pos, int count){

	for (int i = 0; i < count; ++i){
		auto trash = new Trash();
		trash->position = pos;
		trash->velocity = Vec2::UNIT_X.getRotated(
			Vec2::ZERO,
			DEGREES_TO_RADIANS(rand() % 360))
			* (float)(20 + rand() % 20) * 60.0f;

		/* ISSUE : friction도 * 60? */
		trash->friction = 128 * 60;
		stage->addUnit(trash);

		push(trash);

		SpawnUnit noti;
		noti.id = trash->id;
		noti.stage = stage->id;
		noti.unit_type = UNIT_TRASH;
		noti.x = trash->position.x;
		noti.y = trash->position.y;
		stage->gameroom->sendPacket(noti);

		SetPhysics physics_noti;
		physics_noti.id = trash->id;
		physics_noti.velocity_x = trash->velocity.x;
		physics_noti.velocity_y = trash->velocity.y;
		physics_noti.friction = trash->friction;
		stage->gameroom->sendPacket(physics_noti);
	}
}

void TrashPool::update(float dt){

	auto players = stage->ally[Ally::Type::allyPlayer];

	for (auto trash : trashes){
		if (trash->removed)
			continue;

		auto pos = trash->position;

		for (auto unit : *players){
			Player* player = (Player*)unit;
			auto playerPos = player->position;

			if (player->isTankFull())
				continue;

			if (pos.getDistance(playerPos) <= player->_ATTR(range)){

				// 범위 안에 들어오면 바로 쓰레기 획득.
				player->addTrash(1);
				trash->stage->removeUnit(trash);

				Vacuum noti;
				noti.unit_id = player->id;
				noti.trash_id = trash->id;
				player->stage->gameroom->sendPacket(noti);

				/*
				auto move =
					(playerPos - pos).getNormalized() *
					trash->_ATTR(speed);

				trash->position += move * dt;
				*/
			}
		}
	}
}

std::vector<Trash*> TrashPool::query(float x, float y, float w, float h) {
	std::vector<Trash*> objects;

	for (auto trash : trashes){
		auto pos = trash->position;
		if (pos.x >= x && pos.y >= y && pos.x <= x + w && pos.y <= y + h)
			objects.push_back(trash);
	}

	return objects;
}
