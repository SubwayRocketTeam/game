#include "stdafx.h"
#include "IOContext.h"


IOContext::IOContext() {
	ZeroMemory(&overlapped, sizeof(WSAOVERLAPPED));
}

IOContext::~IOContext() {

}


AcceptContext::AcceptContext()
:IOContext(), sock(INVALID_SOCKET) {
	ZeroMemory(&addr, sizeof(sockaddr_in));
}

AcceptContext::~AcceptContext() {

}


TimerContext::TimerContext()
:IOContext(), gameRoomId(INVALID_ID), hTimer(INVALID_HANDLE_VALUE) {

}

TimerContext::~TimerContext() {

}


SocketContext::SocketContext()
:IOContext(), clientId(INVALID_ID), recv(false), buf(nullptr) {

}

SocketContext::~SocketContext() {
	delete[] buf;
}