#include "pch.h"
#include "UserResources.h"

using namespace cocos2d;

UserResources* UserResources::instance = nullptr;

UserResources::UserResources() {

}

UserResources::~UserResources() {

}

UserResources* UserResources::getInstance() {
	if (!instance) {
		instance = new UserResources();
		instance->init();
	}

	return instance;
}

bool UserResources::init() {
	if (!Node::init()) {
		return false;
	}

	auto size = Director::getInstance()->getVisibleSize();

	levelLabel = LabelTTF::create("Create", "arial", 24);
	levelLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
	levelLabel->setPosition(Vec2(size.width / 10 * 5, size.height / 10 * 9));
	this->addChild(levelLabel);

	expLabel = LabelTTF::create("exp/maxexp", "arial", 24);
	expLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
	expLabel->setPosition(Vec2(size.width / 10 * 6, size.height / 10 * 9));
	this->addChild(expLabel);

	goldLabel = LabelTTF::create("gold : ", "arial", 24);
	goldLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
	goldLabel->setPosition(Vec2(size.width / 10 * 7.5, size.height / 10 * 9));
	this->addChild(goldLabel);

	return true;
}

void UserResources::setLevel(int _level) {
	char arr[30];
	sprintf_s(arr, "Lv : %d", _level);
	levelLabel->setString(arr);
}

void UserResources::setExpAndMaxExp(int _exp, int _maxExp) {
	//exp = _exp + " / " + _maxExp;
	char arr[30];
	sprintf_s(arr, "%d / %d", _exp, _maxExp);
	expLabel->setString(arr);
}

void UserResources::setGold(int _gold) {
	//gold = "gold : " + _gold;
	char arr[30];
	sprintf_s(arr, "Gold : %d", _gold);
	goldLabel->setString(arr);
}