#include "stdafx.h"

#include "ClientManager.h"
#include "Client.h"


ClientManager instance;

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
