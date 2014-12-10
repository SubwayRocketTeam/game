#pragma once

#include "IDDispenser.h"
#include "Sendable.h"

class GameRoomManager;
class Unit;
class Stage;

typedef std::map<id_t, id_t> IdPairMap;

class GameRoom :public Sendable {
	friend GameRoomManager;

public:
	GameRoom(const id_t id = INVALID_ID);
	~GameRoom();

	void update(const float dt);

	bool startGame();

	Unit* getUnit(const id_t id);
	Unit* getClientUnit(const id_t client_id);

	virtual int send(void* const buf, const size_t size);

	bool enter(const id_t client_id);
	bool leave(const id_t client_id);

	IdPairMap::const_iterator begin() const;
	IdPairMap::const_iterator end() const;

	bool empty() const;
	size_t size() const;

private:
	Unit* createUnit(const int type);

public:
	const id_t id;
	int ready;

private:
	IDDispenser dispenser;

	// first: client id
	// second : unit id
	IdPairMap clientIds;

	// Stage[2]
	//	CollisionDetector;
	//	TrashPool;
	//	Ally[2];
	//	EnemySpawner;

	bool gameRunning;

	std::vector<Unit*> units;
};