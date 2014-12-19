#include "pch.h"
#include "GameScene.h"

#include <vector>

#include "editor-support/cocostudio/CCSGUIReader.h"
#include "audio/include/SimpleAudioEngine.h"

#include "common/resource.h"
#include "common/PhysicsFactory.h"
#include "common/Preloader.h"

#include "objects/GlobalResource.h"
#include "objects/Ally.h"
#include "objects/Stage.h"
#include "objects/StageLayer.h"
#include "objects/ControlablePlayer.h"
#include "objects/Enemy.h"
#include "objects/EnemySpawner.h"
#include "objects/EnemyFactory.h"
#include "objects/EffectLayer.h"
#include "objects/Effect.h"
#include "objects/EffectFactory.h"
#include "objects/Trash.h"
#include "objects/TrashPool.h"
#include "objects/RepairArea.h"

#include "ui/cursor.h"
#include "ui/StatusConsole.h"
#include "ui/Minimap.h"
#include "ui/SkillIconPanel.h"
#include "ui/UpgradeBar.h"
#include "ui/TrashTank.h"
#include "ui/ChatBox.h"

#include "skill/SkillPool.h"

#include "network/Network.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;
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
	Preloader::getInstance()->push("game_scene");
	onInitGlobalObjects();

	if(!Layer::init())
		return false;
	if(!initUI())
		return false;

	auto players = Ally::getInstance(
		Ally::Type::allyPlayer);
	players->push(player);

	enableKeyboardInput(this);
	scheduleUpdate();

	auto network = Network::getInstance();
	network->sendReady(1);
	printf("ready\n");

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
	player = ControlablePlayer::getInstance();
	player->setPosition(
		Vec2(0,0));
	stage->addChild(player, Z::unit);

	// auto trashPool = TrashPool::getInstance();
	// trashPool->spawn(100);
	// addChild(trashPool);

	/* UI OBJECTS */
	auto console = StatusConsole::create();
	console->setPosition(Vec2(50,300));
	addChild(console);

	auto minimap = Minimap::getInstance();
	minimap->setPosition(860,655);
	addChild(minimap);

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

	auto trashTank = TrashTank::getInstance();
	trashTank->setAnchorPoint(Vec2(0.5,0));
	trashTank->setPosition(visibleSize.width/2, 0);
	addChild(trashTank);

	auto chatBox = ChatBox::getInstance();
	chatBox->setAnchorPoint(Vec2(0,0));
	chatBox->setPosition(0,600);
	addChild(chatBox);

	/* LAYERS */
	addChild(EffectLayer::getInstance());

	return true;
}

void GameScene::onEnter(){
	Layer::onEnter();

	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic(R::BGM.c_str(), true);

	ShowCursor(false);
}
void GameScene::onExit(){
	Layer::onExit();
	Preloader::getInstance()->pop("game_scene");
	onReleaseGlobalObjects();

	auto audio = SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();

	ShowCursor(true);
}

void GameScene::onInitGlobalObjects(){
	/* TODO : 여기에 글로벌 오브젝트들 초기화 처리 */
	GlobalResource::create();
	TrashTank::create();
	TrashPool::create();
	EffectLayer::create();
	EffectFactory::create();
	Minimap::create();
	Stage::create();
	Ally::create();
	StatusConsole::create();
	SkillPool::create();
	EnemyFactory::create();
	PhysicsFactory::create();
	SkillIconPanel::create();
	UpgradeBar::create();
	ControlablePlayer::create("type1.json");
	ChatBox::create();

	/* TODO : 커서 전역에서 쓸수 잇도록 */
	Cursor::create();
}
void GameScene::onReleaseGlobalObjects(){
	/* TODO : 여기에 글로벌 오브젝트들 해제 처리 */
}

void GameScene::update(
	float dt){
}

void GameScene::onKeyboardDown(
	EventKeyboard::KeyCode key){

	/* TODO : 여기좀 정리 */
	if(key == EventKeyboard::KeyCode::KEY_ESCAPE){
		auto reader = GUIReader::getInstance();
		auto layout = reader->widgetFromJsonFile("pause_menu.json");

		auto resume =
			(ui::Widget*)layout->getChildByName("resume");
		resume->addClickEventListener(
			[=](Ref *sender){
				layout->removeFromParentAndCleanup(true);
				Director::getInstance()->resume();
		});

		auto visibleSize = Director::getInstance()->getVisibleSize();
		layout->setPosition(visibleSize/2);
		
		//Stage::getInstance(0)->setVisible(false);
		Stage::getInstance(0)->
			addChild(layout);

		//Director::getInstance()->pause();
	}
}