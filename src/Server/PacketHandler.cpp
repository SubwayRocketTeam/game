#include "stdafx.h"
#include "PacketHandler.h"
#include "PacketType.h"

#include "Client.h"
#include "ClientManager.h"
#include "GameRoom.h"
#include "GameRoomManager.h"

static PacketHandler* handlerMap[PT_MAX];


PacketHandler* PacketHandlerMap::function(packet_type_t type) {
	_ASSERT(type < PT_MAX);
	return handlerMap[type];
}


struct RegisterHandler {
	RegisterHandler(packet_type_t type, PacketHandler* handler) {
		_ASSERT(type < PT_MAX);
		handlerMap[type] = handler;
	}
};

#define REGISTER_HANDLER(type)\
	static PacketHandler handler_##type;\
	static RegisterHandler _reg_##type(PT_##type, handler_##type);\
	static void handler_##type(Client* client, PacketHeader* header) {\
		Packet_##type* packet = (Packet_##type*) header;\



REGISTER_HANDLER(None)
END


REGISTER_HANDLER(Example)
	printf("%u: %f %f\n", client->id, packet->x, packet->y);
END


REGISTER_HANDLER(LoginRequest)
	printf("%u: %s %s\n", client->id, packet->id, packet->pw);
	Packet_LoginResponse* response = new Packet_LoginResponse();
	response->result = 1;
	strcpy_s(response->nickname, "Anz");
	client->send((char*)response, response->size);
END


REGISTER_HANDLER(EnterRoom)
	Packet_EnterNoti noti;
	Packet_Spawn spawnNoti;
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(1);
	for (auto id : *gameroom) {
		noti.clientId = id;
		client->sendLocalData((char*)&noti, sizeof(Packet_EnterNoti));

		auto client = ClientManager::getInstance()->getClient(id);
		spawnNoti.x = client->x;
		spawnNoti.y = client->y;
		spawnNoti.id = id;
		spawnNoti.unit_type = 0;
		client->sendLocalData((char*)&spawnNoti, sizeof(Packet_Spawn));
	}
	gameroom->enter(client->id);

	noti.clientId = client->id;
	gameroom->broadcast((char*)&noti, sizeof(Packet_EnterNoti));

	spawnNoti.id = client->id;
	spawnNoti.unit_type = 0;
	gameroom->broadcastExceptOne((char*)&spawnNoti, sizeof(Packet_Spawn), client->id);

	spawnNoti.unit_type = 1;
	client->sendLocalData((char*)&spawnNoti, sizeof(Packet_Spawn));

	client->speed_x = client->x = 0;
	client->speed_y = client->y = 0;
END


REGISTER_HANDLER(LeaveRoom)
	Packet_LeaveNoti noti;
	noti.clientId = client->id;
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(1);
	gameroom->broadcast((char*)&noti, sizeof(Packet_LeaveNoti));
	gameroom->leave(client->id);
END


REGISTER_HANDLER(MoveStart)
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());
	Packet_MoveStartNoti response;

	float& speed_x = client->speed_x;
	float& speed_y = client->speed_y;
	float& x = client->x;
	float& y = client->y;
	int& tick = client->tick;


	if (speed_x || speed_y){
		float delta =
			(float)(GetTickCount() - tick) / 1000.0f;
		x += speed_x * 350 * delta;
		y += speed_y * 350 * delta;
	}

	response.id = client->id;
	response.velocity_x = packet->direction_x * 350;
	response.velocity_y = packet->direction_y * 350;
	gameroom->broadcast((char*)&response, sizeof(Packet_MoveStartNoti));

	tick = GetTickCount();
	speed_x = packet->direction_x;
	speed_y = packet->direction_y;
END

REGISTER_HANDLER(MoveEnd)
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());

	float& speed_x = client->speed_x;
	float& speed_y = client->speed_y;
	float& x = client->x;
	float& y = client->y;
	int& tick = client->tick;

	float delta =
		(float)(GetTickCount() - tick) / 1000.0f;
	printf("%f / %f %f\n", delta, speed_x, speed_y);
	x += speed_x * 350 * delta;
	y += speed_y * 350 * delta;
	printf("x : %f / y : %f\n", x, y);

	Packet_MoveEndNoti response;
	response.id = client->id;
	response.end_x = x;
	response.end_y = y;
	gameroom->broadcast((char*)&response, sizeof(Packet_MoveEndNoti));

	speed_x = speed_y = 0;
END


REGISTER_HANDLER(ChatMessage)
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());

	Packet_ChatNoti noti;
	strcat_s(noti.msg, packet->msg);

	gameroom->broadcast((char*)&noti, sizeof(Packet_ChatNoti));
END