#include "stdafx.h"
#include "TrashPool.h"
#include "Unit.h"

#include "Stage.h"
#include "Ally.h"

TrashPool::TrashPool(Stage* const stage)
	:stage(stage){
}
TrashPool::~TrashPool(){
}

void TrashPool::init(){
}

void TrashPool::push(Unit *trash){
	_ASSERT(trash->type == UT_TRASH);
	trashes.push_back(trash);
}
void TrashPool::remove(Unit *trash){
	auto it = std::find(trashes.begin(), trashes.end(), trash);
	if (it != trashes.end())
		trashes.erase(it);
}

void TrashPool::spawn(int count){

	for (int i = 0; i < count; ++i){
		auto trash = Unit::create();
		trash->setPosition(
			rand() % 1600 - 800, rand() % 1200 - 600);
		stage->addUnit(trash);

		push(trash);
	}
}
void TrashPool::spawn(const Vec2 &pos, int count){

	for (int i = 0; i < count; ++i){
		auto trash = Unit::create();
		trash->setPosition(pos);
		trash->velocity = Vec2::UNIT_X.getRotated(
			Vec2::ZERO,
			CC_DEGREES_TO_RADIANS(rand() % 360))
			* (20 + rand() % 20) * 60.0f;

		/* ISSUE : frictionµµ * 60? */
		trash->friction = 128 * 60;
		stage->addUnit(trash);

		push(trash);
	}
}

void TrashPool::update(float dt){

	auto players = stage->ally[Ally::Type::allyPlayer];
	auto resource = GlobalResource::getInstance();

	for (auto trash : trashes){
		auto pos = trash->position;

		for (auto player : *players){
			auto playerPos = player->position;

			if (resource->trash >= Max::Tank)
				continue;

			if (pos.getDistance(playerPos) <=
				player->_ATTR(range)){

				auto move =
					(playerPos - pos).getNormalized() *
					trash->_ATTR(speed);

				trash->runAction(
					MoveBy::create(dt, move));
			}
		}
	}
}