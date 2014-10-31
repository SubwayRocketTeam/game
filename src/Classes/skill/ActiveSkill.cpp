#include "ActiveSkill.h"

using namespace std;
using namespace cocos2d;

float ActiveSkill::duration = 0;
float ActiveSkill::cooltime = 0;
float ActiveSkill::cost = 0;

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