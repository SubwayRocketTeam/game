#pragma once

#include "cocos2d.h"

class Unit;

enum {
	HP = 0x01,
	MP = 0x02,
};

// Hp ¶Ç´Â Mp
class Gauge : public cocos2d::Node {
public:
	Gauge();
	virtual ~Gauge();

public:
	static Gauge* create(Unit* _target);
public:
	bool initWithTarget(Unit* _target);
	void update(float dt) override;
public:
	void processHP(float dt);
	void processMP(float dt);
	void processGauge(float dt, const std::string &attrName);
private:
	Unit* target;

	cocos2d::Sprite* hp;
	cocos2d::Sprite* mp;
};