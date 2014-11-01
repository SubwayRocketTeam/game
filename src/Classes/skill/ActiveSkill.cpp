#include "pch.h"
#include "ActiveSkill.h"

#include "objects/Unit.h"

using namespace std;
using namespace cocos2d;

void ActiveSkill::use(
	Unit *u,
	cocos2d::Vec2 pos){

	cocos2d::log(
		"ActiveSkill::use : override me");
}

bool ActiveSkill::initExternalData(
	const string &dataPath){

	if(!Skill::initExternalData(dataPath))
		return false;

	duration = json.get("duration",0).asFloat();
	cooltime = json.get("cooltime",0).asFloat();
	cost = json.get("cost",0).asFloat();

	return true;
}