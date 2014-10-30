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

	return body;
}