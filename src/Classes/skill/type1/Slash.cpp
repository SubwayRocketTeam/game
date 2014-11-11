#include "pch.h"
#include "Slash.h"

#include "common/EffectFactory.h"
#include "common/Effect.h"
#include "objects/PartedBody.h"
#include "objects/Unit.h"
#include "objects/Ally.h"
#include "common/resource.h"

#include "ui/StatusConsole.h"

using namespace std;
using namespace cocos2d;

bool Slash::init(
	const string &dataPath){

	if(!ActiveSkill::init(dataPath))
		return false;

	return true;
}
void Slash::use(
	Unit *u,
	cocos2d::Vec2 pos){

	auto slash = EffectFactory::getInstance()->make("effect01", false);
	auto ally = Ally::getInstance(Ally::Type::allyEnemy);

	AttackData attackData;
	attackData.damage = 1;
	attackData.startPostion = u->getPosition();
	attackData.targetPostion = pos;
	attackData.radius = 100;
	attackData.halfAngle = 90;

	ally->processAttack(u, attackData);

	/*
	slash->runAction(
		Sequence::create(
			FadeOut::create(0.4),
			RemoveSelf::create(),
			nullptr));*/
	slash->setRotation(
		u->getBody()->getRotation() + 180);
	slash->setScale(0.5f);

	u->addChild(slash);
}