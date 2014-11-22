#include "pch.h"
#include "LoginScene.h"

#include "editor-support/cocostudio/CCSGUIReader.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;

LoginScene::LoginScene(){
}
LoginScene::~LoginScene(){
}

Scene* LoginScene::scene(){
	auto scene = Scene::create();
	LoginScene *layer = LoginScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoginScene::init(){
	if(!Layer::init())
		return false;
	
	auto reader = GUIReader::getInstance();
	auto layout = reader->widgetFromJsonFile("login_scene.json");

	addChild(layout);

	return true;
}