#include "ActiveSkill.h"

#include "shared/compat.h"

using namespace std;

void ActiveSkill::use(
	Unit *u,
	Vec2 pos){

}

void ActiveSkill::update(
	Unit *u,
	float dt) {

}

bool ActiveSkill::initExternalData(
	const string &dataPath){

	if(!Skill::initExternalData(dataPath))
		return false;

	cooltime = json.get("cooltime",0).asFloat();
	cost = json.get("cost",0).asFloat();

	return true;
}