#pragma once

#include <WinSock2.h>
#include "BufferQueue.h"
#include "IDDispenser.h"

class GameRoom;

class Client {
public:
	Client(const id_t id = INVALID_ID);
	~Client();

	int send(char* buf, const size_t size);
	int sendLocalData(const char* buf, const size_t size);
	int recv();
	bool push(const char* buf, const size_t size);

	void processPacket();

public:
	const id_t id;

private:
	BufferQueue<BUF_SIZE> bufferQueue;
	SOCKET socket;
	id_t gameRoomId;

};