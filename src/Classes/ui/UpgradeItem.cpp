#include "pch.h"
#include "UpgradeItem.h"

#include "common/resource.h"

using namespace cocos2d;

UpgradeItem *UpgradeItem::create(
	int id){

	UpgradeItem *s = new UpgradeItem();

	if (s && s->init(id)){
		s->autorelease();
		return s;
	}
	CC_SAFE_DELETE(s);
	return nullptr;
}
UpgradeItem::UpgradeItem()
	:progress(nullptr), level(0) {

}

bool UpgradeItem::init(
	int id){

	if (!Sprite::initWithFile(_MAKE_PATH("upgrade_back_%d.png", id)))
		return false;

	// auto size = getContentSize();
	setAnchorPoint(Vec2(0.5f, 0.5f));
	setPositionY(36.f);
	// setPositionY(size.height / 2);

	auto front_image = Sprite::create(_MAKE_PATH("upgrade_front_%d.png", id));
	progress = ProgressTimer::create(front_image);
	progress->setAnchorPoint(Vec2(0.f, 0.f));
	progress->setType(ProgressTimer::Type::BAR);
	progress->setBarChangeRate(Vec2(1, 0));
	progress->setMidpoint(Vec2(0, 0));
	progress->setPercentage(0.f);
	addChild(progress);

	return true;
}

void UpgradeItem::upgrade(){
	if (level >= Max::Upgrade)
		return;
	level += 1;
	progress->setPercentage(100.f * level / Max::Upgrade);
	setScale(2.f);
	runAction(
		EaseExponentialOut::create(
		ScaleTo::create(0.5f, 1.f)
		));
}