#include "pch.h"
#include "EnemyFactory.h"

#include "Enemy.h"
#include "Enemy.h"
#include "Stage.h"
#include "Ally.h"

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
	enemy->setInfo(instance->dic[type]);
	return enemy;
}

void EnemyFactory::spawn(EnemyType type) {
	auto stage = Stage::getInstance(0);
	auto stageSize = stage->getContentSize();
	auto ally = Ally::getInstance(
		Ally::Type::allyEnemy);
	auto factory = EnemyFactory::getInstance();

	Enemy *e = factory->createEnemy(type);
	e->setPosition(
		rand()%(int)stageSize.width - stageSize.width/2,
		rand()%(int)stageSize.height - stageSize.height/2);
	e->resetAggro();

	ally->push(e);
	stage->addChild(e, Z::unit);
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