#include "pch.h"
#include "UpgradeBar.h"
#include "TrashTank.h"

#include "common/resource.h"
#include "objects\GlobalResource.h"

#include "objects\ControlablePlayer.h"

#include "network\Network.h"

using namespace cocos2d;

static UpgradeBar *instance = nullptr;
static const int actionSlide = 100;

enum UpgradeBar::SlideDirection{
	slideUp,
	slideDown
};

UpgradeBar *UpgradeBar::create(){
	instance = new UpgradeBar();

	if(instance && instance->init()){
		instance->autorelease();
		return instance;
	}

	CC_SAFE_DELETE(instance);
	return nullptr;
}
UpgradeBar *UpgradeBar::getInstance(){
	return instance;
}

UpgradeBar::UpgradeBar() :cost(10), upgradeTrying(false) {
	// TODO: cost 초기값 빼기
}

UpgradeBar::~UpgradeBar() {

}

bool UpgradeBar::init(){
	if(!Sprite::initWithFile(R::UpgradeBar))
		return false;

	enableKeyboardInput(this);

	return true;
}
void UpgradeBar::update(
	float dt){

}

void UpgradeBar::slide(
	SlideDirection direction){

	auto visibleSize =
		Director::getInstance()->getVisibleSize();
	auto dst = Vec2(visibleSize.width/2,visibleSize.height);

	if(direction == slideDown)
		dst.y -= getContentSize().height;

	stopActionByTag(actionSlide);
	runAction(
		MoveTo::create(0.05f, dst))
		->setTag(actionSlide);
}

void UpgradeBar::onKeyboardDown(
	EventKeyboard::KeyCode key){

	// 업그레이드 하는 거 서버로 보내기
	auto tank = TrashTank::getInstance();
//	auto player = ControlablePlayer::getInstance();
	auto resource = GlobalResource::getInstance();
	auto network = Network::getInstance();
	// bool upgraded = false;
	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_SHIFT:
		tank->blink(cost);
		slide(slideDown);
		break;
	case EventKeyboard::KeyCode::KEY_F1:
		if (upgradeTrying)
			return;
		if (resource->trash >= cost)
			// upgraded = player->upgrade(Attr::hp);
			network->sendUpgrade(ATTR_HP);
		upgradeTrying = true;
		break;
	case EventKeyboard::KeyCode::KEY_F2:
		if (upgradeTrying)
			return;
		if (resource->trash >= cost)
			// upgraded = player->upgrade(Attr::attack);
			network->sendUpgrade(ATTR_ATTACK);
		upgradeTrying = true;
		break;
	case EventKeyboard::KeyCode::KEY_F3:
		if (upgradeTrying)
			return;
		if (resource->trash >= cost)
			// upgraded = player->upgrade(Attr::speed);
			network->sendUpgrade(ATTR_SPEED);
		upgradeTrying = true;
		break;
	case EventKeyboard::KeyCode::KEY_F4:
		if (upgradeTrying)
			return;
		if (resource->trash >= cost)
			// upgraded = player->upgrade(Attr::range);
			network->sendUpgrade(ATTR_RANGE);
		upgradeTrying = true;
		break;
	}

	/*
	if (upgraded) {
		resource->trash -= cost;
		cost += 10;
	}
	*/

}
void UpgradeBar::onKeyboardUp(
	EventKeyboard::KeyCode key){

	if(key == EventKeyboard::KeyCode::KEY_SHIFT){
		auto tank = TrashTank::getInstance();
		tank->stopBlink();

		slide(slideUp);
	}
}
void UpgradeBar::upgradeOver() {
	// TODO: cost 증가값 빼기
	auto resource = GlobalResource::getInstance();
	resource->trash -= cost;
	cost += 10;
	upgradeTrying = false;
}
