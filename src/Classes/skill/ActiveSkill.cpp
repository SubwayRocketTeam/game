#include "ActiveSkill.h"

using namespace std;
using namespace cocos2d;

void use(
	Unit *u,
	cocos2d::Vec2 pos){

	cocos2d::log(
		"ActiveSkill::use : override me");
}

bool ActiveSkill::initExternalData(
	const string &dataPath){

	if(!Skill::initExternalData(dataPath))
		return false;

	return true;
}