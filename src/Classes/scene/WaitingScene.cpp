#include "pch.h"
#include "WaitingScene.h"

#include "network/Network.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;

WaitingScene::WaitingScene(){
}
WaitingScene::~WaitingScene(){
}

Scene* WaitingScene::scene(){
	auto scene = Scene::create();
	WaitingScene *layer = WaitingScene::create();
	scene->addChild(layer);
	return scene;
}

bool WaitingScene::init(){
	if (!Layer::init())
		return false;

	auto reader = GUIReader::getInstance();
	auto layout = reader->widgetFromJsonFile("waiting_scene.json");

	addChild(layout);

	//onInitGlobalObjects();

	auto network = Network::getInstance();
	network->sendEnterRoom(0);

	return true;
}

void WaitingScene::onInitGlobalObjects(){
}
void WaitingScene::onReleaseGlobalObjects(){
}