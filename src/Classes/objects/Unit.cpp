﻿#include "pch.h"
#include "Unit.h"

#include "skill/AttributeName.h"
#include "skill/SkillPool.h"
#include "skill/ActiveSkill.h"
#include "skill/PassiveSkill.h"

#include "ui/StatusConsole.h"

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
	const string &imageName, const int part){

	if(!Sprite::init())
		return false;

	body = PartedBody::create(imageName, part);
	if(body == nullptr)
		return false;

	if(!initPhysics())
		return false;
	if(!initAttrs())
		return false;

	addChild(body);

	return true;
}
bool Unit::initAttrs(){
	_SET_ATTR(hp, 3);
	_SET_ATTR(speed, 4);

	return true;
}
bool Unit::initPhysics(){
	cocos2d::log("initPhysics : override me");

	return true;
}

bool Unit::damage(
	const AttackData& attackData){

	Vec2 power = getPosition() - attackData.startPostion;
	power.normalize();
	power *= 1000000;
	// getPhysicsBody()->applyImpulse(power);
	
	float hp = _ATTR(hp);
	hp = hp - (attackData.damage - _ATTR(defence));
	_SET_ATTR(hp, hp);
	// TODO: 사망하는 로직 위치 적당한 곳 찾아서 이동
	if (hp <= 0) {
		removeFromParentAndCleanup(true);
		return true;
	}
	return false;

}

bool Unit::useSkill(
	int id,
	float x,float y){

	auto pool = SkillPool::getInstance();
	auto skill = (ActiveSkill*)pool->get(id);

	skill->use(this, Vec2(x,y));

	return true;
}
void Unit::addPassive(
	int id){

	auto console = StatusConsole::getInstance();
	auto pool = SkillPool::getInstance();
	auto skill = (PassiveSkill*)pool->get(id);

	for(auto pair : skill->bonusList){
		string name = pair.first;
		Attribute attr = pair.second;
		Attribute &target = attrs[name];

		target.getBonusValue() += attr.getBonusValue();
		target.getBonusRate() += attr.getBonusRate();
	}

	char msg[256];
	sprintf(msg, "passive enabled - %d", id);
	console->output(msg);

	for(auto pair : skill->bonusList){
		sprintf(msg, "name : %s / value : %.0f / rate : %.0f",
			pair.first.c_str(), pair.second.getBonusValue(), pair.second.getBonusRate());
		console->output(msg);
	}
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
Attribute &Unit::getAttribute(
	const string &name){
	
	CC_ASSERT(attrs.find(name) != attrs.end());

	return attrs[name];
}
Ally::Type Unit::getAllyID(){
	return allyID;
}