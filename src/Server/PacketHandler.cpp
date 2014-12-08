#include "stdafx.h"
#include "PacketHandler.h"
#include "PacketType.h"

#include "Client.h"
#include "ClientManager.h"
#include "GameRoom.h"
#include "GameRoomManager.h"

static PacketHandler* handlerMap[PT_PacketMax];


PacketHandler* PacketHandlerMap::function(packet_type_t type) {
	_ASSERT(type < PT_PacketMax);
	return handlerMap[type];
}


struct RegisterHandler {
	RegisterHandler(packet_type_t type, PacketHandler* handler) {
		_ASSERT(type < PT_PacketMax);
		handlerMap[type] = handler;
	}
};

#define REGISTER_HANDLER(type)\
	static PacketHandler handler_##type;\
	static RegisterHandler _reg_##type(PT_##type, handler_##type);\
	static void handler_##type(Client* client, PacketHeader* header) {\
		type* packet = (type*) header;\



REGISTER_HANDLER(PacketNone)
END


REGISTER_HANDLER(LoginRequest)
	printf("%u: %s %s\n", client->id, packet->id, packet->pw);
	LoginResponse response;
	response.result = 1;
	strcpy_s(response.nickname, "Anz");
	client->sendPacket(response);
END


REGISTER_HANDLER(EnterRoom)
	EnterNoti noti;
	SpawnUnit spawnNoti;
	auto gameroom = GameRoomManager::getInstance()->getAvailableGameRoom();
	client->setGameRoomId(gameroom->id);
	gameroom->enter(client->id);

	noti.client_id = client->id;
	gameroom->sendPacket(noti);

	if (gameroom->size() >= 2) {
		ReadyRequest packet;
		gameroom->sendPacket(packet);
	}
END

REGISTER_HANDLER(Ready)
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(
		client->getGameRoomId());
	gameroom->ready ++;

	if(gameroom->ready != 2)
		return;

	/* TODO : °íÄ¡±â */
	{
		StartGame packet;
		gameroom->sendPacket(packet);
	}

	for (auto id : *gameroom) {
		SpawnUnit noti;
		noti.id = id;
		noti.unit_type = 1;
		noti.x = 0;
		noti.y = 0;
		auto client = ClientManager::getInstance()->getClient(id);
		client->sendPacket(noti);

		client->speed_x = client->x = 0;
		client->speed_y = client->y = 0;
	}

	for (auto id : *gameroom) {
		SpawnUnit noti;
		noti.id = id;
		noti.unit_type = 0;
		noti.x = 0;
		noti.y = 0;
		gameroom->sendPacket(noti);
	}
END


REGISTER_HANDLER(LeaveRoom)
	LeaveNoti noti;
	noti.client_id = client->id;
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());
	gameroom->sendPacket(noti);
	gameroom->leave(client->id);
END


REGISTER_HANDLER(MoveStart)
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());
	MoveStartNoti response;

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
	gameroom->sendPacket(response);

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

	MoveEndNoti response;
	response.id = client->id;
	response.end_x = x;
	response.end_y = y;
	gameroom->sendPacket(response);

	speed_x = speed_y = 0;
END


REGISTER_HANDLER(ChatMessage)
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());

	ChatNoti noti;
	strcat_s(noti.msg, packet->msg);

	gameroom->sendPacket(noti);
END