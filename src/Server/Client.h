#pragma once

#include <WinSock2.h>
#include "BufferQueue.h"
#include "IDDispenser.h"
#include "PacketHandler.h"
#include "Sendable.h"

class GameRoom;

class Client : public Sendable {
public:
	Client(const id_t id = INVALID_ID, const SOCKET sock = INVALID_SOCKET);
	~Client();

	virtual int send(void* const buf, const size_t size);
	int sendAllocatedData(void* const buf, const size_t size);
	int recv();

	bool push(void* buf, const size_t size);

	void processPacket();

	void onConnect();
	void onDisconnect();

	void setGameRoomId(id_t id);
	id_t getGameRoomId();


public:
	const id_t id;

private:
	BufferQueue<BUF_SIZE> bufferQueue;
	SOCKET socket;

	id_t gameRoomId;
};