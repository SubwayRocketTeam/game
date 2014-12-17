#include "pch.h"
#include "Player.h"

#include "Enemy.h"
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

Player::Player() : 
	speedFactor(1),
	immortal(0), stiff(0){

	allyID = Ally::Type::allyPlayer;
}
Player::~Player(){
}

Player *Player::create(
	const string &dataPath){
	Player* player = new Player();
	
	if(player && player->init(dataPath)){
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
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

	/* max_attr */
	attrList = root.get("max_attrs", Json::Value::null);
	if (attrList.isNull())
		return false;

	for (auto attr : attrList){
		auto name = attr.get("name", "").asString();
		float value = attr.get("value", 0).asFloat();

		maxAttrs[name] = value;
	}

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

	/* 서버에서 먹여줌 */
	/*
	if(resource->trash < Max::Tank){
		for(auto trash : trashes){
			trash->sweep();
			resource->trash += 1;
		}
	}
	*/
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

void Player::updatePhysics(
	float dt) {
	friction = stiff > 0.f ? 1000.f : 0.f;
	Unit::updatePhysics(dt);
}

bool Player::onDamage(
	const AttackData& attackData){

	if(immortal > 0.0f)
		return false;

	/* TODO : 무적 기간 상수에 집어넣기 */
	blink();
	immortal = 0.5;
	stiff = MAX(stiff, 0.2f);

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
	velocity = deltaNorm * 300.f;

	return true;
}
bool Player::onDeath(){
	/*
	auto ally = Ally::getInstance(Ally::Type::allyPlayer);
	if (std::find(ally->begin(), ally->end(), this) != ally->end()) {
		auto enemy_ally = Ally::getInstance(Ally::Type::allyEnemy);
		for (auto unit : *enemy_ally) {
			Enemy* enemy = (Enemy*)unit;
			enemy->removeAggro(this);
		}
	}
	*/
	return false;
}
