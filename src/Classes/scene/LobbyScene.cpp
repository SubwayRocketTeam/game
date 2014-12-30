#include "pch.h"
#include "LobbyScene.h"
#include "GameScene.h"

#include "network/Network.h"

#include "ui/UIText.h"
#include "ui/UIListView.h"
#include "ui/UIButton.h"

#include "audio/include/SimpleAudioEngine.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;
using namespace CocosDenshion;

LobbyScene::LobbyScene(){
}
LobbyScene::~LobbyScene(){
}

static int tagLayout = 1;

Scene* LobbyScene::scene(){
	auto scene = Scene::create();
	LobbyScene *layer = LobbyScene::create();
	scene->addChild(layer, 0, 1);
	return scene;
}

bool LobbyScene::init(){
	if(!Layer::init())
		return false;
	
	auto reader = GUIReader::getInstance();
	auto layout = reader->widgetFromJsonFile("lobby_scene.json");

	addChild(layout, 0, tagLayout);

	auto list = (ui::ListView*)layout->getChildByName("rooms");

	auto btnFast =
		(ui::Button*)layout->getChildByName("btn_fast");
	auto btnRefresh =
		(ui::Button*)layout->getChildByName("btn_refresh");

	btnFast->setPressedActionEnabled(true);
	btnRefresh->setPressedActionEnabled(true);

	btnFast->addClickEventListener(
		CC_CALLBACK_1(LobbyScene::onFastStart, this));
	btnRefresh->addClickEventListener(
		CC_CALLBACK_1(LobbyScene::onRefresh, this));

	return true;
}

void LobbyScene::enter(int room_id) {
	auto network = Network::getInstance();
	network->sendEnterRoom(room_id);
}

void LobbyScene::refresh() {
	auto layout = getChildByTag(tagLayout);
	auto list = layout->getChildByName("rooms");
	list->removeAllChildren();
	rooms.clear();

	auto network = Network::getInstance();
	network->sendRoomRequest();
}

void LobbyScene::addRooms(int room_num, char* room_ids) {
	auto reader = GUIReader::getInstance();
	auto layout = getChildByTag(tagLayout);
	auto list = (ui::ListView*)layout->getChildByName("rooms");
	for (int i = 0; i < room_num; ++i) {
		rooms.push_back(room_ids[i]);
		auto item = reader->widgetFromJsonFile("room_item.json");
		auto text = (ui::Text*)item->getChildByName("label");
		text->setString(_MAKE_PATH("Room #%d", room_ids[i]));
		item->setPositionX(20);
		item->addClickEventListener(
			CC_CALLBACK_1(LobbyScene::onEnterRoom, this, room_ids[i]));
		list->pushBackCustomItem(item);
	}
}

void LobbyScene::onEnter() {
	Layer::onEnter();
	refresh();
}


void LobbyScene::onInitGlobalObjects(){
}
void LobbyScene::onReleaseGlobalObjects(){
}

void LobbyScene::onButtonPressed(
	Ref *_sender, ui::Widget::TouchEventType type){

	if(type != ui::Widget::TouchEventType::BEGAN)
		return;

	auto sender = (ui::Button*)_sender;
	sender->runAction(
		Sequence::create(
			ScaleTo::create(0.23 / 2, 1.1, 0.95),
			ScaleTo::create(0.17 / 2, 0.9, 1.1),
			ScaleTo::create(0.15 / 2, 1.05, 0.95),
			ScaleTo::create(0.08 / 2, 1, 1),
			nullptr));
}
void LobbyScene::onEnterRoom(
	cocos2d::Ref *sender, int room_id) {

	enter(room_id);
}

void LobbyScene::onFastStart(
	cocos2d::Ref *sender) {
	
	if (rooms.empty())
		return;

	enter(rooms[rand() % rooms.size()]);
}
void LobbyScene::onRefresh(
	cocos2d::Ref *sender) {

	refresh();
}
