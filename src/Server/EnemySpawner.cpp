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

void EnemySpawner::spawn(
	EnemyType type){

	auto ally = stage->ally[Ally::Type::allyEnemy];
	auto factory = EnemyFactory::getInstance();

	Enemy *e = factory->createEnemy(type);
	e->position = Vec2();
	e->resetAggro();

	ally->push(e);
	stage->addUnit(e);
}