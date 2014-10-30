#pragma once

#include "cocos2d.h"

#include <string>

class PhysicsFactory{
public:
	static PhysicsFactory *create();
	static PhysicsFactory *getInstance();

	cocos2d::PhysicsBody *make(
		const std::string &name);
};