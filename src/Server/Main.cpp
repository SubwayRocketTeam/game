#include "stdafx.h"

#include "CompletionKeyType.h"
#include "IOContext.h"

#include "Client.h"
#include "ClientManager.h"
#include "GameRoom.h"
#include "GameRoomManager.h"
#include "Scheduler.h"
#include "EnemyFactory.h"

#include "Event.h"
#include "config.h"

#include "shared/JsonLoader.h"
#include "shared/skill/SkillPool.h"

#include <SDL.h>
#pragma comment (lib, "sdl2")

void WorkerThread(HANDLE hCP);

#undef main
void main()
{
	SDL_Init(SDL_INIT_VIDEO);

	WSAData wsadata = { 0, };
	if (WSAStartup(MAKEWORD(2, 2), &wsadata)) {
		ErrorLog(WSAGetLastError());
		return;
	}

	HANDLE hCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 1);
	if (hCP == NULL) {
		ErrorLog(WSAGetLastError());
		return;
	}

	Scheduler::hCompletionPort = hCP;
	
	Event::newSchedule = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (Event::newSchedule == INVALID_HANDLE_VALUE) {
		ErrorLog(GetLastError());
		return;
	}

	std::thread worker(WorkerThread, hCP);

	SOCKET listenSocket = WSASocketW(AF_INET, SOCK_STREAM, 0, nullptr, 0, WSA_FLAG_OVERLAPPED);
	if (listenSocket == INVALID_SOCKET) {
		ErrorLog(WSAGetLastError());
		return;
	}

	char option = 1;
	if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == SOCKET_ERROR) {
		ErrorLog(WSAGetLastError());
		return;
	}
	if (setsockopt(listenSocket, IPPROTO_TCP, TCP_NODELAY, &option, sizeof(option)) == SOCKET_ERROR) {
		ErrorLog(WSAGetLastError());
		return;
	}

	sockaddr_in serverAddr = { 0, };
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(config::port);
	if (bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		ErrorLog(WSAGetLastError());
		return;
	}

	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		ErrorLog(WSAGetLastError());
		return;
	}

	JsonLoader::create();
	SkillPool::create();
	EnemyFactory::create();
	ClientManager::create();
	GameRoomManager::create();
	Scheduler::create();

	while (true) {
		AcceptContext* context = new AcceptContext;
		int addrLen = sizeof(context->addr);

		SOCKET clientSocket = accept(listenSocket, (sockaddr*)&context->addr, &addrLen);
		if (clientSocket == INVALID_SOCKET) {
			ErrorLog(WSAGetLastError());
			continue;
		}

		context->sock = clientSocket;

		PostQueuedCompletionStatus(hCP, 0, CKT_ACCEPT, (LPOVERLAPPED)context);
	}

	worker.join();

	closesocket(listenSocket);
	CloseHandle(hCP);
	CloseHandle(Event::newSchedule);
	WSACleanup();
}


void WorkerThread(HANDLE hCP) {
	while (true) {
		DWORD transferred;
		ComplationKeyType completionKey;
		IOContext* iocontext;

		if (!GetQueuedCompletionStatus(hCP, &transferred, (PULONG_PTR)&completionKey, (LPOVERLAPPED*)&iocontext, INFINITE)) {
			DWORD error = GetLastError();
			if (error != ERROR_NETNAME_DELETED)
			{
				ErrorLog(error);
				break;
			}
		}

		switch (completionKey) {

		case CKT_ACCEPT:
		{
			AcceptContext* context = (AcceptContext*)iocontext;

			if (CreateIoCompletionPort((HANDLE)context->sock, hCP, CKT_SOCKET, 0) != hCP) {
				ErrorLog(GetLastError());
				closesocket(context->sock);
			}
			else
			{
				id_t id = ClientManager::getInstance()->createClient(context->sock);
			}
			break;
		}

		case CKT_TIMER:
		{
			TimerContext* context = (TimerContext*)iocontext;
			GameRoom* room = GameRoomManager::getInstance()->getGameRoom(context->gameRoomId);
			// printf("TIMERTIMERTIMERTIMERITMER\n");
			if (room)
				room->update();
			break;
		}

		case CKT_SOCKET:
		{
			SocketContext* context = (SocketContext*)iocontext;
			if (context->recv) {
				// printf("RECV\n");
				Client* client = ClientManager::getInstance()->getClient(context->clientId);
				if (transferred == 0) {
					ClientManager::getInstance()->removeClient(context->clientId);
				}
				else if (client) {
					client->push(context->buf, transferred);
					client->processPacket();
					client->recv();
				}
			}
			SAFE_DELETE_ARR(context->buf);
			break;
		}

		}

		SAFE_DELETE(iocontext);
	}
}


void ScheduleThread() {

}