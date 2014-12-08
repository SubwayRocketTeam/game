﻿#include "stdafx.h"
#include "GameRoomManager.h"
#include "Client.h"
#include "ClientManager.h"
#include "GameRoom.h"
#include "Scheduler.h"
#include "PacketType.h"

/* ISSUE : 이러면 생성자 무조건 public으로 놔야됨 */
GameRoomManager instance;

GameRoomManager::GameRoomManager() :
	available(INVALID_ID){
}

GameRoomManager* GameRoomManager::getInstance() {
	return &instance;
}


GameRoom* GameRoomManager::getGameRoom(const id_t id) {
	std::lock_guard<std::mutex> lock(mutex);
	auto it = rooms.find(id);
	if (it == rooms.end())
		return nullptr;
	return it->second;
}
GameRoom *GameRoomManager::getAvailableGameRoom(){
	/* TODO : 4 교체 */
	auto room = getGameRoom(available);
	if (!room)
		available = INVALID_ID;
	else if (room->clientIds.size() >= 2) {
		StartGame packet;
		room->sendPacket(packet);

		for (auto id : *room) {
			SpawnUnit noti;
			noti.id = id;
			noti.unit_type = 1;
			auto client = ClientManager::getInstance()->getClient(id);
			client->sendPacket(noti);

			client->speed_x = client->x = 0;
			client->speed_y = client->y = 0;
		}

		for (auto id : *room) {
			SpawnUnit noti;
			noti.id = id;
			noti.unit_type = 0;
			room->sendPacket(noti);
		}

		available = INVALID_ID;
	}

	if (available == INVALID_ID){
		/* ISSUE : id로 관리하면 매번 map::find가 실행됨 */ 
		/* SOLUTION : createGameRoom이 GameRoom*을 반환하게 */
		available = createGameRoom();
	}

	return getGameRoom(available);
}

id_t GameRoomManager::createGameRoom() {
	std::lock_guard<std::mutex> lock(mutex);
	id_t id = dispenser.issue();
	GameRoom* room = new GameRoom(id);
	rooms[id] = room;
	Scheduler::getInstance()->schedule(id);
	return id;
}

bool GameRoomManager::removeGameRoom(const id_t id) {
	std::lock_guard<std::mutex> lock(mutex);
	auto it = rooms.find(id);
	if (it == rooms.end())
		return false;
	rooms.erase(it);
	printf("Room %d Exploded.\n", id);
	return true;
}
