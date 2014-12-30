#include "pch.h"
#include "LobbyScene.h"
#include "GameScene.h"

#include "network/Network.h"

#include "ui/UIText.h"
#include "ui/UIListView.h"

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
	// list->setItemsMargin();

	auto btnFast =
		(ui::Widget*)layout->getChildByName("btn_fast");
	auto btnRefresh =
		(ui::Widget*)layout->getChildByName("btn_refresh");

	btnFast->addTouchEventListener(
		CC_CALLBACK_2(LobbyScene::onFastStart, this));
	btnRefresh->addTouchEventListener(
		CC_CALLBACK_2(LobbyScene::onRefresh, this));

	refresh();

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
		item->addTouchEventListener(
			CC_CALLBACK_2(LobbyScene::onEnter, this, room_ids[i]));
		list->pushBackCustomItem(item);
	}
}



void LobbyScene::onInitGlobalObjects(){
}
void LobbyScene::onReleaseGlobalObjects(){
}

void LobbyScene::onEnter(
	cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type, int room_id) {
	if (type != ui::Widget::TouchEventType::ENDED)
		return;
	enter(room_id);
}

void LobbyScene::onFastStart(
	cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type != ui::Widget::TouchEventType::ENDED)
		return;
	if (rooms.empty())
		return;

	enter(rand() % rooms.size());
}
void LobbyScene::onRefresh(
	cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type != ui::Widget::TouchEventType::ENDED)
		return;

	refresh();
}
