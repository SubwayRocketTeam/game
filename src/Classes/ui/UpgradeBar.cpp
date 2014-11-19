#include "pch.h"
#include "UpgradeBar.h"

#include "common/resource.h"

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

	if(key == EventKeyboard::KeyCode::KEY_SHIFT)
		slide(slideDown);
}
void UpgradeBar::onKeyboardUp(
	EventKeyboard::KeyCode key){

	if(key == EventKeyboard::KeyCode::KEY_SHIFT)
		slide(slideUp);
}