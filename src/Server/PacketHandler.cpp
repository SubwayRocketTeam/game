#include "stdafx.h"
#include "PacketHandler.h"
#include "PacketType.h"

#include "Unit.h"
#include "Player.h"
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
		type* packet = (type*) header;



REGISTER_HANDLER(PacketNone)
END


REGISTER_HANDLER(CheckVersionRequest)
	CheckVersionResponse response;
	
	if(packet->version == PACKET_VERSION)
		response.result = 1;

	client->sendPacket(response);
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

gameroom->ready++;

	if(gameroom->ready != 2)
		return;

	gameroom->startGame();
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
	Player* player = (Player*)gameroom->getClientUnit(client->id);
	player->moveDirection = Vec2(packet->direction_x, packet->direction_y).getNormalized();

	MoveStartNoti response;
	response.id = player->id;
	response.velocity_x = player->moveDirection.x * player->_ATTR(speed);
	response.velocity_y = player->moveDirection.y * player->_ATTR(speed);
	printf("START %d (%f %f)\n", response.id, response.velocity_x, response.velocity_y);
	gameroom->sendPacket(response);
END

REGISTER_HANDLER(MoveEnd)
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());
	Player* player = (Player*)gameroom->getClientUnit(client->id);
	player->moveDirection = Vec2::ZERO;

	MoveEndNoti response;
	response.id = player->id;
	response.end_x = player->position.x;
	response.end_y = player->position.y;
	printf("END %d (%f %f)\n", response.id, response.end_x, response.end_y);
	gameroom->sendPacket(response);
END

REGISTER_HANDLER(SyncRotation)
	auto gameroom =
		GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());

	SyncRotationNoti noti;
	noti.id = gameroom->getClientUnitId(client->id);
	noti.angle = packet->angle;

	gameroom->sendPacket(noti);
END

REGISTER_HANDLER(ChatMessage)
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());

	ChatNoti noti;
	strcat_s(noti.msg, packet->msg);

	gameroom->sendPacket(noti);
END