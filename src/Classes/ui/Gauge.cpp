#include "pch.h"
#include "Gauge.h"

#include "objects/Unit.h"

#include "common/resource.h"

using namespace std;
using namespace cocos2d;

Gauge::Gauge() {

}

Gauge::~Gauge() {

}

Gauge* Gauge::create(Unit* _target) {
	Gauge* ret = new Gauge();
	if (ret && ret->init()) {
		ret->autorelease();
		ret->target = _target;
		return ret;
	}
	return nullptr;
}

bool Gauge::init() {
	if (!Node::init()) {
		return false;
	}

	hp = Sprite::create(R::HPGauge);
	addChild(hp);

	//mp = Sprite::create(R::MPGauge);
	//addChild(mp);

	hp->setPositionY(100);
	//mp->setPositionY(90);

	hp->setOpacity(150);
	//mp->setOpacity(150);

	scheduleUpdate();

	return true;
}

void Gauge::update(float dt) {
	processHP(dt);
}

void Gauge::processGauge(float dt, const std::string &attrName) {
	float now = target->getAttribute(attrName).getValue();
	float max = target->getAttribute(attrName).getMaxValue();
	float regenPerSecHP = target->getAttribute(attrName + "_regen").get();
	if (now > max) {
		now = max;
		return;
	}

	now += dt * regenPerSecHP;
}

void Gauge::processHP(float dt) {
	float now = target->getAttribute("hp").getValue();
	float max = target->getAttribute("hp").getMaxValue();

	if (now > max) {
		now = max;
	}

	hp->setTextureRect(Rect(0, 0, now / max * 100, 10));
}

void Gauge::processMP(float dt) {
	float now = target->getAttribute("mp").getValue();
	float max = target->getAttribute("mp").getMaxValue();
	float regenPerSecHP = target->getAttribute("mp_regen").get();
	if (now > max) {
		now = max;
		return;
	}

	now += dt * regenPerSecHP;

	mp->setTextureRect(Rect(0, 0, now / max * 100, 10));
}