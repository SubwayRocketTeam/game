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

	printf("enter noti : %d\n", pkt->client_id);
}
void Network::handleLeaveRoomNoti(
	LeaveNoti *pkt){

	printf("leave noti : %d\n", pkt->client_id);
}

void Network::handleReadyRequest(
	ReadyRequest *pkt){

	auto scene = GameScene::scene();
	Director::getInstance()
		->replaceScene(scene);
}
void Network::handleStartGame(
	StartGame *pkt){

	printf("start game / team : %d, seed : %d\n",
		pkt->team, pkt->seed);
}