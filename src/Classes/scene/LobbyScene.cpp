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
#include "ui/SpawnIconPanel.h"
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

	//onInitGlobalObjects();

	auto network = Network::getInstance();
	network->sendEnterRoom();

	return true;
}

void LobbyScene::onInitGlobalObjects(){
}
void LobbyScene::onReleaseGlobalObjects(){
}