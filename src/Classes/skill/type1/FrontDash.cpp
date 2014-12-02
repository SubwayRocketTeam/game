#include "pch.h"
#include "FrontDash.h"

#include "objects/Unit.h"
#include "objects/Afterimage.h"

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

	float angle = u->getRotation();
	Vec2 foward = 
		-Vec2(0,1).rotateByAngle(Vec2::ZERO, 
			CC_DEGREES_TO_RADIANS(-angle));
	
	u->runAction(
		MoveBy::create(duration, foward * distance));

	auto afterimage =  Afterimage::create(
		u->getParent(),
		u, duration);
	u->addChild(afterimage);
}