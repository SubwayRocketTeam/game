#include "pch.h"
#include "Network.h"

#include "common/resource.h"

#include "objects/Stage.h"
#include "objects/Unit.h"

#include "scene/GameScene.h"

using namespace cocos2d;

/* TODO : 수정, 스테이지 id, 유닛 id 등 */
void Network::handleEnterRoomNoti(
	EnterNoti *pkt){

}
void Network::handleLeaveRoomNoti(
	LeaveNoti *pkt){

}

void Network::handleStartGame(
	StartGame *pkt){

	auto scene = GameScene::scene();
	Director::getInstance()
		->replaceScene(scene);
}