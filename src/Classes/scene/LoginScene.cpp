#include "pch.h"
#include "LoginScene.h"
#include "GameScene.h"
#include "LobbyScene.h"
#include "WaitingScene.h"

#include "network/Network.h"

#include "common\resource.h"

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

	auto nicknamePanel = 
		(ui::Widget*)layout->getChildByName("nickname");
	auto btnLogin = 
		(ui::Widget*)layout->getChildByName("btn_login");
	btnLogin->addTouchEventListener(
		CC_CALLBACK_2(LoginScene::onLogin, this));

	
	nicknamePanel->setCascadeOpacityEnabled(true);
	nicknamePanel->setScaleY(0);
	nicknamePanel->setOpacity(0);
	nicknamePanel->runAction(
		Spawn::create(
			ScaleTo::create(0.6, 1),
			FadeIn::create(0.6),
			nullptr));
	
	btnLogin->setScaleY(0);
	btnLogin->setOpacity(0);
	btnLogin->runAction(
		Sequence::create(
			DelayTime::create(0.6),
			Spawn::create(
				ScaleTo::create(0.4, 1),
				FadeIn::create(0.4),
				nullptr),
			nullptr));

	addChild(layout, 0, tagLayout);

	return true;
}

void LoginScene::onEnter() {
	Layer::onEnter();
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic(R::TitleBGM.c_str(), true);
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

	auto network = Network::getInstance();
	network->sendLoginRequest(nickname.c_str());

	auto scene = WaitingScene::scene();
	Director::getInstance()
		->pushScene(scene);
}