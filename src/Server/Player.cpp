#include "stdafx.h"
#include "Player.h"

#include "Bullet.h"
#include "Trash.h"
#include "TrashPool.h"
#include "EnemyFactory.h"
#include "Ally.h"
#include "AttackData.h"

#include "Stage.h"
#include "CollisionDetector.h"

#include "shared/JsonLoader.h"

#include "common/resource.h"
#include "common/max.h"

#include "shared/skill/PassiveSkill.h"
#include "shared/skill/ActiveSkill.h"
#include "shared/skill/SkillPool.h"
#include "shared/skill/id.h"
#include "shared/skill/AttributeName.h"


Player::Player()
	:speedFactor(1), immortal(0), stiff(0), trash(0){
	type = UT_PLAYER;
	ally = Ally::Type::allyPlayer;
}
Player::~Player(){
}

bool Player::init(
	const std::string &dataPath){

	if (!Unit::init())
		return false;
	if (!initExternalData(dataPath))
		return false;

	return true;
}
bool Player::initAttrs(){
	Unit::initAttrs();
	return true;
}
bool Player::initPhysics(){
	radius = 30;
	return true;
}
bool Player::initExternalData(
	const std::string &dataPath){

	Json::Value root;
	if (!JsonLoader::load(dataPath, root))
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

	/* incr */
	auto incrList = root.get("incrs", Json::Value::null);
	if (incrList.isNull())
		return false;

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

bool Player::useSkill(
	SKillIndex index,
	float x, float y){

	auto skill = skills[index];
	float cooltime = skill->cooltime;

	if (cooltimes[index] > 0.0f)
		return false;
	if (skill->cost > _ATTR(mp))
		return false;
	if (index == skillMouseLeft)
		cooltime *= _ATTR(attackSpeed);

	skill->use(this, Vec2(x, y));

	cooltimes[index] = cooltime;
	_ATTR_VALUE(mp) -= skill->cost;
	stiff = skill->duration;

	return true;
}

void Player::update(
	float dt){
	updateConditions(dt);

	if (!stiff) {
		position += moveDirection * _ATTR(speed);
	}

	Unit::update(dt);

	/* TODO : 충돌 범위 상수나 이미지 크기 기반으로 하도록 */
	/* TODO : 빨려들어오는건 쓰레기가 직접 오는데,
	*        청소하는건 플레이어가 청소
	*        어떻게 할건지 정하기 */
	auto pos = position;
	auto trashPool = stage->trashPool;
	auto trashes = trashPool->query(
		pos.x - 20, pos.y - 20, 40, 40);

	/* */
	for (auto trash : trashes){
		if (isTankFull())
			break;
		stage->removeUnit(trash);
		trash += 1;
	}

}

void Player::updatePhysics(float dt){
	friction = stiff ? 1.f : 0.f;
	Unit::updatePhysics(dt);
}

void Player::updateConditions(
	float dt){

	/* cooltime */
	for (float &cooltime : cooltimes){
		if (cooltime > 0.0f)
			cooltime -= dt;
	}

	/* stiff */
	if (stiff > 0.0f)
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
	immortal = 0.5;
	stiff = max(stiff, 0.2f);

	auto deltaNorm =
		(position - attackData.object->position).getNormalized();

	velocity = deltaNorm * 10;

	return true;
}
bool Player::onDeath(){
	return false;
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
