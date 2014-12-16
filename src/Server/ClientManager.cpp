#include "stdafx.h"

#include "ClientManager.h"
#include "Client.h"


ClientManager instance; ///< 위험하다. 전역 공간에 선언하면, 생성자가 언제 어떤 순서로 호출되지 모름.. 
/// http://blog.naver.com/spacesun/140200515569

ClientManager* ClientManager::getInstance() {
	return &instance;
}


Client* ClientManager::getClient(const id_t id) {
	auto it = clients.find(id);
	if (it == clients.end())
		return nullptr;
	return it->second;
}

id_t ClientManager::createClient(const SOCKET sock) {
	id_t id = dispenser.issue();
	Client* client = new Client(id, sock);
	clients[id] = client;
	client->onConnect();
	return id;
}

bool ClientManager::removeClient(const id_t id) {
	auto it = clients.find(id);
	if (it == clients.end())
		return false;
	it->second->onDisconnect();
	clients.erase(it);
	return true;
}
