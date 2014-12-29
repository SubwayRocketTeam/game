#include "pch.h"
#include "EnemyFactory.h"

#include "Enemy.h"
#include "EnemyExplode.h"
#include "EnemyDup.h"
#include "Stage.h"
#include "Ally.h"

#include "skill/SkillPool.h"
#include "skill/id.h"

#include "shared/JsonLoader.h"

#include "objects/enemyInfo.h"

using namespace cocos2d;

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

Enemy* EnemyFactory::createEnemy(int stage, EnemyType type)
{
	Enemy* enemy;
	switch (type) {
	case enemyExplode:
		enemy = EnemyExplode::create(stage);
		break;
	case enemyDup:
		enemy = EnemyDup::create(stage);
		break;
	default:
		enemy = Enemy::create(stage, type);
		break;
	}
	enemy->setInfo(dic[type]);
	return enemy;
}

void EnemyFactory::spawn(EnemyType type) {
	auto stage = Stage::getInstance(0);
	auto stageSize = stage->getContentSize();
	auto ally = Stage::getInstance(0)->getAlly(
		Ally::Type::allyEnemy);
	auto factory = EnemyFactory::getInstance();

	Enemy *e = factory->createEnemy(0, type);
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

		skeleton->cost = info.get("cost", 0).asInt();
		skeleton->cooltime = info.get("cooltime", 0).asFloat();

		dic.push_back(skeleton);
	}

	return true;
}

EnemyInfo* EnemyFactory::getEenmyInfo(
	EnemyType type) {
	return dic[type];
}
