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

struct ScheduleTimerContext : IOContext {
	ScheduleTimerContext();

	id_t gameRoomId;
};

struct TimerContext : IOContext {
	TimerContext();

	id_t gameRoomId;
};

struct SocketContext : IOContext {
	SocketContext();

	id_t clientId;
	bool recv;
	char* buf;	// 반드시 동적할당된 메모리를 point
};