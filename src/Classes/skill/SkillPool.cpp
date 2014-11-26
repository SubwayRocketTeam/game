#include "pch.h"
#include "SkillPool.h"

#include "common/JsonLoader.h"
#include "common/resource.h"

#include "skill/id.h"
#include "skill/general/Suction.h"
#include "skill/general/Repair.h"
#include "skill/type1/Slash.h"
#include "skill/type1/FrontDash.h"
#include "skill/type1/Adrenaline.h"
#include "skill/enemy/Spiral.h"
#include "skill/PassiveSkill.h"

using namespace std;
using namespace cocos2d;

static SkillPool *instance = nullptr;

SkillPool *SkillPool::create(){
	instance = new SkillPool();

	if(instance)
		instance->init();

	return instance;
}
SkillPool *SkillPool::getInstance(){
	return instance;
}

bool SkillPool::init(){
	Json::Value root;
	if(!JsonLoader::load(R::SkillList, root))
		return false;

	skills[skillSlash] = new Slash();
	skills[skillFrontDash] = new FrontDash();
	skills[skillSuction] = new Suction();
	skills[skillTestPassive] = new Adrenaline();
	skills[skillSpiral] = new Spiral();
	skills[skillRepair] = new Repair();

	for(auto skill : root){
		int id = skill.get("id",0).asInt();
		string dataPath =
			skill.get("path", string::npos).asString();

		initSkill(id, dataPath);
	}

	return true;
}
bool SkillPool::initSkill(
	int id, const string &dataPath){

	skills[id]->init(dataPath);

	return true;
}
void SkillPool::release(){
	for(auto pair : skills){
		delete pair.second;
	}
	skills.clear();
}

Skill *SkillPool::get(
	int id){

	auto pair = skills.find(id);
	if(pair == skills.end())
		return nullptr;

	return pair->second;
}