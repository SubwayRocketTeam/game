#include "stdafx.h"
#include "EnemySpawner.h"
#include "EnemyFactory.h"

#include "Unit.h"
#include "Enemy.h"
#include "Stage.h"
#include "Ally.h"

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

	auto ally = stage->ally[Ally::Type::allyEnemy];
	auto factory = EnemyFactory::getInstance();

	Enemy *e = factory->createEnemy(type);
	e->position = Vec2(rand()%1600-800, rand()%1200-600);

	ally->push(e);
	stage->addUnit(e);

	e->resetAggro();
	return e;
}