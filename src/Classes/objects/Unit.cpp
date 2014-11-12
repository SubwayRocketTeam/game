#include "pch.h"
#include "Unit.h"

#include "common/EffectFactory.h"
#include "common/Effect.h"
#include "common/resource.h"

#include "skill/AttributeName.h"
#include "skill/SkillPool.h"
#include "skill/ActiveSkill.h"
#include "skill/PassiveSkill.h"

#include "ui/StatusConsole.h"

#include "PartedBody.h"
#include "ui/gauge.h"

using namespace std;
using namespace cocos2d;

Unit::Unit() : 
	body(nullptr),
	dbgAngle(nullptr){
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

	gauge = Gauge::create(this);
	addChild(gauge);

	addChild(body);

	return true;
}
bool Unit::initAttrs(){
	_SET_ATTR(hp, 3);
	_SET_ATTR(mp, 0);
	_SET_ATTR(speed, 4);
	_SET_ATTR(hpRegen, 0.0f);
	_SET_ATTR(mpRegen, 0.0f);

	return true;
}
bool Unit::initPhysics(){
	cocos2d::log("initPhysics : override me");

	return true;
}

bool Unit::death(){
	removeFromParentAndCleanup(true);

	return true;
}

void Unit::updateGauge(float dt) {
	attrs["hp"].getValue() += attrs["hp_regen"].get() * dt;
	attrs["mp"].getValue() += attrs["mp_regen"].get() * dt;
}

bool Unit::damage(
	const AttackData& attackData){

	auto factory = EffectFactory::getInstance();
	auto worldPos = getParent()->convertToWorldSpace(getPosition());

	factory->add(
		worldPos, R::Hit1, false);

	Vec2 power = getPosition() - attackData.startPostion;
	power.normalize();
	power *= 100000;
	getPhysicsBody()->applyImpulse(power);
	
	attrs["hp"].getValue() -= (attackData.damage - _ATTR(defence));

	
	if (attrs["hp"].get() <= 0) {
		return death();
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

	auto pool = SkillPool::getInstance();
	auto skill = (PassiveSkill*)pool->get(id);

	/* 이미 가지고 있는 패시브 */
	if(passives.find(skill) != passives.end())
		return;
	passives.insert(skill);

	for(auto pair : skill->bonusList){
		string name = pair.first;
		Attribute attr = pair.second;
		Attribute &target = attrs[name];

		target.getBonusValue() += attr.getBonusValue();
		target.getBonusRate() += attr.getBonusRate();
	}

	/* 디버그용 콘솔 출력 */
	auto console = StatusConsole::getInstance();
	char msg[256];

	sprintf(msg, "passive enabled - %d", id);
	console->output(msg);

	for(auto pair : skill->bonusList){
		sprintf(msg, "name : %s / value : %.0f / rate : %.0f",
			pair.first.c_str(), pair.second.getBonusValue(), pair.second.getBonusRate());
		console->output(msg);
	}
}
void Unit::removePassive(
	int id){

	auto pool = SkillPool::getInstance();
	auto skill = (PassiveSkill*)pool->get(id);

	CC_ASSERT(passives.find(skill) != passives.end());

	passives.erase(skill);

	for(auto pair : skill->bonusList){
		string name = pair.first;
		Attribute attr = pair.second;
		Attribute &target = attrs[name];

		target.getBonusValue() -= attr.getBonusValue();
		target.getBonusRate() -= attr.getBonusRate();
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