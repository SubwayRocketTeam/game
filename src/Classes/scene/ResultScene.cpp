#include "pch.h"
#include "ResultScene.h"

#include "network/Network.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;

ResultScene::ResultScene(){
}
ResultScene::~ResultScene(){
}

Scene* ResultScene::scene(){
	auto scene = Scene::create();
	ResultScene *layer = ResultScene::create();
	scene->addChild(layer);
	return scene;
}

bool ResultScene::init(){
	if (!Layer::init())
		return false;

	auto reader = GUIReader::getInstance();
	auto layout = reader->widgetFromJsonFile("result_scene.json");

	addChild(layout);

	return true;
}

void ResultScene::onInitGlobalObjects(){
}
void ResultScene::onReleaseGlobalObjects(){
}