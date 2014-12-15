#include "SkillPool.h"

#include "common/resource.h"

#include "shared/JsonLoader.h"

#include "shared/skill/id.h"
#include "shared/skill/ActiveSkill.h"
#include "shared/skill/PassiveSkill.h"

#include "skill/general/Suction.h"
#include "skill/general/Repair.h"
#include "skill/type1/Slash.h"
#include "skill/type1/FrontDash.h"
#include "skill/type1/Adrenaline.h"
#include "skill/enemy/Spiral.h"
#include "skill/enemy/Explosion.h"
#include "skill/enemy/EnemyShot.h"

#define REGISTER_SKILL(name) skills[skill##name] = new name()

using namespace std;

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

	REGISTER_SKILL(Slash);
	REGISTER_SKILL(FrontDash);
	REGISTER_SKILL(Suction);
	REGISTER_SKILL(Adrenaline);
	REGISTER_SKILL(Spiral);
	REGISTER_SKILL(Explosion);
	REGISTER_SKILL(EnemyShot);
	REGISTER_SKILL(Repair);

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