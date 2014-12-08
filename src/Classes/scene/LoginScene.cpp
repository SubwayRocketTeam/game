#include "pch.h"
#include "LoginScene.h"
#include "GameScene.h"
#include "LobbyScene.h"
#include "SelectScene.h"

#include "network/Network.h"

#include "audio/include/SimpleAudioEngine.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;
using namespace CocosDenshion;

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

	auto btnLogin = 
		(ui::Widget*)layout->getChildByName("btn_login");
	auto btnValley = 
		(ui::Widget*)layout->getChildByName("btn_valley");
	auto btnDescription = 
		(ui::Widget*)layout->getChildByName("btn_description");

	btnLogin->addTouchEventListener(
		CC_CALLBACK_2(LoginScene::onLogin, this));
	btnValley->addTouchEventListener(
		CC_CALLBACK_2(LoginScene::onValley, this));
	btnDescription->addTouchEventListener(
		CC_CALLBACK_2(LoginScene::onDescription, this));

	addChild(layout);

	return true;
}

void LoginScene::onLogin(
	Ref *sender, ui::Widget::TouchEventType type){

	if(type != ui::Widget::TouchEventType::ENDED)
		return;

	/* TODO : 입력받은 아이디로 로그인 & 리스폰스 체크 */
	auto network = Network::getInstance();
	network->sendLoginRequest(
		"pjc0247", "asdf1234");

	auto scene = LobbyScene::scene();
	Director::getInstance()
		->pushScene(scene);
}
void LoginScene::onDescription(
	Ref *sender, ui::Widget::TouchEventType type){

	if(type != ui::Widget::TouchEventType::ENDED)
		return;

	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("setsumei_siyou.mp3");

	auto scene = SelectScene::scene();
	Director::getInstance()
		->pushScene(scene);
}
void LoginScene::onValley(
	Ref *sender, ui::Widget::TouchEventType type){

	if(type != ui::Widget::TouchEventType::ENDED)
		return;

	system("explorer \"http://rini.ssut.me/valley/Web.html\"");
}