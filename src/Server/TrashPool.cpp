#include "stdafx.h"
#include "TrashPool.h"
#include "Trash.h"
#include "Player.h"

#include "Stage.h"
#include "Ally.h"

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
	}
}
void TrashPool::spawn(const Vec2 &pos, int count){

	for (int i = 0; i < count; ++i){
		auto trash = new Trash();
		trash->position = pos;
		trash->velocity = Vec2::UNIT_X.getRotated(
			Vec2::ZERO,
			DEGREES_TO_RADIANS(rand() % 360))
			* (20 + rand() % 20) * 60.0f;

		/* ISSUE : frictionµµ * 60? */
		trash->friction = 128 * 60;
		stage->addUnit(trash);

		push(trash);
	}
}

void TrashPool::update(float dt){

	auto players = stage->ally[Ally::Type::allyPlayer];

	for (auto trash : trashes){
		auto pos = trash->position;

		for (auto unit : *players){
			Player* player = (Player*)unit;
			auto playerPos = player->position;

			if (player->isTankFull())
				continue;

			if (pos.getDistance(playerPos) <=
				player->_ATTR(range)){

				auto move =
					(playerPos - pos).getNormalized() *
					trash->_ATTR(speed);

				trash->position += move * dt;
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
