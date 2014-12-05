#include "stdafx.h"
#include "GameRoom.h"
#include "GameRoomManager.h"
#include "ClientManager.h"
#include "Client.h"
#include "CompletionKeyType.h"

GameRoom::GameRoom(const id_t id)
:id(id) {
}

GameRoom::~GameRoom() {
}

void GameRoom::update(const float dt) {
}


bool GameRoom::enter(const id_t client_id) {
	if (client_id == INVALID_ID) return false;
	if (!clientIds.insert(client_id).second)
		return false;

	return true;
}

bool GameRoom::leave(const id_t client_id) {
	if (client_id == INVALID_ID) return false;
	auto it = clientIds.find(client_id);
	if (it == clientIds.end())
		return false;
	clientIds.erase(it);
	// 모두 나가면 방폭
//	if (clientIds.size() == 0)
//		GameRoomManager::getInstance()->removeGameRoom(id);
	return true;
}


void GameRoom::broadcast(const char* const buf, const size_t size) {
	if (!buf || size < 1) return;
	for (auto id : clientIds) {
		Client* client = ClientManager::getInstance()->getClient(id);
		if (client)
			client->sendLocalData(buf, size);
	}
}

void GameRoom::broadcastExceptOne(const char* const buf, const size_t size, const id_t except_id) {
	if (!buf || size < 1) return;
	for (auto id : clientIds) {
		if (id == except_id)
			continue;
		Client* client = ClientManager::getInstance()->getClient(id);
		if (client)
			client->sendLocalData(buf, size);
	}
}



const std::set<id_t>::iterator GameRoom::begin() const {
	return clientIds.begin();
}

const std::set<id_t>::iterator GameRoom::end() const {
	return clientIds.end();
}

bool GameRoom::empty() const {
	return clientIds.empty();
}
