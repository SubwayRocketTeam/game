#include "stdafx.h"

#include "Client.h"
#include "IOContext.h"
#include "PacketType.h"
#include "ClientManager.h"
#include "GameRoom.h"
#include "GameRoomManager.h"


PacketHandler Client::handlerMap[PT_MAX];

void Client::bindHandler(const PacketType type, PacketHandler handler) {
	handlerMap[type] = handler;
}


Client::Client(const id_t id, const SOCKET sock)
:id(id), socket(sock), gameRoomId(INVALID_ID) {

}

Client::~Client() {
	closesocket(socket);
}

int Client::send(char* buf, const size_t size) {
	if (!buf || size < 1)
		return SOCKET_ERROR;

	SocketContext* context = new SocketContext();
	context->buf = buf;
	context->clientId = id;
	context->recv = false;

	WSABUF wsabuf;
	wsabuf.buf = buf;
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

int Client::sendLocalData(const char* buf, const size_t size) {
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


bool Client::push(const char* buf, const size_t size) {
	return bufferQueue.push(buf, size);
}


void Client::processPacket() {
	PacketHeader header;
	while (true) {
		if (!bufferQueue.peek((char*)&header, sizeof(PacketHeader)))
			break;

		if (bufferQueue.getLength() < header.size)
			break;

		/*
		auto handler = handlerMap[header.type];
		if (handler.target<void(PacketHeader*)>() == nullptr)
			continue;
		*/

		char* buf = new char[header.size];

		bufferQueue.pop(buf, header.size);

		/*
		handler((PacketHeader*)buf);
		*/

		switch (header.type) {
		
		case PT_Example:
		{
			Packet_Example* packet = (Packet_Example*)buf;
			printf("%u: %f %f\n", id, packet->x, packet->y);
			break;
		}

		case PT_LoginRequest:
		{
			Packet_LoginRequest* packet = (Packet_LoginRequest*)buf;
			printf("%u: %s %s\n", id, packet->id, packet->pw);
			Packet_LoginResponse* response = new Packet_LoginResponse();
			response->result = 1;
			strcpy_s(response->nickname, "Anz");
			send((char*)response, response->size);
			break;
		}

		case PT_EnterRoom:
		{
			Packet_EnterNoti noti;
			Packet_Spawn spawnNoti;
			auto gameroom = GameRoomManager::getInstance()->getGameRoom(1);
			for (auto id : *gameroom) {
				noti.clientId = id;
				sendLocalData((char*)&noti, sizeof(Packet_EnterNoti));
			}
			gameroom->enter(id);
			gameRoomId = 1;
			noti.clientId = id;
			spawnNoti.id = id;
			gameroom->broadcast((char*)&noti, sizeof(Packet_EnterNoti));
			gameroom->broadcast((char*)&spawnNoti, sizeof(Packet_Spawn));
			break;
		}

		case PT_MoveStartRequest:
		{
			Packet_MoveStartRequest* packet = (Packet_MoveStartRequest*)buf;
			auto gameroom = GameRoomManager::getInstance()->getGameRoom(gameRoomId);
			Packet_MoveStartResponse response;
			response.id = packet->id;
			response.velocity_x = packet->direction_x * 7;
			response.velocity_y = packet->direction_y * 7;
			gameroom->broadcast((char*)&response, sizeof(Packet_MoveStartResponse));
			break;
		}

		case PT_MoveEndRequest:
		{
			Packet_MoveEndRequest* packet = (Packet_MoveEndRequest*)buf;
			auto gameroom = GameRoomManager::getInstance()->getGameRoom(gameRoomId);
			Packet_MoveEndResponse response;
			response.id = packet->id;
			gameroom->broadcast((char*)&response, sizeof(Packet_MoveEndResponse));
			break;
		}

		}

		SAFE_DELETE_ARR(buf);
	}
}

void Client::onConnect() {
	recv();
}

void Client::onDisconnect() {
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(gameRoomId);
	if (gameroom) {
		Packet_LeaveNoti noti;
		noti.clientId = id;
		gameroom->leave(id);
		gameroom->broadcast((char*)&noti, sizeof(Packet_LeaveNoti));
	}
}
