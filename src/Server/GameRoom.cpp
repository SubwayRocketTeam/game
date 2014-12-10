#include "stdafx.h"
#include "GameRoom.h"
#include "GameRoomManager.h"
#include "ClientManager.h"
#include "Client.h"
#include "CompletionKeyType.h"
#include "Unit.h"

typedef std::pair<id_t, id_t> IdPair;

GameRoom::GameRoom(const id_t id)
	:id(id), ready(0), gameRunning(false) {
	for (int i = 0; i < STAGE_MAX; ++i)
		stage[i] = new Stage(this, i);
}

GameRoom::~GameRoom() {

}

void GameRoom::update() {
	DWORD now_tick = timeGetTime();
	for (int i = 0; i < STAGE_MAX; ++i)
		stage[i]->update(now_tick - tick);
	tick = now_tick;
}


bool GameRoom::enter(const id_t client_id) {
	if (client_id == INVALID_ID) return false;
	if (!clientIds.insert(IdPair(client_id, INVALID_ID)).second)
		return false;
	ClientManager::getInstance()->getClient(client_id)->setGameRoomId(id);
	return true;
}

bool GameRoom::leave(const id_t client_id) {
	if (client_id == INVALID_ID) return false;
	auto it = clientIds.find(client_id);
	if (it == clientIds.end())
		return false;
	clientIds.erase(it);
	ClientManager::getInstance()->getClient(client_id)->setGameRoomId(INVALID_ID);

	// 모두 나가면 방폭
	if (clientIds.size() == 0)
		GameRoomManager::getInstance()->removeGameRoom(id);
	return true;
}


bool GameRoom::startGame() {
	if (gameRunning || ready < clientIds.size()) return false;
	gameRunning = true;

	// TODO: 게임 시작을 통보

	for (auto& id : clientIds) {
		id.second = addUnit(new Unit(), UT_PLAYER, 0);
		// TODO: 클라에게 자신이 생성됨을 통보
	}

	// TODO: 모든 클라에게 생성된 유닛을 통보

	return true;
}


id_t GameRoom::addUnit(Unit* unit, const int type, const int stage_id) {
	_ASSERT(stage_id >= 0 && stage_id < STAGE_MAX);
	id_t id = dispenser.issue();
	Stage* now_stage = stage[stage_id];
	unit->id = id;
	unit->type = type;
	unit->stage = now_stage;
	now_stage->addUnit(unit);
	units.push_back(unit);
}

void GameRoom::eraseUnit(const id_t id) {
	Unit* unit = getUnit(id);
	if (!unit)
		return;

	unit->stage->removeUnit(id);

	auto it = std::find(units.begin(), units.end(), unit);
	if (it != units.end())
		units.erase(it);

	SAFE_DELETE(unit);
}

Unit* GameRoom::getUnit(const id_t id) {
	auto it = std::find_if(units.begin(), units.end(), [id](Unit* u){ return u->id == id; });
	if (it == units.end())
		return nullptr;
	return *it;
}

Unit* GameRoom::getClientUnit(const id_t client_id) {
	auto it = clientIds.find(client_id);
	if (it == clientIds.end())
		return nullptr;
	return getUnit(it->second);
}


int GameRoom::send(void* const buf, const size_t size) {
	if (!buf || size < 1)
		return SOCKET_ERROR;
	for (auto id : clientIds) {
		Client* client = ClientManager::getInstance()->getClient(id.first);
		if (client)
		{
			if (client->send(buf, size) == SOCKET_ERROR)
				return SOCKET_ERROR;
		}
	}
	return 0;
}


IdPairMap::const_iterator GameRoom::begin() const {
	return clientIds.begin();
}

IdPairMap::const_iterator GameRoom::end() const {
	return clientIds.end();
}

bool GameRoom::empty() const {
	return clientIds.empty();
}

size_t GameRoom::size() const {
	return clientIds.size();
}
