#include "pch.h"

#include "SkillIconPanel.h"
#include "SkillIcon.h"

#include "skill/SkillPool.h"
#include "skill/ActiveSkill.h"

#include "common/resource.h"

#include "network/Network.h"

using namespace std;
using namespace cocos2d;

static SkillIconPanel *instance = nullptr;

SkillIconPanel *SkillIconPanel::create(){

	instance = new SkillIconPanel();

	if(instance && instance->init()){
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return nullptr;
}
SkillIconPanel *SkillIconPanel::getInstance(){
	return instance;
}

bool SkillIconPanel::init(){
	if(!Sprite::initWithFile(R::SkillPanel))
		return false;

	enableKeyboardInput(this);

	return true;
}

void SkillIconPanel::setSkillList(
	int id[Max::Skills]){

	for(int i=0;i<Max::Skills;i++){
		auto icon = SkillIcon::create(id[i]);
		icon->setPosition(50 + 68 * i, 37);
		addChild(icon);
		icons[id[i]] = icon;
	}
}
void SkillIconPanel::use(
	int id){
	
	icons[id]->use();
}

void SkillIconPanel::processSpawn(
	EventKeyboard::KeyCode code){

	auto network = Network::getInstance();
	int type = -1;

	/* TODO : 키<->몹ID 어딘가에 저장 */
	switch(code){
	case EventKeyboard::KeyCode::KEY_1:
		type = 10;
		break;
	case EventKeyboard::KeyCode::KEY_2:
		type = 11;
		break;
	case EventKeyboard::KeyCode::KEY_3:
		type = 12;
		break;
	case EventKeyboard::KeyCode::KEY_4:
		type = 13;
		break;
	}

	if(type >= 0)
		network->sendSpawnRequest(type);
}
void SkillIconPanel::onKeyboardDown(
	EventKeyboard::KeyCode code){

	processSpawn(code);
}