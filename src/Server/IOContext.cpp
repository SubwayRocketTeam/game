#include "stdafx.h"
#include "IOContext.h"


IOContext::IOContext() {
	ZeroMemory(&overlapped, sizeof(WSAOVERLAPPED));
}

AcceptContext::AcceptContext()
:IOContext(), sock(INVALID_SOCKET) {
	ZeroMemory(&addr, sizeof(sockaddr_in));
}

TimerContext::TimerContext()
:IOContext(), gameRoomId(INVALID_ID) {

}

SocketContext::SocketContext()
:IOContext(), clientId(INVALID_ID), recv(false), buf(nullptr) {

}
