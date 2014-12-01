#include "stdafx.h"

#include "Client.h"
#include "IOContext.h"
#include "PacketType.h"

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

		char* buf = new char[header.size];

		bufferQueue.pop(buf, header.size);

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

		}

		SAFE_DELETE_ARR(buf);
	}
}
