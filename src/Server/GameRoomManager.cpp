#include "stdafx.h"
#include "GameRoomManager.h"
#include "GameRoom.h"

GameRoomManager instance;

GameRoomManager* GameRoomManager::getInstance() {
	return &instance;
}


GameRoom* GameRoomManager::getGameRoom(const id_t id) {
	auto it = rooms.find(id);
	if (it == rooms.end())
		return nullptr;
	return it->second;
}

id_t GameRoomManager::createGameRoom() {
	id_t id = dispenser.issue();
	GameRoom* room = new GameRoom(id);
	if (!room->initTimer()) {
		SAFE_DELETE(room);
		return INVALID_ID;
	}
	room->update();
	rooms[id] = room;

	return id;
}

bool GameRoomManager::removeGameRoom(const id_t id) {
	auto it = rooms.find(id);
	if (it == rooms.end())
		return false;
	rooms.erase(it);
	return true;
}
