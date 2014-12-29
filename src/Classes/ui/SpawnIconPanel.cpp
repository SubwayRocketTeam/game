#include "pch.h"

#include "SpawnIconPanel.h"
#include "SpawnIcon.h"

#include "TrashTank.h"

#include "skill/SkillPool.h"
#include "skill/ActiveSkill.h"

#include "common/resource.h"

#include "objects\GlobalResource.h"
#include "objects\EnemyType.h"

#include "network/Network.h"

using namespace std;
using namespace cocos2d;

static SpawnIconPanel *instance = nullptr;

SpawnIconPanel *SpawnIconPanel::create(){

	instance = new SpawnIconPanel();

	if(instance && instance->init()){
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return nullptr;
}
SpawnIconPanel *SpawnIconPanel::getInstance(){
	return instance;
}

bool SpawnIconPanel::init(){
	if(!Node::init())
		return false;
	
	enableKeyboardInput(this);

	schedule(
		SEL_SCHEDULE(&SpawnIconPanel::updateCooltime), 1.f / Global::ups);

	return true;
}

void SpawnIconPanel::setIconList(
	int id[Max::Enemies]){

	for(int i=0;i<Max::Enemies;i++){
		auto icon = SpawnIcon::create(id[i]);
		addChild(icon);
		icons[id[i]] = icon;
		cooltimes[id[i]] = 0.f;
	}
}
void SpawnIconPanel::use(
	int id){
	
	auto& trash = GlobalResource::getInstance()->trash;
	auto cost = icons[id]->getCost();
	if (cooltimes[id] > 0.f || trash < cost)
		return;
	trash -= cost;
	cooltimes[id] = icons[id]->getCooltime();
	icons[id]->use();

	auto network = Network::getInstance();
	auto type = id + ENEMY_BASIC;
	network->sendSpawnRequest(type);
}

void SpawnIconPanel::processSpawn(
	EventKeyboard::KeyCode code){

	int type = -1;

	/* TODO : 키<->몹ID 어딘가에 저장 */
	switch(code){
	case EventKeyboard::KeyCode::KEY_1:
		type = enemyBasic;
		break;
	case EventKeyboard::KeyCode::KEY_2:
		type = enemyFollow;
		break;
	case EventKeyboard::KeyCode::KEY_3:
		type = enemySpiral;
		break;
	case EventKeyboard::KeyCode::KEY_4:
		type = enemyExplode;
		break;
	}

	if (type >= 0)
		use(type);
}
void SpawnIconPanel::onKeyboardDown(
	EventKeyboard::KeyCode code){

	processSpawn(code);
}


void SpawnIconPanel::updateCooltime(
	float dt) {
	for (auto& cooltime : cooltimes) {
		if (cooltime.second > 0.f)
			cooltime.second -= dt;
	}
}

void SpawnIconPanel::onExit() {
	disableKeyboardInput();
	Node::onExit();
}
