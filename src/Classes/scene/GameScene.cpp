#include "pch.h"
#include "GameScene.h"

#include <vector>

#include "audio/include/SimpleAudioEngine.h"

#include "common/resource.h"

#include "objects/Ally.h"
#include "objects/Stage.h"
#include "objects/StageLayer.h"
#include "objects/Player.h"
#include "objects/Enemy.h"
#include "objects/EnemySpawner.h"
#include "objects/EffectLayer.h"
#include "objects/Effect.h"
#include "objects/EffectFactory.h"
#include "objects/Trash.h"
#include "objects/TrashPool.h"
#include "objects/RepairArea.h"

#include "ui/cursor.h"
#include "ui/StatusConsole.h"
#include "ui/UserResources.h"
#include "ui/Minimap.h"
#include "ui/SkillIconPanel.h"
#include "ui/UpgradeBar.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

GameScene::GameScene() :
	player(nullptr){
}
GameScene::~GameScene(){
}

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

	auto players = Ally::getInstance(
		Ally::Type::allyPlayer);
	players->push(player);

	enableKeyboardInput(this);
	scheduleUpdate();

	return true;
}
bool GameScene::initUI(){
	auto director = Director::getInstance();
	auto visibleSize = director->getVisibleSize();
	auto origin = director->getVisibleOrigin();

	/* STAGE */
	auto stageLayer = StageLayer::create();
	auto stage = Stage::getInstance(0);

	addChild(stageLayer);

	/* REPAIR AREA */
	auto repairArea = RepairArea::create();
	repairArea->setPosition(200,200);
	stage->addChild(repairArea);

	/* PLAYER */
	player = Player::create("type1.json");
	player->setPosition(
		Vec2(100,100));
	stage->addChild(player, Z::unit);

	auto trashPool = TrashPool::getInstance();
	trashPool->spawn(100);
	addChild(trashPool);

	/* UI OBJECTS */
	auto console = StatusConsole::create();
	console->setPosition(Vec2(50,300));
	addChild(console);

	auto resourcesUI = UserResources::getInstance();
	this->addChild(resourcesUI);

	auto minimap = Minimap::getInstance();
	minimap->setPosition(175,125);
	addChild(minimap);
	//minimap->setVisible(false);

	auto cursor = Cursor::getInstance();
	addChild(cursor);

	int skills[] = {10,11,12,12};
	auto skillPanel = SkillIconPanel::getInstance();
	skillPanel->setSkillList(skills);
	skillPanel->setPosition(500,100);
	addChild(skillPanel);

	auto upgradeBar = UpgradeBar::getInstance();
	upgradeBar->setAnchorPoint(Vec2(0.5,0));
	upgradeBar->setPosition(visibleSize.width/2, visibleSize.height);
	addChild(upgradeBar);

	/* LAYERS */
	addChild(EffectLayer::getInstance());

	return true;
}

void GameScene::onEnter(){
	Layer::onEnter();
	onInitGlobalObjects();

	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic(R::BGM.c_str(), true);
}
void GameScene::onExit(){
	Layer::onExit();
	onReleaseGlobalObjects();

	auto audio = SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();
}

void GameScene::onInitGlobalObjects(){
	/* TODO : 여기에 글로벌 오브젝트들 초기화 처리 */
}
void GameScene::onReleaseGlobalObjects(){
	/* TODO : 여기에 글로벌 오브젝트들 해제 처리 */
}

void GameScene::update(
	float dt){
}