#include "pch.h"
#include "Player.h"

#include "Trash.h"
#include "TrashPool.h"
#include "PlayerGauge.h"
#include "GlobalResource.h"

#include "Stage.h"
#include "CollisionDetector.h"

#include "shared/JsonLoader.h"

#include "ui/gauge.h"
#include "ui/StatusConsole.h"

#include "common/resource.h"

#include "skill/PassiveSkill.h"
#include "skill/ActiveSkill.h"
#include "skill/SkillPool.h"
#include "skill/id.h"
#include "skill/AttributeName.h"

#include "network/Network.h"

using namespace std;
using namespace cocos2d;

static Player *instance = nullptr;

Player::Player() : 
	speedFactor(1),
	immortal(0), stiff(0){

	allyID = Ally::Type::allyPlayer;
}
Player::~Player(){
}

Player *Player::create(
	const string &dataPath){

	CC_ASSERT(instance == nullptr);

	instance = new Player();
	
	if(instance && instance->init(dataPath)){
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return nullptr;
}
Player *Player::getInstance(){
	CC_ASSERT(instance != nullptr);

	return instance;
}

bool Player::init(
	const string &dataPath){

	if (!Unit::init(R::PlayerBody))
		return false;
	if(!initExternalData(dataPath))
		return false;

	auto gauge = PlayerGauge::create(
		_ATTR(hp), _ATTR_MAX(hp));
	gauge->setPosition(getContentSize()/2);
	addChild(gauge, -1);

	schedule(
		SEL_SCHEDULE(&Player::updateRotation), 0.1f);
	schedule(
		SEL_SCHEDULE(&Player::updateConditions), 1.0f / Global::ups);
	scheduleUpdate();

	return true;
}
bool Player::initAttrs(){
	Unit::initAttrs();

	return true;
}
bool Player::initPhysics(){
	Stage::getInstance(0)->getCollisionDetector()
		->addUnit(this);
//	radius = 30;

	return true;
}
bool Player::initExternalData(
	const string &dataPath){

	Json::Value root;
	if(!JsonLoader::load(dataPath,root))
		return false;

	/* attr */
	auto attrList = root.get("attrs", Json::Value::null);
	if(attrList.isNull())
		return false;

	for(auto attr : attrList){
		auto name = attr.get("name", "").asString();
		float value = attr.get("value", 0).asFloat();

		attrs[name].set(value);
	}

	radius = _ATTR(radius);

	/* skill list */
	auto skillList = root.get("skills", Json::Value::null);
	if(skillList.isNull())
		return false;

	auto pool = SkillPool::getInstance();
	for(auto skill : skillList){
		skills.push_back(
			(ActiveSkill*)pool->get(skill.asInt()));
		cooltimes.push_back(0);
	}

	return true;
}

void Player::update(
	float dt){
		
	/* TODO : 충돌 범위 상수나 이미지 크기 기반으로 하도록 */
	/* TODO : 빨려들어오는건 쓰레기가 직접 오는데,
	 *        청소하는건 플레이어가 청소
	 *        어떻게 할건지 정하기 */
	auto resource = GlobalResource::getInstance();
	auto pos = getPosition();
	auto trashPool = TrashPool::getInstance();
	auto trashes = trashPool->query(
		Rect(pos.x - 20, pos.y - 20, 40, 40));

	/* */
	if(resource->trash < Max::Tank){
		for(auto trash : trashes){
			trash->sweep();
			resource->trash += 1;
		}
	}

	friction = stiff ? 1.f : 0.f;
}
void Player::updateConditions(
	float dt){

	/* cooltime */
	for(float &cooltime : cooltimes){
		if(cooltime > 0.0f)
			cooltime -= dt;
	}

	/* stiff */
	if(stiff > 0.0f)
		stiff -= dt;

	/* IMMORTAL */
	if(immortal > 0.0f)
		immortal -= dt;
}
void Player::updateRotation(
	float dt){

	auto network = Network::getInstance();
	network->sendSyncRotation(
		getRotation());
}

bool Player::onDamage(
	const AttackData& attackData){

	if(immortal > 0.0f)
		return false;

	/* TODO : 무적 기간 상수에 집어넣기 */
	blink();
	immortal = 0.5;
	stiff = MAX(stiff, 0.2);

	auto deltaNorm =
		(getPosition() -
		attackData.object->getPosition())
		.getNormalized();
	/*
	runAction(
		EaseExponentialOut::create(
			MoveBy::create(0.2f, deltaNorm * 70)
		));
	*/
	velocity = deltaNorm * 10;

	return true;
}
bool Player::onDeath(){
	return false;
}
