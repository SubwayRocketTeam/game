#include "pch.h"
#include "LoginScene.h"
#include "GameScene.h"
#include "LobbyScene.h"
#include "WaitingScene.h"

#include "network/Network.h"

#include "audio/include/SimpleAudioEngine.h"

#include "ui/UITextField.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;
using namespace CocosDenshion;

static const int tagLayout = 1;

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
	btnLogin->addTouchEventListener(
		CC_CALLBACK_2(LoginScene::onLogin, this));
		
	addChild(layout, 0, tagLayout);

	return true;
}

void LoginScene::onLogin(
	Ref *sender, ui::Widget::TouchEventType type){

	if(type != ui::Widget::TouchEventType::ENDED)
		return;
	auto layout = getChildByTag(tagLayout);
	auto nicknamePanel =
		(ui::Widget*)layout->getChildByName("nickname");
	auto textNickname =
		(ui::TextField*)nicknamePanel->getChildByName("tf");
	if (textNickname->getStringLength() < 0)
		return;
	std::string nickname = textNickname->getString();

	/* TODO : 입력받은 아이디로 로그인 & 리스폰스 체크 */
	auto network = Network::getInstance();
	network->sendLoginRequest(nickname.c_str());

	auto scene = WaitingScene::scene();
	Director::getInstance()
		->pushScene(scene);
}