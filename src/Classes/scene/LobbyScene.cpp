#include "pch.h"
#include "LobbyScene.h"
#include "GameScene.h"

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

	return true;
}