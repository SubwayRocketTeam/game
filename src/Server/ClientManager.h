﻿#pragma once

#include "IDDispenser.h"
#include <map>

class Client;

class ClientManager {
public:
	static void create();
	static ClientManager* getInstance();

	Client* getClient(const id_t id);
	id_t createClient(const SOCKET sock);
	bool removeClient(const id_t id);

private:
	ClientManager();

private:
	IDDispenser dispenser;
	std::map<id_t, Client*> clients;
};