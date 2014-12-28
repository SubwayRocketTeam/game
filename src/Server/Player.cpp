#include "stdafx.h"
#include "Player.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Trash.h"
#include "TrashPool.h"
#include "EnemyFactory.h"
#include "Ally.h"
#include "AttackData.h"

#include "Stage.h"
#include "GameRoom.h"
#include "CollisionDetector.h"

#include "PacketType.h"

#include "shared/JsonLoader.h"

#include "common/resource.h"
#include "common/max.h"

#include "shared/skill/PassiveSkill.h"
#include "shared/skill/ActiveSkill.h"
#include "shared/skill/SkillPool.h"
#include "shared/skill/id.h"
#include "shared/skill/AttributeName.h"

#include "config.h"

Player::Player()
	:speedFactor(1), immortal(0), stiff(0)
	, trash(0), upgradeCost(config::upgrade_cost_start){
	type = UT_PLAYER;
	ally = Ally::Type::allyPlayer;
}
Player::~Player(){
}

bool Player::init(
	const int player_type){

	if (!Unit::init())
		return false;
	if (!initExternalData(player_type))
		return false;

	return true;
}
bool Player::initAttrs(){
	Unit::initAttrs();
	return true;
}
bool Player::initPhysics(){
	return true;
}
bool Player::initExternalData(
	const int player_type){

	char buf[32];
	sprintf_s(buf, "type%d.json", player_type);

	Json::Value root;
	if (!JsonLoader::load(buf, root))
		return false;

	/* attr */
	auto attrList = root.get("attrs", Json::Value::null);
	if (attrList.isNull())
		return false;

	for (auto attr : attrList){
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
	if (skillList.isNull())
		return false;

	auto pool = SkillPool::getInstance();
	for (auto skill : skillList){
		skills.push_back(
			(ActiveSkill*)pool->get(skill.asInt()));
		cooltimes.push_back(0);
	}

	return true;
}

void Player::update(
	float dt){
	updateConditions(dt);

	if (stiff <= 0.f) {
		position += moveDirection * _ATTR(speed) * dt;
	}

	Unit::update(dt);
}

void Player::updateConditions(
	float dt){

	/* cooltime */
	for (float &cooltime : cooltimes){
		if (cooltime > 0.0f)
			cooltime -= dt;
	}

	/* stiff */
	if (stiff > 0.f)
		stiff -= dt;

	/* IMMORTAL */
	if (immortal > 0.0f)
		immortal -= dt;
}

bool Player::onDamage(
	const AttackData& attackData){

	if (immortal > 0.0f)
		return false;

	/* TODO : 무적 기간 상수에 집어넣기 */
	immortal = 1.f;
	stiff = max(stiff, 0.5f);

	auto deltaNorm =
		(position - attackData.position).getNormalized();

	// 중간과정 없이 바로 위치 변경
//	velocity = deltaNorm * 30.f * 60.f;
	position += deltaNorm * 100.f;

	Attack noti;
	noti.attacker_id = attackData.user->id;
	noti.target_id = id;
	noti.knockback_x = position.x;
	noti.knockback_y = position.y;
	noti.attack_position_x = attackData.position.x;
	noti.attack_position_y = attackData.position.y;
	noti.damage = attackData.damage;
	noti.aggro = attackData.aggro;
	
	stage->gameroom->sendPacket(noti);

	return true;
}
bool Player::onDeath(){
	auto ally = stage->ally[Ally::Type::allyPlayer];
	if (std::find(ally->begin(), ally->end(), this) != ally->end()) {
		auto enemy_ally = stage->ally[Ally::Type::allyEnemy];
		for (auto unit : *enemy_ally) {
			Enemy* enemy = (Enemy*)unit;
			enemy->removeAggro(this);
		}
	}

	int upgrade_times = 0;
	for (auto& pair : upgradeTimes)
		upgrade_times += pair.second;

	stage->trashPool->spawn(
		position, trash + upgrade_times * config::death_upgrade_trash);
	trash = 0;

	return true;
}

bool Player::isTankFull() const {
	return trash >= Max::Tank;
}

int Player::getTrash() const {
	return trash;
}

void Player::addTrash(const int amount) {
	trash = max(0, min(Max::Tank, trash + amount));
}

bool Player::upgrade(
	const std::string& attr_name) {

	if (trash < upgradeCost)
		return false;

	auto it = maxAttrs.find(attr_name);
	if (it == maxAttrs.end())
		return false;

	float attr_max = it->second;

	auto& attr = getAttribute(attr_name);
	upgradeTimes[attr_name] += 1;
	attr.getBonusValue() = (attr_max - attr.getValue()) / Max::Upgrade * upgradeTimes[attr_name];

	trash -= upgradeCost;
	upgradeCost = min(Max::Tank, upgradeCost + config::upgrade_cost_delta);

	return true;
}
