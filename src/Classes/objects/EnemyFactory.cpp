#include "pch.h"
#include "EnemyFactory.h"

#include "Enemy.h"

#include "skill/SkillPool.h"
#include "skill/id.h"

#include "common/JsonLoader.h"

#include "objects/enemyInfo.h"

USING_NS_CC;

static EnemyFactory* instance = nullptr;

EnemyFactory::EnemyFactory() {

}

EnemyFactory::~EnemyFactory() {

}

EnemyFactory* EnemyFactory::create() {
	if (!instance) {
		instance = new EnemyFactory();
		instance->init();
	}
	
	return instance;
}

EnemyFactory* EnemyFactory::getInstance() {
	return instance;
}

Enemy* EnemyFactory::createEnemy(EnemyType type)
{
	Enemy* enemy = Enemy::create();
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

		dic.push_back(skeleton);
	}

	return true;
}