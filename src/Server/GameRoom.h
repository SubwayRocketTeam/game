#pragma once

#include "IDDispenser.h"
#include "Sendable.h"
#include "Stage.h"
#include "common\max.h"

#include <SDL.h>

class GameRoomManager;
class Unit;

typedef std::map<id_t, id_t> IdPairMap;

class GameRoom :public Sendable {
	friend GameRoomManager;

public:
	GameRoom(const id_t id = INVALID_ID);
	~GameRoom();

	void update();

	bool startGame();

	Unit* getUnit(const id_t id);
	Unit* getClientUnit(const id_t client_id);
	id_t getClientUnitId(const id_t client_id);
	void setTeam(const id_t client_id, int team);
	int getTeam(const id_t client_id);
	int getTeamNum(const int team_id);

	size_t getClientNum() const;

	virtual int send(void* const buf, const size_t size);

	bool enter(const id_t client_id);
	bool leave(const id_t client_id);

	IdPairMap::const_iterator begin() const;
	IdPairMap::const_iterator end() const;

	bool empty() const;
	size_t size() const;

	id_t addUnit(Unit* unit);		// Stage에서만 불러야 한다.
	void removeUnit(Unit* unit);	// Stage에서만 불러야 한다.

	bool isPlaying();
	bool isFull();

private:
	void addUnitImmediate(Unit* unit);
	void removeUnitImmediate(Unit* unit);

	void flush();

public:
	const id_t id;
	int ready;

private:
	IDDispenser dispenser;

	// first: client id
	// second : unit id
	IdPairMap clientIds;

	std::map<id_t, int> teams;

	DWORD tick;

	Stage* stage[Max::Teams];

	bool gameRunning;

	std::vector<Unit*> units;
	std::set<Unit*> addUnits;
	std::set<Unit*> removeUnits;

	SDL_Window *window;			///< 으잉? 서버에서 왠 SDL??
	SDL_Renderer *renderer;
};