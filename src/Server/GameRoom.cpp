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
	static int a = 0;
	printf("%d - %d\n", id, ++a);
}


bool GameRoom::enter(const id_t client_id) {
	if (client_id == INVALID_ID) return false;
	if (!clientIds.insert(client_id).second)
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


int GameRoom::send(void* const buf, const size_t size) {
	if (!buf || size < 1)
		return SOCKET_ERROR;
	for (auto id : clientIds) {
		Client* client = ClientManager::getInstance()->getClient(id);
		if (client)
		{
			if (client->send(buf, size) == SOCKET_ERROR)
				return SOCKET_ERROR;
		}
	}
	return 0;
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
