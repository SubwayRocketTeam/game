#include "stdafx.h"
#include "EnemySpawner.h"
#include "EnemyFactory.h"

#include "Unit.h"
#include "Enemy.h"
#include "Stage.h"
#include "GameRoom.h"
#include "Ally.h"

#include "PacketType.h"

#include "Vec2.h"

EnemySpawner::EnemySpawner(Stage* const stage)
	:stage(stage){
}
EnemySpawner::~EnemySpawner(){
}

void EnemySpawner::init(){
}

Enemy* EnemySpawner::spawn(
	EnemyType type){
	return spawn(type, Vec2(rand()%1600-800, rand()%1200-600));
}

Enemy* EnemySpawner::spawn(
	EnemyType type,
	const Vec2& position){

	auto ally = stage->ally[Ally::Type::allyEnemy];
	auto factory = EnemyFactory::getInstance();

	Enemy *e = factory->createEnemy(type);
	e->position = position;

	// ally->push(e);
	stage->addUnit(e);

	e->resetAggro();

	SpawnUnit noti;
	noti.id = e->id;
	noti.stage = stage->id;
	noti.x = position.x;
	noti.y = position.y;
	noti.unit_type = UNIT_ENEMY;
	noti.sub_type = type + ENEMY_BASIC;

	stage->gameroom->sendPacket(noti);

	return e;
}

