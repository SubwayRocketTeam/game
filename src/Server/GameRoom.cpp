#include "stdafx.h"
#include "GameRoom.h"
#include "GameRoomManager.h"
#include "ClientManager.h"
#include "Client.h"
#include "CompletionKeyType.h"

HANDLE GameRoom::hCompletionPort = INVALID_HANDLE_VALUE;


GameRoom::GameRoom(const id_t id)
:id(id), hTimer(INVALID_HANDLE_VALUE) {
}

GameRoom::~GameRoom() {
	if (hTimer != INVALID_HANDLE_VALUE)
		CloseHandle(hTimer);
}


bool GameRoom::initTimer() {
	/*
	hTimer = CreateWaitableTimer(nullptr, FALSE, nullptr);
	if (hTimer == NULL) {
		ErrorLog(GetLastError());
		hTimer = INVALID_HANDLE_VALUE;
		return false;
	}
	if (CreateIoCompletionPort(hTimer, hCompletionPort, CKT_TIMER, 0) != hCompletionPort) {
		ErrorLog(GetLastError());
		CloseHandle(hTimer);
		hTimer = INVALID_HANDLE_VALUE;
		return false;
	}
	*/
	return true;
}


void GameRoom::update() {

	/*
	LARGE_INTEGER period = { 0, };
	if (hTimer != INVALID_HANDLE_VALUE)
		SetWaitableTimer(hTimer, &period, 16, nullptr, nullptr, TRUE);
	*/
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
	if (clientIds.size() == 0)
		GameRoomManager::getInstance()->removeGameRoom(id);
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
