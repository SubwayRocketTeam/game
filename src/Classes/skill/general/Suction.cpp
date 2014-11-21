#include "pch.h"
#include "Suction.h"

#include "objects/Unit.h"
#include "objects/Ally.h"
#include "objects/Stage.h"

#include "common/resource.h"

#include "objects/AttackData.h"

using namespace std;
using namespace cocos2d;

void Suction::use(
	Unit *u,
	cocos2d::Vec2 pos){

//	auto slash = Sprite::create(R::SkillSlash);
	auto ally = Ally::getInstance(
	_OPPOSITE(u->getAllyID()));

	AttackData attackData;
	attackData.user = u;
	attackData.object = u;
	attackData.damage = 0;
	attackData.postion = u->getPosition();
	attackData.radius = 100;
	attackData.aggro = 1;

	ally->processAttack(attackData);

	/*
	slash->runAction(
	Sequence::create(
	FadeOut::create(0.4),
	RemoveSelf::create(),
	nullptr));
	slash->setRotation(
	u->getRotation());

	u->addChild(slash);
	*/
}