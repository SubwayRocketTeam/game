#include "pch.h"
#include "PhysicsFactory.h"

#include "objects/Unit.h"

using namespace std;
using namespace cocos2d;

static PhysicsFactory *instance = nullptr;

PhysicsFactory *PhysicsFactory::create(){
	instance = new PhysicsFactory();

	return instance;
}
PhysicsFactory *PhysicsFactory::getInstance(){
	return instance;
}

PhysicsBody *PhysicsFactory::make(
	const string &name){

	PhysicsBody *body;

	body = PhysicsBody::createCircle(20);

	return body;
}