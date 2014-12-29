#include "pch.h"
#include "ResultScene.h"

#include "network/Network.h"
#include "network/GameRoom.h"

#include "ui/UIImageView.h"
#include "ui/UIText.h"

#include "scene/WaitingScene.h"

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

	auto winTeam = layout->getChildByName("pn_team_win");
	auto loseTeam = layout->getChildByName("pn_team_lose");

	int win_team_index = 0;
	int lose_team_index = 0;
	auto gameroom = GameRoom::getInstance();
	for (auto& pair : *gameroom) {
		auto& client = pair.second;
		Node* panel = nullptr;
		if (client.team == gameroom->getWinTeam()) {
			panel = winTeam->getChildByTag(win_team_index++);
		}
		else {
			panel = loseTeam->getChildByTag(lose_team_index++);
		}
		auto robot_image = (ui::ImageView*)panel->getChildByName("robot");
		auto nickname_text = (ui::Text*)panel->getChildByName("nickname");

		robot_image->loadTexture(_MAKE_PATH("robot%d.png", client.robot));
		nickname_text->setString(client.nickname);
	}

	auto btnExit =
		(ui::Widget*)layout->getChildByName("btn_exit");
	btnExit->addTouchEventListener(
		CC_CALLBACK_2(ResultScene::onExitRoom, this));

	addChild(layout);

	return true;
}

void ResultScene::onInitGlobalObjects(){
}
void ResultScene::onReleaseGlobalObjects(){
}
void ResultScene::onExitRoom(
	Ref *sender, ui::Widget::TouchEventType type) {

	if (type != ui::Widget::TouchEventType::ENDED)
		return;

	auto network = Network::getInstance();
	network->sendLeaveRoom();

	auto scene = WaitingScene::scene();
	Director::getInstance()
		->replaceScene(scene);
}
