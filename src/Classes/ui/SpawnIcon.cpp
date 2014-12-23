#include "pch.h"
#include "SpawnIcon.h"

#include "TrashTank.h"

#include "common/resource.h"

#include "skill/SkillPool.h"
#include "skill/ActiveSkill.h"

#include "objects\EnemyFactory.h"
#include "objects\EnemyInfo.h"

using namespace cocos2d;

SpawnIcon *SpawnIcon::create(
	int id){

	SpawnIcon *s = new SpawnIcon();

	if(s && s->init(id)){
		s->autorelease();
		return s;
	}
	CC_SAFE_DELETE(s);
	return nullptr;
}
SpawnIcon::SpawnIcon()
	:id(0), icon(nullptr), cost(0), cooltime(0) {

}

bool SpawnIcon::init(
	int _id){

	id = _id;

	if(!Sprite::initWithFile(R::TankIndicator))
		return false;

	auto icon_image = Sprite::create(_MAKE_PATH("enemy_icon_%d.png", id));

	auto size = getContentSize();
	icon = ProgressTimer::create(icon_image);
	icon->setType(ProgressTimer::Type::RADIAL);
	icon->setPosition(25.f, 46.f);
	icon->setPercentage(100.f);
	addChild(icon);

	auto factory = EnemyFactory::getInstance();
	auto enemy_info = factory->getEenmyInfo((EnemyType)id);
	auto tank = TrashTank::getInstance();

	cost = enemy_info->cost;
	cooltime = enemy_info->cooltime;

	auto x = tank->getCostX(cost);
	setPosition(x, 50.f);

	return true;
}

void SpawnIcon::use(){
	icon->runAction(
		ProgressFromTo::create(cooltime, 0.f, 100.f));
}

int SpawnIcon::getCost() {
	return cost;
}
float SpawnIcon::getCooltime() {
	return cooltime;
}
