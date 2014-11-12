#include "pch.h"
#include "FrontDash.h"

#include "objects/PartedBody.h"
#include "objects/Unit.h"
#include "objects/Afterimage.h"

#include "common/Effect.h"
#include "common/EffectFactory.h"
#include "common/resource.h"

#include "ui/StatusConsole.h"

using namespace std;
using namespace cocos2d;

bool FrontDash::initExternalData(
	const string &dstPath){

	if(!ActiveSkill::initExternalData(dstPath))
		return false;
	
	distance = json.get("distance", 0).asFloat();

	return true;
}

void FrontDash::use(
	Unit *u,
	cocos2d::Vec2 pos){

	auto console = StatusConsole::getInstance();
	console->output("use front dash");

	float angle = u->getBody()->getRotation();
	Vec2 foward = 
		-Vec2(0,1).rotateByAngle(Vec2::ZERO, 
			CC_DEGREES_TO_RADIANS(-angle));
	
	/*
	u->runAction(
		MoveBy::create(duration, foward * distance))
	->setTag(Unit::actionMove);
	*/
	u->getPhysicsBody()->applyImpulse(
		foward * 800000);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [=](PhysicsContact &contact){
		printf("impact\n");

		auto ally = Ally::getInstance(
			_OPPOSITE(u->getAllyID()));

		AttackData attackData;
		attackData.damage = 1;
		attackData.startPostion = u->getPosition();
		attackData.targetPostion = pos;
		attackData.radius = 130;
		attackData.halfAngle = 90;

		ally->processAttack(u, attackData);

		u->getEventDispatcher()->removeEventListener(listener);

		return true;
	};

	u->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, u);

	auto afterimage =  Afterimage::createWithPartedBody(
		u->getParent(),
		u->getBody(), duration);
	u->addChild(afterimage);

	auto factory = EffectFactory::getInstance();
	auto effect = factory->make("dash", false);
	effect->setRotation(u->getBody()->getRotation() + 90);
	u->addChild(effect);
}