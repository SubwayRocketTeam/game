#pragma once

#include "IDDispenser.h"

struct IOContext {
	IOContext();
	virtual ~IOContext();

	WSAOVERLAPPED overlapped;
};

struct AcceptContext : IOContext {
	AcceptContext();
	virtual ~AcceptContext();

	SOCKET sock;
	sockaddr_in addr;
};

struct TimerContext : IOContext {
	TimerContext();
	virtual ~TimerContext();

	id_t gameRoomId;
	HANDLE hTimer;
};

struct SocketContext : IOContext {
	SocketContext();
	virtual ~SocketContext();

	id_t clientId;
	bool recv;
	char* buf;	// 반드시 동적할당된 메모리를 point
};