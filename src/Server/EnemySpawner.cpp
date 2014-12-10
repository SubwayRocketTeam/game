#include "stdafx.h"
#include "EnemySpawner.h"
#include "EnemyFactory.h"

#include "Enemy.h"
#include "Stage.h"
#include "Ally.h"

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
	e->setPosition(
		getPosition());
	e->resetAggro();

	ally->push(e);
	stage->addChild(e, Z::unit);
}