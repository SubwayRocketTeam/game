#include "pch.h"
#include "GameScene.h"

#include <vector>

#include "common/resource.h"
#include "common/Effect.h"
#include "common/EffectFactory.h"

#include "objects/Ally.h"
#include "objects/Stage.h"
#include "objects/Player.h"
#include "objects/Enemy.h"
#include "objects/EnemySpawner.h"
#include "objects/EnemyPool.h"
#include "objects/BodyAnimation.h"
#include "objects/AnimationPool.h"
#include "objects/EffectLayer.h"

#include "ui/cursor.h"
#include "ui/StatusConsole.h"
#include "ui/UserResources.h"
#include "ui/Minimap.h"
#include "ui/SkillIconPanel.h"

using namespace std;
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
	if(!Layer::init())
		return false;
	if(!initUI())
		return false;
	
	auto pool = EnemyPool::create();
	addChild(pool);

	auto animPool = AnimationPool::create();
	addChild(animPool);

	int frames[] = {1, 2, 3, 4, 5, 6};
	vector<int> v(frames, frames+sizeof(frames) / sizeof(int));
	
	animPool->add(
		BodyAnimation::create(R::Run, v, 8), R::Run);

	auto players = Ally::getInstance(
		Ally::Type::allyPlayer);
	players->push(player);

	scheduleUpdate();

	return true;
}
bool GameScene::initUI(){
	auto director = Director::getInstance();
	auto visibleSize = director->getVisibleSize();
	auto origin = director->getVisibleOrigin();

	/* STAGE */
	stage = Stage::getInstance(0);
	stage->setPosition(origin + visibleSize / 2);
	addChild(stage);

	/* PLAYER */
	player = Player::create("type1.json");
	player->setPosition(
		Vec2(100,100));
	stage->addChild(player, 1);

	/* UI OBJECTS */
	auto console = StatusConsole::create();
	console->setPosition(Vec2(50,300));
	addChild(console);

	auto resourcesUI = UserResources::getInstance();
	this->addChild(resourcesUI);

	auto minimap = Minimap::getInstance();
	minimap->setPosition(175,125);
	addChild(minimap);

	cursor = Cursor::getInstance();
	addChild(cursor);

	int skills[] = {10,11,12,12};
	auto skillPanel = SkillIconPanel::getInstance();
	skillPanel->setSkillList(skills);
	skillPanel->setPosition(500,100);
	addChild(skillPanel);

	/* LAYERS */
	addChild(EffectLayer::getInstance());

	return true;
}

void GameScene::update(
	float dt){
}