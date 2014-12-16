#pragma once

#include "IDDispenser.h"
#include <map>

class GameRoom;

class GameRoomManager {
public:
	static void create();
	static GameRoomManager* getInstance();

	GameRoom* getGameRoom(const id_t id);
	GameRoom* getAvailableGameRoom();
	id_t createGameRoom();
	bool removeGameRoom(const id_t id);

private:
	GameRoomManager();

private:
	std::mutex mutex;

	IDDispenser dispenser;
	std::map<id_t, GameRoom*> rooms;

	id_t available;
};