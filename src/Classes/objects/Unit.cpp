#include "pch.h"
#include "Unit.h"

#include "EffectFactory.h"
#include "Effect.h"

#include "common/resource.h"

#include "skill/SkillPool.h"
#include "skill/ActiveSkill.h"
#include "skill/PassiveSkill.h"

#include "ui/StatusConsole.h"
#include "ui/gauge.h"

#include <map>

using namespace std;
using namespace cocos2d;

static map<int, Unit*> instances;

struct Unit::PassiveData{
	float remaining;
	float update;
	float interval;
};

Unit::Unit()
:friction(0){
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

	//schedule(SEL_SCHEDULE(&Unit::updateGauge), 1.f / Global::fps);
	schedule(SEL_SCHEDULE(&Unit::updatePassives), 1.f / Global::fps);
	schedule(SEL_SCHEDULE(&Unit::updatePhysics), 1.f / Global::fps);

	return true;
}
bool Unit::initAttrs(){
	_INIT_ATTR(hp, 3);
	_INIT_ATTR(mp, 0);
	_INIT_ATTR(speed, 4);
	_INIT_ATTR(hpRegen, 0.0f);
	_INIT_ATTR(mpRegen, 0.0f);
	_INIT_ATTR(defence, 0.0f);
	_INIT_ATTR(gold, 0);

	_ATTR_MAX(gold) = 100;

	return true;
}
bool Unit::initPhysics(){

	return true;
}

void Unit::updateGauge(
	float dt) {

	_ATTR_VALUE(hp) += _ATTR(hpRegen) * dt;
	_ATTR_VALUE(mp) += _ATTR(mpRegen) * dt;
}
void Unit::updatePassives(
	float dt){

	vector<int> removeList;

	for(auto &pair : passives){
		auto id = pair.first;
		auto &data = pair.second;

		data.remaining -= dt;
		data.update -= dt;

		/* 지속 시간이 끝났으면 지우기 */
		if(data.remaining <= 0)
			removeList.push_back(id);
		/* interval마다 update 호출해주기 */
		else if(data.interval != 0){
			if(data.update <= 0){
				auto pool = SkillPool::getInstance();
				auto skill = (PassiveSkill*)pool->get(id);

				skill->update(this, data.remaining);
				data.update = data.interval;
			}
		}
	}

	for(auto id : removeList)
		removePassive(id);
}

void Unit::updatePhysics(
	float dt){
	velocity += acceleration * dt;
	velocity = velocity.getNormalized() * MAX(0, velocity.getLength() - friction * dt);
	setPosition(getPosition() + velocity);
}


void Unit::blink(){
	stopActionByTag(actionBlink);
	runAction(
		Repeat::create(
			Sequence::create(
				FadeTo::create(0.125, 100),
				FadeTo::create(0.125, 255),
				nullptr),
			2))
		->setTag(actionBlink);
}

bool Unit::onDamage(
	const AttackData &attackData){

	return true;
}
bool Unit::onDeath(){
	return true;
}
bool Unit::damage(
	const AttackData& attackData){

	if(onDamage(attackData))
		_ATTR_VALUE(hp) -= MAX(0, attackData.damage - _ATTR(defence));
	
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
	Vec2 pos){

	auto pool = SkillPool::getInstance();
	auto skill = (ActiveSkill*)pool->get(id);

	if (skill)
		skill->use(this, pos);

	return true;
}
void Unit::addPassive(
	int id){

	auto pool = SkillPool::getInstance();
	auto skill = (PassiveSkill*)pool->get(id);

	/* 이미 가지고 있는 패시브 */
	if(passives.find(id) != passives.end())
		return;
	/* TODO : 패시브 중복 적용이면
	          남은 시간 더하기 or 초기화할건지 */
	PassiveData data;
	data.update = data.interval = skill->interval;
	data.remaining = skill->duration;
	passives[id] = data;

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

	CC_ASSERT(passives.find(id) != passives.end());

	passives.erase(id);

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

void Unit::hit() {
	//gauge->setOpacity(255);
	//gauge->runAction(FadeOut::create(0.3f));
}

void Unit::collide(
	cocos2d::Vec2 delta){
	setPosition(getPosition() + delta);
}
