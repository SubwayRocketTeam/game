#include "pch.h"
#include "UpgradeBar.h"
#include "TrashTank.h"
#include "UpgradeItem.h"

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

UpgradeBar::UpgradeBar() :itemHeight(100.f), cost(10), upgradeTrying(false) {
	// TODO: cost 초기값 빼기
}

UpgradeBar::~UpgradeBar() {

}

bool UpgradeBar::init(){
	if(!Node::init())
		return false;

	auto visibleSize =
		Director::getInstance()->getVisibleSize();

	for (int i = 1; i <= 4; ++i) {
		auto item = UpgradeItem::create(i);
		itemHeight = item->getContentSize().height;

		item->setPositionX(((i - 1) * 2 - 3) * (item->getContentSize().width + 10) / 2);
		items[i] = item;
		addChild(item);
	}

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
		dst.y -= itemHeight;

	stopActionByTag(actionSlide);
	runAction(
		EaseOut::create(
		MoveTo::create(0.1f, dst),
		5.f
		))->setTag(actionSlide);
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
		UpgradeType type = ATTR_NONE;

		switch (key)
		{
		case EventKeyboard::KeyCode::KEY_F1:
			type = ATTR_HP;
			break;
		case EventKeyboard::KeyCode::KEY_F2:
			type = ATTR_ATTACK;
			break;
		case EventKeyboard::KeyCode::KEY_F3:
			type = ATTR_SPEED;
			break;
		case EventKeyboard::KeyCode::KEY_F4:
			type = ATTR_RANGE;
			break;
		default:
			return;
		}

		network->sendUpgrade(type);
		items[type]->upgrade();
		upgradeTrying = true;
	}
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
	cost = MIN(Max::Tank, cost+10);
	upgradeTrying = false;
}

void UpgradeBar::onExit() {
	disableKeyboardInput();
	Node::onExit();
}
