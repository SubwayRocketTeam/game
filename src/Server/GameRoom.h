#pragma once

#include "IDDispenser.h"
#include "Sendable.h"

class GameRoomManager;

class GameRoom :public Sendable {
	friend GameRoomManager;

public:
	GameRoom(const id_t id = INVALID_ID);
	~GameRoom();

	void update(const float dt);

	bool enter(const id_t client_id);
	bool leave(const id_t client_id);

	virtual int send(void* const buf, const size_t size);
	int sendExceptOne(void* const buf, const size_t size, const id_t except_id);

	const std::set<id_t>::iterator begin() const;
	const std::set<id_t>::iterator end() const;

	bool empty() const;

public:
	const id_t id;

private:
	IDDispenser dispenser;
	std::set<id_t> clientIds;
};