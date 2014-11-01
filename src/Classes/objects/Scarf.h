#pragma once

#include "cocos2d.h"

class Scarf : public cocos2d::DrawNode{
public:
	static const int Parts = 6;

protected:
	static const int Delay = 2;
	static const int Segments = 30;
	static const int Length = 4;

	struct ScarfNode{
		cocos2d::Vec2 point;
		cocos2d::Vec2 velocity[Delay];
		cocos2d::Vec2 tail;
	};

public:
	static Scarf *create();
	virtual bool init();

	void pushRotation(
		float angle);

protected:
	Scarf();
	virtual ~Scarf();

	void update(float dt);

protected:
	ScarfNode scarfNode[Segments];

	float angle;
};
