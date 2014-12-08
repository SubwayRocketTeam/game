#include "pch.h"
#include "TrashPool.h"
#include "Trash.h"

#include "Stage.h"
#include "GlobalResource.h"

#include <algorithm>

using namespace std;
using namespace cocos2d;

static TrashPool *instance = nullptr;

TrashPool::TrashPool(){
}
TrashPool::~TrashPool(){
}

TrashPool *TrashPool::create(){
	instance = new TrashPool();
	if(instance && instance->init())
		return instance;
	return nullptr;
}
TrashPool *TrashPool::getInstance(){
	return instance;
}
bool TrashPool::init(){
	if(!Node::init())
		return false;

	scheduleUpdate();

	return true;
}

void TrashPool::push(
	Trash *trash){

	trashes.pushBack(trash);
}
void TrashPool::remove(
	Trash *trash){

	trashes.eraseObject(trash);
}

void TrashPool::spawn(
	int count){

	auto stage = Stage::getInstance(0);
	for (int i = 0; i < count; ++i){
		auto trash = Trash::create();
		trash->setPosition(
			rand()%1600-800, rand()%1200-600);
		stage->addChild(trash, Z::trash);

		push(trash);
	}
}
void TrashPool::spawn(
	Vec2 pos,
	int count){

	auto stage = Stage::getInstance(0);
	for (int i = 0; i < count; ++i){
		auto trash = Trash::create();
		trash->setPosition(pos);
		trash->velocity = Vec2::UNIT_X.rotateByAngle(
			Vec2::ZERO,
			CC_DEGREES_TO_RADIANS(rand() % 360))
			* (20 + rand() % 20) * 60.0f;

		/* ISSUE : friction도 * 60? */
		trash->friction = 128 * 60;
		stage->addChild(trash);

		push(trash);
	}
}
Vector<Trash*> TrashPool::query(
	Rect rect){

	Vector<Trash*> objects;
	for(auto trash : trashes){
		auto trashPos = trash->getPosition();
		Rect trashRect =
			Rect(trashPos.x-25, trashPos.y-25, 50,50);

		if(trashRect.intersectsRect(rect))
			objects.pushBack(trash);
	}

	return objects;
}

/* 플레이어가 쓰레기를 빨아들이는게 아니라
 * 쓰레기가 플레이어에게 빨려들어가는 구조.
 * -> 현실적인 인과관계상으론 반대지만, 
	  이렇게짜면 구조상으로 쓰레기는 스스로 움직이는 꼴
	  (플레이어가 다른 오브젝트에 간섭 X)

 * Trash 오브젝트의 speed attr은 빨려들어가는 속도가 된다.
 * 쓰레기 스스로 빨려들어가는 속도 조절 가능
 * (무게 따라 속도 다르다던가...)
 */
void TrashPool::update(
	float dt){

	auto players = Ally::getInstance(
		Ally::Type::allyPlayer);
	auto resource = GlobalResource::getInstance();
	
	for(auto trash : trashes){
		auto pos = trash->getPosition();

		for(auto player : *players){
			auto playerPos = player->getPosition();

			/* TODO : 내가 조종하는 플레이어일 경우에만 이거 처리 */
			if(resource->trash >= Max::Tank)
				continue;

			if(pos.getDistance(playerPos) <=
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