#pragma once

#include "cocos2d.h"

class Unit;

class CollisionDetector : public cocos2d::Node {
public:
	static CollisionDetector* create();

	void addUnit(
		Unit* unit);
	void removeUnit(
		Unit* unit);

protected:
	bool init();
	void update(
		float dt);

protected:
	cocos2d::Vector<Unit*> unitVector;
};