#include "pch.h"
#include "SkillIcon.h"

#include "common/resource.h"

#include "skill/SkillPool.h"
#include "skill/ActiveSkill.h"

using namespace cocos2d;

SkillIcon *SkillIcon::create(
	int id){

	SkillIcon *s = new SkillIcon();

	if(s && s->init(id)){
		s->autorelease();
		return s;
	}
	CC_SAFE_DELETE(s);
	return nullptr;
}
bool SkillIcon::init(
	int _id){

	id = _id;

	if(!Sprite::initWithFile(
		_MAKE_PATH("%d.png", id)))
		return false;

	auto black = Sprite::create(R::SkillIconOverlay);

	overlay = ProgressTimer::create(black);
	overlay->setType(ProgressTimer::Type::RADIAL);
	overlay->setPosition(getContentSize()/2);
	overlay->setOpacity(128);
	overlay->setPercentage(0);
	overlay->setScaleX(-1);
	addChild(overlay);

	return true;
}

void SkillIcon::use(){
	auto pool = SkillPool::getInstance();
	auto skill = (ActiveSkill*)pool->get(id);
	auto cooltime = skill->cooltime;

	overlay->runAction(
		ProgressFromTo::create(cooltime, 100, 0));
}