#pragma once

#include "IDDispenser.h"

struct IOContext {
	IOContext();

	WSAOVERLAPPED overlapped;
};

struct AcceptContext : IOContext {
	AcceptContext();

	SOCKET sock;
	sockaddr_in addr;
};

struct TimerContext : IOContext {
	TimerContext();

	id_t gameRoomId;
	HANDLE hTimer;
};

struct SocketContext : IOContext {
	SocketContext();

	id_t clientId;
	bool recv;
	char* buf;	// 반드시 동적할당된 메모리를 point
};