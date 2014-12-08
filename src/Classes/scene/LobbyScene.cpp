#include "pch.h"
#include "LobbyScene.h"
#include "GameScene.h"

#include "common/PhysicsFactory.h"

#include "objects/GlobalResource.h"
#include "objects/Ally.h"
#include "objects/Stage.h"
#include "objects/StageLayer.h"
#include "objects/Player.h"
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

#include "audio/include/SimpleAudioEngine.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;
using namespace CocosDenshion;

LobbyScene::LobbyScene(){
}
LobbyScene::~LobbyScene(){
}

Scene* LobbyScene::scene(){
	auto scene = Scene::create();
	LobbyScene *layer = LobbyScene::create();
	scene->addChild(layer);
	return scene;
}

bool LobbyScene::init(){
	if(!Layer::init())
		return false;
	
	auto reader = GUIReader::getInstance();
	auto layout = reader->widgetFromJsonFile("lobby_scene.json");

	addChild(layout);

	auto network = Network::getInstance();
	network->sendEnterRoom();

	onInitGlobalObjects();

	return true;
}

void LobbyScene::onInitGlobalObjects(){
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
	Player::create("type1.json");
	ChatBox::create();

	/* TODO : 커서 전역에서 쓸수 잇도록 */
	Cursor::create();
}
void LobbyScene::onReleaseGlobalObjects(){
}