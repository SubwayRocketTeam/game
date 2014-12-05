#pragma once

#include "IDDispenser.h"
#include <map>

class GameRoom;

class GameRoomManager {
public:
	static GameRoomManager* getInstance();

	GameRoom* getGameRoom(const id_t id);
	GameRoom* getAvailableGameRoom();
	id_t createGameRoom();
	bool removeGameRoom(const id_t id);

	GameRoomManager();
private:
	

private:
	std::mutex mutex;

	IDDispenser dispenser;
	std::map<id_t, GameRoom*> rooms;

	GameRoom *available;
};