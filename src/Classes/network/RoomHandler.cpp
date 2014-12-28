#include "pch.h"
#include "Network.h"

#include "common/resource.h"

#include "objects/Stage.h"
#include "objects/Unit.h"

#include "scene/GameScene.h"

using namespace cocos2d;

void Network::handleRoomResponse(
	RoomResponse *pkt) {
	printf("room list : \n");
	for (int i = 0; i < pkt->room_num; ++i) {
		printf("%d\n", pkt->room_list[i]);
	}
}
void Network::handleEnterResponse(
	EnterResponse *pkt) {
	if (pkt->room_id == 0)
		printf("enter room failed\n");
	else
		printf("enter success : %d\n", pkt->room_id);
}

/* TODO : 수정, 스테이지 id, 유닛 id 등 */
void Network::handleEnterNoti(
	EnterNoti *pkt){

	printf("enter noti : %d\n", pkt->client_id);
}
void Network::handleLeaveNoti(
	LeaveNoti *pkt){

	printf("leave noti : %d\n", pkt->client_id);
}
void Network::handleSelectRobotNoti(
	SelectRobotNoti *pkt) {
	
	printf("client %d selected robot %d.\n", pkt->client_id, pkt->robot_id);

}
void Network::handleSelectTeamNoti(
	SelectTeamNoti *pkt) {
	printf("client %d selected team %d.\n", pkt->client_id, pkt->team_id);
}

void Network::handleReadyNoti(
	ReadyNoti *pkt){

	auto scene = GameScene::scene();
	Director::getInstance()
		->replaceScene(scene);
}
void Network::handleStartGame(
	StartGame *pkt){

	printf("start game\n");
}

void Network::handleGameOver(
	GameOver *pkt) {
	printf("game over. team %d win.\n", pkt->win_team);
}
