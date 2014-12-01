#pragma once

#include <set>

#include "IDDispenser.h"

class GameRoom {
public:
	GameRoom(const id_t id = INVALID_ID);
	~GameRoom();

	bool initTimer();

	void update();

	bool enter(const id_t client_id);
	bool leave(const id_t client_id);

	void broadcast(const char* const buf, const size_t size);

	const std::set<id_t>::iterator begin() const;
	const std::set<id_t>::iterator end() const;

public:
	static HANDLE hCompletionPort;

	const id_t id;

private:
	HANDLE hTimer;
	std::set<id_t> clientIds;
};