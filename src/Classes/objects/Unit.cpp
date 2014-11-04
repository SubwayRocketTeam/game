#include "pch.h"
#include "Unit.h"

#include "PartedBody.h"

using namespace std;
using namespace cocos2d;

Unit::Unit(){
}
Unit::~Unit(){
}

Unit *Unit::create(){
	Unit *u = new Unit();

	if(u && u->init()){
		u->autorelease();
		return u;
	}
	CC_SAFE_DELETE(u);
	return nullptr;
}
Unit *Unit::create(
	const string &image){

	Unit *u = new Unit();

	if (u && u->init(image)){
		u->autorelease();
		return u;
	}
	CC_SAFE_DELETE(u);
	return nullptr;
}
Unit *Unit::create(
	const string &image, const int part){

	Unit *u = new Unit();

	if (u && u->init(image, part)){
		u->autorelease();
		return u;
	}
	CC_SAFE_DELETE(u);
	return nullptr;
}

bool Unit::init(){
	if (!Sprite::init())
		return false;

	return true;
}

/*
	단일 이미지도 PartedBody로 처리
*/
bool Unit::init(
	const string &image){

	if (!Sprite::init())
		return false;

	body = PartedBody::create(image);
	if (body == nullptr)
		return false;

	if (!initPhysics())
		return false;

	addChild(body);

	return true;
}
bool Unit::init(
	const string &prefix, const int part){

	if(!Sprite::init())
		return false;

	body = PartedBody::create(prefix, part);
	if(body == nullptr)
		return false;

	if(!initPhysics())
		return false;

	addChild(body);

	return true;
}
bool Unit::initPhysics(){
	cocos2d::log("initPhysics : override me");

	return true;
}

void Unit::enableDebug(){
	dbgAngle = 
		LabelTTF::create("", "arial", 30);
	dbgAngle->setColor(Color3B::WHITE);
	
	schedule(
		SEL_SCHEDULE(&Unit::updateDebug), 0.1f);

	addChild(dbgAngle);
}
void Unit::updateDebug(float dt){
	char str[64];
	sprintf(str, "%.0f'",
		body->getRotation());
	dbgAngle->setString(str);
}

PartedBody *Unit::getBody(){
	return body;
}