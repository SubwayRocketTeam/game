#include "pch.h"
#include "Unit.h"

#include "common/EffectFactory.h"
#include "common/Effect.h"
#include "common/resource.h"

#include "skill/SkillPool.h"
#include "skill/ActiveSkill.h"
#include "skill/PassiveSkill.h"

#include "ui/StatusConsole.h"

#include "PartedBody.h"
#include "ui/gauge.h"

#include <map>

using namespace std;
using namespace cocos2d;

static map<int, Unit*> instances;

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
Unit *Unit::getInstanceByID(
	int id){

	CC_ASSERT(instances.find(id) != instances.end());

	return instances[id];
}

bool Unit::init(){
	if (!Sprite::init())
		return false;

	return true;
}

bool Unit::init(
	const string &imageName, const int part){

	char path[128];
	sprintf(path, "%s.png", imageName.c_str());

	if(!Sprite::initWithFile(path))
		return false;

	if(!initPhysics())
		return false;
	if(!initAttrs())
		return false;

	//gauge = Gauge::create(this);
	//addChild(gauge);

	schedule(SEL_SCHEDULE(&Unit::updateGauge), 1.f / Global::fps);

	return true;
}
bool Unit::initAttrs(){
	_INIT_ATTR(hp, 3);
	_INIT_ATTR(mp, 0);
	_INIT_ATTR(speed, 4);
	_INIT_ATTR(hpRegen, 0.0f);
	_INIT_ATTR(mpRegen, 0.0f);

	return true;
}
bool Unit::initPhysics(){

	return true;
}

void Unit::onDamage(
	const AttackData &attackData){
}
bool Unit::onDeath(){
	return true;
}

void Unit::updateGauge(float dt) {
	_ATTR_VALUE(hp) += _ATTR(hpRegen) * dt;
	_ATTR_VALUE(mp) += _ATTR(mpRegen) * dt;
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
	
	_ATTR_VALUE(hp) -= (attackData.damage - _ATTR(defence));

	onDamage(attackData);

	if (_ATTR(hp) <= 0) {
		if(onDeath()){
			removeFromParentAndCleanup(true);
			return true;
		}
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

void Unit::setID(
	int _id){
	id = _id;
}
int Unit::getID(){
	return id;
}
Attribute &Unit::getAttribute(
	const string &name){
	
	CC_ASSERT(attrs.find(name) != attrs.end());

	return attrs[name];
}
Ally::Type Unit::getAllyID(){
	return allyID;
}