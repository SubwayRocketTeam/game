#include "pch.h"
#include "SkillIconPanel.h"
#include "SkillIcon.h"

#include "skill/SkillPool.h"
#include "skill/ActiveSkill.h"

#include "common/resource.h"

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
