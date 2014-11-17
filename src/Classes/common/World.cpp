#include "pch.h"

#include "World.h"
#include "objects/Unit.h"

#include <Box2D/Box2D.h>

using namespace cocos2d;

static World *instance = nullptr;

World::World() {

}

World::~World() {

}

World *World::create() {
	instance = new World();

	if (!instance->init()) {
		return nullptr;
	}

	return instance;
}

World *World::getInstance() {
	return instance;
}

b2Body *World::make(Unit *target) {
	b2BodyDef def;
	def.type = b2_dynamicBody;
	def.fixedRotation = true;
	def.position.Set(target->getPositionX() / PTM_RATIO, target->getPositionY() / PTM_RATIO);

	b2CircleShape shape;
	shape.m_p.Set(0, 0);
	shape.m_radius = 60 / PTM_RATIO;

	b2FixtureDef fixDef;
	fixDef.shape = &shape;
	fixDef.density = 1.0f;
	fixDef.friction = 0.1f;
	fixDef.restitution = 0.0f;

	b2Body *body = world->CreateBody(&def);
	body->CreateFixture(&fixDef);

	return body;
}

void World::destroy(Unit *target) {
	world->DestroyBody(target->getPhysicsBody());
}

bool World::init() {
	if (!Node::init()) {
		return false;
	}

	world = new b2World(b2Vec2(0, 0));
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);

	scheduleUpdate();

	return true;
}

void World::update(float dt) {
	world->Step(dt, 8, 8);
}