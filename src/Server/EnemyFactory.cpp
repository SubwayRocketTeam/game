#include "stdafx.h"
#include "EnemyFactory.h"

#include "Unit.h"
#include "Enemy.h"
#include "EnemyExplode.h"
#include "Stage.h"
#include "GameRoom.h"
#include "Ally.h"

#include "shared/skill/SkillPool.h"
#include "shared/skill/id.h"
#include "shared/skill/Attribute.h"
#include "shared/skill/AttributeName.h"
#include "shared/skill/ActiveSkill.h"

#include "shared/JsonLoader.h"
#include "EnemyInfo.h"

static EnemyFactory* instance;

void EnemyFactory::create() {
	instance = new EnemyFactory();
	instance->init();
}

EnemyFactory* EnemyFactory::getInstance() {
	return instance;
}

EnemyFactory::EnemyFactory() {
}

EnemyFactory::~EnemyFactory() {
	for (auto info : dic) {
		SAFE_DELETE(info);
	}
}

Enemy* EnemyFactory::createEnemy(EnemyType type)
{
	Enemy* enemy;
	switch (type) {
	case enemyExplode:
		enemy = new EnemyExplode();
		break;
	default:
		enemy = new Enemy();
		break;
	}
	enemy->setInfo(dic[type]);
	return enemy;
}

bool EnemyFactory::init() {

	if (!initExternalData("enemy_list.json")) {
		return false;
	}

	return true;
}

bool EnemyFactory::initExternalData(const std::string &dataPath) {

	Json::Value root;
	if (!JsonLoader::load(dataPath, root)) {
		return false;
	}

	auto enemyList = root.get("enemyList", Json::Value::null);
	if (enemyList.isNull()) {
		return false;
	}

	for (auto info : enemyList) {
		EnemyInfo *skeleton = new EnemyInfo();

		skeleton->name = info.get("name", "").asString();

		auto attrList = info.get("attrs", Json::Value::null);
		if (attrList.isNull()) {
			return false;
		}

		for (auto attr : attrList) {
			auto name = attr.get("name", "").asString();
			auto value = attr.get("value", 0).asFloat();

			skeleton->attrs[name].set(value);
		}

		auto skillList = info.get("skills", Json::Value::null);
		if (skillList.isNull()) {
			return false;
		}

		auto pool = SkillPool::getInstance();
		for (auto skillId : skillList) {
			skeleton->skills.push_back((ActiveSkill*)pool->get(skillId.asInt()));
		}

		auto pay = info.get("pay", 0).asInt();
		skeleton->pay = pay;
		dic.push_back(skeleton);
	}

	return true;
}