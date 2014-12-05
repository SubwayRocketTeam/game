#pragma once

#include "IDDispenser.h"
#include <map>

class GameRoom;

class GameRoomManager {
public:
	static GameRoomManager* getInstance();

	GameRoom* getGameRoom(const id_t id);
	id_t createGameRoom();
	bool removeGameRoom(const id_t id);

private:
	std::mutex mutex;

	IDDispenser dispenser;
	std::map<id_t, GameRoom*> rooms;
};