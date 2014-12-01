#pragma once

#include <WinSock2.h>
#include "BufferQueue.h"
#include "IDDispenser.h"
#include "PacketType.h"

typedef std::function<void(PacketHeader*)> PacketHandler;

class GameRoom;

class Client {
public:
	static void bindHandler(const PacketType type, PacketHandler handler);

	Client(const id_t id = INVALID_ID, const SOCKET sock = INVALID_SOCKET);
	~Client();

	int send(char* buf, const size_t size);
	int sendLocalData(const char* buf, const size_t size);
	int recv();

	bool push(const char* buf, const size_t size);

	void processPacket();

	void onConnect();
	void onDisconnect();

public:
	const id_t id;

private:
	static std::map<PacketType, PacketHandler> handlerMap;

	BufferQueue<BUF_SIZE> bufferQueue;
	SOCKET socket;
	id_t gameRoomId;

};