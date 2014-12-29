#include "pch.h"
#include "Suction.h"

#include "objects/Unit.h"
#include "objects/Ally.h"
#include "objects/Stage.h"

#include "common/resource.h"

#include "objects/AttackData.h"

using namespace std;
using namespace cocos2d;

bool Suction::update(
	Unit *user,
	float remaining){

//	auto slash = Sprite::create(R::SkillSlash);
	auto ally = Stage::getInstance(user->getStageID())->getAlly(
	_OPPOSITE(user->getAllyID()));

	AttackData attackData;
	attackData.user = user;
	attackData.object = user;
	attackData.damage = 0;
	attackData.position = user->getPosition();
	attackData.radius = user->getAttribute(Attr::range).get();
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

	return true;
}