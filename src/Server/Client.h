#pragma once

#include <WinSock2.h>
#include "BufferQueue.h"
#include "IDDispenser.h"
#include "PacketHandler.h"

class GameRoom;

class Client {
public:
	Client(const id_t id = INVALID_ID, const SOCKET sock = INVALID_SOCKET);
	~Client();

	int send(char* buf, const size_t size);
	int sendLocalData(const char* buf, const size_t size);
	int recv();

	bool push(const char* buf, const size_t size);

	void processPacket();

	void onConnect();
	void onDisconnect();

	void setGameRoomId(id_t id);
	id_t getGameRoomId();


public:
	const id_t id;
	float x, y;
	float speed_x, speed_y;
	int tick;

private:
	BufferQueue<BUF_SIZE> bufferQueue;
	SOCKET socket;

	id_t gameRoomId;
};