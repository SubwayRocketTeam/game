#include "pch.h"
#include "Adrenaline.h"

#include "objects/Unit.h"

using namespace cocos2d;

bool Adrenaline::update(
	Unit *user, float remaining){

	user->runAction(
		Sequence::create(
			TintTo::create(0.1, 255,64,64),
			TintTo::create(0.2, 255,255,255),
			nullptr));

	return true;
}