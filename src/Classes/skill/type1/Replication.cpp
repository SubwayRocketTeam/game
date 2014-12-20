#include "pch.h"
#include "Replication.h"

#include "objects/Unit.h"
#include "objects/Ally.h"
#include "objects/Bullet.h"
#include "objects/Stage.h"
#include "objects/Replica.h"

#include "common/resource.h"

#include "ui/StatusConsole.h"

using namespace cocos2d;

void Replication::use(
	Unit *u,
	cocos2d::Vec2 pos){

	auto stage = Stage::getInstance(u->getStageID());
	auto replica = Replica::create();

	replica->setPosition(pos);

	stage->addChild(replica);
}