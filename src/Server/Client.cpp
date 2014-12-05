#include "stdafx.h"

#include "Client.h"
#include "IOContext.h"
#include "PacketType.h"
#include "ClientManager.h"
#include "GameRoom.h"
#include "GameRoomManager.h"
#include "PacketHandler.h"

Client::Client(const id_t id, const SOCKET sock)
:id(id), socket(sock), gameRoomId(INVALID_ID) {

}

Client::~Client() {
	closesocket(socket);
}

int Client::send(void* buf, const size_t size) {
	if (!buf || size < 1)
		return SOCKET_ERROR;

	SocketContext* context = new SocketContext();
	context->buf = (char*)buf;
	context->clientId = id;
	context->recv = false;

	WSABUF wsabuf;
	wsabuf.buf = (char*)buf;
	wsabuf.len = size;

	DWORD byteSent;

	if (WSASend(socket, &wsabuf, 1, &byteSent, 0, &context->overlapped, nullptr) == SOCKET_ERROR) {
		int error = WSAGetLastError();
		if (error != WSA_IO_PENDING)
		{
			ErrorLog(error);
			return SOCKET_ERROR;
		}
	}
	return byteSent;
}

int Client::sendLocalData(void* buf, const size_t size) {
	if (!buf || size < 1)
		return SOCKET_ERROR;
	char* new_buf = new char[size];
	memcpy_s(new_buf, size, buf, size);
	return send(new_buf, size);
}

int Client::recv() {
	SocketContext* context = new SocketContext();
	context->buf = new char[BUF_SIZE];
	context->clientId = id;
	context->recv = true;

	WSABUF wsabuf;
	wsabuf.buf = context->buf;
	wsabuf.len = BUF_SIZE;

	DWORD byteRecvd;
	DWORD flag = 0;

	if (WSARecv(socket, &wsabuf, 1, &byteRecvd, &flag, &context->overlapped, nullptr) == SOCKET_ERROR) {
		int error = WSAGetLastError();
		if (error != WSA_IO_PENDING)
		{
			ErrorLog(error);
			return SOCKET_ERROR;
		}
	}

	return byteRecvd;
}


bool Client::push(void* buf, const size_t size) {
	return bufferQueue.push((char*)buf, size);
}


void Client::processPacket() {
	PacketHeader header;
	while (true) {
		if (!bufferQueue.peek((char*)&header, sizeof(PacketHeader)))
			break;

		if (bufferQueue.getLength() < header.size)
			break;

		char* buf = new char[header.size];
		bufferQueue.pop(buf, header.size);

		auto handler = PacketHandlerMap::function(header.type);
		if (handler)
			handler(this, (PacketHeader*)buf);

		SAFE_DELETE_ARR(buf);
	}
}

void Client::onConnect() {
	printf("Connected : Client id %d\n", id);
	recv();
}

void Client::onDisconnect() {
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(gameRoomId);
	printf("Disconnected : Client id %d\n", id);
	if (gameroom) {
		Packet_LeaveNoti noti;
		noti.clientId = id;
		gameroom->leave(id);
		gameroom->broadcast((char*)&noti, sizeof(Packet_LeaveNoti));
	}
}


void Client::setGameRoomId(id_t id) {
	gameRoomId = id;
}

id_t Client::getGameRoomId() {
	return gameRoomId;
}
