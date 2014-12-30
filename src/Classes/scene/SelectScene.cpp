#include "pch.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "LobbyScene.h"

#include "network\GameRoom.h"
#include "network\Network.h"

#include "ext/uiProgressTo.h"

#include "ui/UILoadingBar.h"
#include "ui/UIText.h"

#include "shared/JsonLoader.h"

#include "shared/skill/AttributeName.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;

static int layoutTag = 1;

SelectScene::SelectScene(){
}
SelectScene::~SelectScene(){
}

Scene* SelectScene::scene(){
	auto scene = Scene::create();
	SelectScene *layer = SelectScene::create();
	scene->addChild(layer);
	return scene;
}

bool SelectScene::init(){
	if(!Layer::init())
		return false;
	
	auto reader = GUIReader::getInstance();
	auto layout = reader->widgetFromJsonFile("select_scene.json");

	addChild(layout, 0, layoutTag);

	auto gameroom = GameRoom::getInstance();
	auto room_text = (ui::Text*)((ui::Widget*)layout->getChildByName("pn_room_no"))
		->getChildByName("label");
	room_text->setString(_MAKE_PATH("Room #%d", gameroom->getRoomId()));

	onSelectRobot(nullptr, ui::Widget::TouchEventType::ENDED
		, gameroom->getClient(gameroom->getMyId()).robot);

	((ui::Widget*)layout->getChildByName("btn_ready"))
		->addTouchEventListener(CC_CALLBACK_2(SelectScene::onReady, this));
	((ui::Widget*)layout->getChildByName("btn_exit"))
		->addTouchEventListener(CC_CALLBACK_2(SelectScene::onExitRoom, this));

	((ui::Widget*)layout->getChildByName("pn_team1"))
		->addTouchEventListener(CC_CALLBACK_2(SelectScene::onSelectTeam, this, 0));
	((ui::Widget*)layout->getChildByName("pn_team2"))
		->addTouchEventListener(CC_CALLBACK_2(SelectScene::onSelectTeam, this, 1));

	auto robots = layout->getChildByName("pn_robot");

	for(auto robot : robots->getChildren()){
		((ui::Widget*)robot)
			->addTouchEventListener(CC_CALLBACK_2(SelectScene::onSelectRobot, this, robot->getTag()));
	}


	return true;
}

void SelectScene::onSelectRobot(
	Ref *sender, ui::Widget::TouchEventType type, int robot) {
	if (type != ui::Widget::TouchEventType::ENDED)
		return;

	auto gameroom = GameRoom::getInstance();
	if (gameroom->getClient(gameroom->getMyId()).robot == robot)
		return;

	Network::getInstance()->sendSelectRobot(robot);

	auto layout = getChildByTag(layoutTag);
	auto robots = layout->getChildByName("pn_robot");

	robots->getChildByTag(robot)->runAction(
		Sequence::create(
		ScaleTo::create(0.23 / 2, 1.1, 0.95),
		ScaleTo::create(0.17 / 2, 0.9, 1.1),
		ScaleTo::create(0.15 / 2, 1.05, 0.95),
		ScaleTo::create(0.08 / 2, 1, 1),
		nullptr
		));

	auto infos = layout->getChildByName("pn_info");
	auto pbHp = (ui::LoadingBar*)infos->getChildByName("hp")->getChildByName("pb");
	auto pbAttack = (ui::LoadingBar*)infos->getChildByName("attack")->getChildByName("pb");
	auto pbSpeed = (ui::LoadingBar*)infos->getChildByName("speed")->getChildByName("pb");
	auto pbRange = (ui::LoadingBar*)infos->getChildByName("range")->getChildByName("pb");

	Json::Value root;
	if (!JsonLoader::load(_MAKE_PATH("type%d.json", robot), root))
		return;

	auto attrList = root.get("attrs", Json::Value::null);
	if (attrList.isNull())
		return;

	for (auto attr : attrList){
		auto name = attr.get("name", "").asString();
		float value = attr.get("value", 0).asFloat();

		if (name == Attr::hp) {
			pbHp->runAction(EaseElasticOut::create(UiProgressTo::create(0.6, value/100.f*100.f)));
		}
		else if (name == Attr::attack) {
			pbAttack->runAction(EaseElasticOut::create(UiProgressTo::create(0.6, value / 20.f*100.f)));
		}
		else if (name == Attr::speed) {
			pbSpeed->runAction(EaseElasticOut::create(UiProgressTo::create(0.6, value / 600.f*100.f)));
		}
		else if (name == Attr::range) {
			pbRange->runAction(EaseElasticOut::create(UiProgressTo::create(0.6, value / 2000.f*100.f)));
		}
	}
}
void SelectScene::onSelectTeam(
	Ref *sender, ui::Widget::TouchEventType type, int team) {
	if (type != ui::Widget::TouchEventType::ENDED)
		return;

	auto gameroom = GameRoom::getInstance();
	if (gameroom->getClient(gameroom->getMyId()).team != team)
		Network::getInstance()->sendSelectTeam(team);
}
void SelectScene::onReady(
	Ref *sender, ui::Widget::TouchEventType type) {
	if (type != ui::Widget::TouchEventType::ENDED)
		return;

	auto gameroom = GameRoom::getInstance();
	Network::getInstance()->sendReadyRequest(!gameroom->getClient(gameroom->getMyId()).ready);
}
void SelectScene::onExitRoom(
	Ref *sender, ui::Widget::TouchEventType type) {
	if (type != ui::Widget::TouchEventType::ENDED)
		return;

	Network::getInstance()->sendLeaveRoom();

	auto scene = LobbyScene::scene();
	Director::getInstance()->replaceScene(scene);
}

void SelectScene::onInitGlobalObjects(){
}
void SelectScene::onReleaseGlobalObjects(){
}