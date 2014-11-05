#include "pch.h"
#include "Gauge.h"

using namespace std;
using namespace cocos2d;

Gauge::Gauge() {
	max = 0;
	now = 0;

	targetWidth = 0;
	regenPerSec = 0;
}

Gauge::~Gauge() {

}

bool Gauge::initWithFile(const string &filename) {
	if (!Sprite::initWithFile(filename)) {
		return false;
	}

	this->setAnchorPoint(Vec2(0.0f, 0.0f));

	schedule(SEL_SCHEDULE(&Gauge::update), 1.0f / 60.f);

	return true;
}

void Gauge::update(float dt) {
	if (now > max) {
		now = max;
		return;
	}
	now += dt * regenPerSec;

	this->setScaleX(targetWidth / this->getContentSize().width * this->getNowToMaxRatio());
}

Gauge* Gauge::create(const std::string &name, float _targetWidth, int _max) {
	Gauge* ret = new Gauge();
	if (ret && ret->initWithFile(name)) {
		ret->autorelease();
		ret->max = _max;
		ret->now = _max;
		ret->targetWidth = _targetWidth;
		return ret;
	}
	return nullptr;
}