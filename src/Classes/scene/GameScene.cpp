#include "pch.h"
#include "GameScene.h"

#include "common\resource.h"

#include "objects/Stage.h"
#include "objects/Player.h"
#include "objects/Enemy.h"
#include "objects/EnemySpawner.h"
#include "objects/EnemyPool.h"
#include "objects/BodyAnimation.h"
#include "objects/AnimationPool.h"

#include "ui/cursor.h"
#include "ui/StatusConsole.h"

using namespace cocos2d;

Scene* GameScene::scene(){
	auto scene = Scene::createWithPhysics();
	auto world = scene->getPhysicsWorld();

	world->setDebugDrawMask(
		PhysicsWorld::DEBUGDRAW_NONE);
	world->setGravity(Vec2(0,0));

	GameScene *layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init(){
	if (!Layer::init())
		return false;

	auto director = Director::getInstance();
	auto visibleSize = director->getVisibleSize();
	auto origin = director->getVisibleOrigin();

	stage = Stage::create();
	stage->setPosition(origin + visibleSize / 2);
	addChild(stage);

	auto pool = EnemyPool::create();
	addChild(pool);

	auto animPool = AnimationPool::create();
	addChild(animPool);
	animPool->add(BodyAnimation::create(R::Run, {1, 2, 3, 4, 5, 6}, 8), R::Run);

	player = Player::create("type1.json");

	player->setPosition(
		Vec2(100,100));
	stage->addChild(player, 1);

	cursor = Cursor::getInstance();
	addChild(cursor);

	auto console = StatusConsole::create();
	console->setPosition(Vec2(50,0));
	addChild(console);

	scheduleUpdate();

	return true;
}

void GameScene::update(
	float dt){
}