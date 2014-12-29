#include "stdafx.h"
#include "GameRoomManager.h"
#include "Client.h"
#include "ClientManager.h"
#include "GameRoom.h"
#include "Scheduler.h"
#include "PacketType.h"

static GameRoomManager* instance;

void GameRoomManager::create() {
	instance = new GameRoomManager();
}

GameRoomManager::GameRoomManager() :
	available(INVALID_ID){
}

GameRoomManager* GameRoomManager::getInstance() {
	return instance;
}


GameRoom* GameRoomManager::getGameRoom(const id_t id) {
	std::lock_guard<std::mutex> lock(mutex);
	auto it = rooms.find(id);
	if (it == rooms.end())
		return nullptr;
	return it->second;
}
GameRoom *GameRoomManager::getAvailableGameRoom(){
	auto room = getGameRoom(available);
	if (!room || room->isPlaying()) {
		available = INVALID_ID;
	}

	if (available == INVALID_ID){
		available = createGameRoom();
	}

	return getGameRoom(available);
}

void GameRoomManager::notifyAvailableGameRooms(const id_t client_id) {
	auto client = ClientManager::getInstance()->getClient(client_id);
	if (!client)
		return;

	bool new_room_flag = true;
	int room_num = 0;
	char room_arr[33];
	for (auto& pair : rooms) {
		auto gameroom = pair.second;
		if (gameroom->isFull() || gameroom->isPlaying())
			continue;
		room_arr[room_num++] = pair.first;
		
		if (gameroom->getClientNum() == 0)
			new_room_flag = false;

		if (room_num >= 32)
			break;
	}

	if (new_room_flag)
		room_arr[room_num++] = createGameRoom();

	RoomResponse noti;
	noti.room_num = room_num;
	strcpy_s(noti.room_list, room_arr);
	client->sendPacket(noti);
}

id_t GameRoomManager::createGameRoom() {
	std::lock_guard<std::mutex> lock(mutex);
	id_t id = dispenser.issue();
	GameRoom* room = new GameRoom(id);
	rooms[id] = room;
	Scheduler::getInstance()->schedule(id);
	printf("Room %d Created.\n", id);
	return id;
}

bool GameRoomManager::removeGameRoom(const id_t id) {
	std::lock_guard<std::mutex> lock(mutex);
	auto it = rooms.find(id);
	if (it == rooms.end())
		return false;
	auto room = it->second;
	rooms.erase(it);
	printf("Room %d Exploded.\n", id);
	SAFE_DELETE(room);
	return true;
}
