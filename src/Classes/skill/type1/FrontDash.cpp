#include "pch.h"
#include "FrontDash.h"
#include "objects/PartedBody.h"

#include "common/resource.h"
#include "objects/Unit.h"

using namespace std;
using namespace cocos2d;

void FrontDash::use(
	Unit *u,
	cocos2d::Vec2 pos){

	float angle = u->getBody()->getRotation();
	Vec2 foward = 
		-Vec2(0,1).rotateByAngle(Vec2::ZERO, 
			CC_DEGREES_TO_RADIANS(-angle));
	
	u->runAction(
		MoveBy::create(duration, foward * 250))
	->setTag(Unit::actionMove);
}