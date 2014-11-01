#include "GameScene.h"
#include "AppMacros.h"

#include "objects/Stage.h"
#include "objects/Player.h"
#include "objects/Enemy.h"
#include "objects/EnemySpawner.h"
#include "objects/EnemyPool.h"

#include "ui/cursor.h"

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
	auto spawner = EnemySpawner::create();

	addChild(pool);
	addChild(spawner);

	player = Player::create();

	player->setPosition(
		Vec2(100,100));
	stage->addChild(player);

	cursor = Cursor::getInstance("bang.png");
	this->addChild(cursor);

	scheduleUpdate();

    return true;
}

void GameScene::update(
	float dt){
	cursor->update(dt);
}