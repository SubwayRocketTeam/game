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

	// 업그레이드 하는 거 서버로 보냄
	// 쓰레기 없는데 업그레이드 패킷이 날아가면 그냥 무시하기 때문에...
	// 서버랑 클라 쓰레기 수가 정확하게 맞아야 함.
	auto tank = TrashTank::getInstance();
	auto resource = GlobalResource::getInstance();
	auto network = Network::getInstance();

	if (key == EventKeyboard::KeyCode::KEY_SHIFT) {
		tank->blink(cost);
		slide(slideDown);
	}
	else if (!upgradeTrying && resource->trash >= cost){
		switch (key)
		{
		case EventKeyboard::KeyCode::KEY_F1:
			network->sendUpgrade(ATTR_HP);
			break;
		case EventKeyboard::KeyCode::KEY_F2:
			network->sendUpgrade(ATTR_ATTACK);
			break;
		case EventKeyboard::KeyCode::KEY_F3:
			network->sendUpgrade(ATTR_SPEED);
			break;
		case EventKeyboard::KeyCode::KEY_F4:
			network->sendUpgrade(ATTR_RANGE);
			break;
		}

		upgradeTrying = true;
	}
	// 디버그용
	if (key == EventKeyboard::KeyCode::KEY_F5)
		resource->trash += 100;

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
