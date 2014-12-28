#include "pch.h"
#include "RoomScene.h"

#include "network/Network.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;

RoomScene::RoomScene(){
}
RoomScene::~RoomScene(){
}

Scene* RoomScene::scene(){
	auto scene = Scene::create();
	RoomScene *layer = RoomScene::create();
	scene->addChild(layer);
	return scene;
}

bool RoomScene::init(){
	if (!Layer::init())
		return false;

	auto reader = GUIReader::getInstance();
	auto layout = reader->widgetFromJsonFile("room_scene.json");

	addChild(layout);

	//onInitGlobalObjects();

	auto network = Network::getInstance();
	network->sendEnterRoom();

	return true;
}

void RoomScene::onInitGlobalObjects(){
}
void RoomScene::onReleaseGlobalObjects(){
}