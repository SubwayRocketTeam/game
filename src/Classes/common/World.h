#pragma once

#include "cocos2d.h"
#include "GLES-Render.h"

class b2World;
class b2Body;

class Unit;

#define PTM_RATIO 32
//#define PTM(x) x * PTM_RATIO

class World : public cocos2d::Node {
public:
	static World *create();
	static World *getInstance();

	b2Body *make(Unit *target);
	void destroy(Unit *target);

private:
	World();
	~World();

	virtual bool init() override;

	virtual void update(float dt) override;

private:
	b2World *world;
};