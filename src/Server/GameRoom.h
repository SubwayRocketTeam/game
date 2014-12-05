#pragma once

#include <set>

#include "IDDispenser.h"

class GameRoom {
	friend GameRoomManager;

public:
	GameRoom(const id_t id = INVALID_ID);
	~GameRoom();

	void update(const float dt);

	bool enter(const id_t client_id);
	bool leave(const id_t client_id);

	void broadcast(const char* const buf, const size_t size);
	void broadcastExceptOne(const char* const buf, const size_t size, const id_t except_id);

	const std::set<id_t>::iterator begin() const;
	const std::set<id_t>::iterator end() const;

	bool empty() const;

public:
	const id_t id;

private:
	IDDispenser dispenser;
	std::set<id_t> clientIds;
};