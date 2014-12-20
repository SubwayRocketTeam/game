#include "pch.h"
#include "Duplication.h"

#include "objects/Unit.h"
#include "objects/Ally.h"
#include "objects/Bullet.h"
#include "objects/Stage.h"

#include "objects/EnemyDup.h"
#include "objects/EnemyFactory.h"

using namespace cocos2d;

void Duplication::use(
	Unit *u,
	cocos2d::Vec2 pos){

	auto factory = EnemyFactory::getInstance();
	auto stage = Stage::getInstance(u->getStageID());

	for(int i=0;i<2;i++){
		auto e = 
			factory->createEnemy(EnemyType::enemyBasic);
		e->setPosition(pos);
		stage->addChild(e);
	}
}