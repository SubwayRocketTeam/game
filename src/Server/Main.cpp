#include "stdafx.h"

#include "CompletionKeyType.h"
#include "IOContext.h"

#include "Client.h"
#include "ClientManager.h"
#include "GameRoom.h"
#include "GameRoomManager.h"
#include "Scheduler.h"

#include "Event.h"
#include "config.h"

void WorkerThread(HANDLE hCP);

void main()
{
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

	Scheduler::getInstance()->init();

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

//	GameRoomManager::getInstance()->createGameRoom();

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
			if (room)
				room->update(16.f/1000.f);
			break;
		}

		case CKT_SOCKET:
		{
			SocketContext* context = (SocketContext*)iocontext;
			if (context->recv) {
				Client* client = ClientManager::getInstance()->getClient(context->clientId);
				if (transferred == 0) {
					ClientManager::getInstance()->removeClient(context->clientId);
				}
				else {
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