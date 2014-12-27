#include "stdafx.h"
#include "PacketHandler.h"
#include "PacketType.h"

#include "Unit.h"
#include "Enemy.h"
#include "Player.h"
#include "Client.h"
#include "ClientManager.h"
#include "GameRoom.h"
#include "GameRoomManager.h"
#include "EnemySpawner.h"
#include "EnemyFactory.h"
#include "EnemyType.h"
#include "EnemyInfo.h"

static PacketHandler* handlerMap[PT_PacketMax];


PacketHandler* PacketHandlerMap::function(packet_type_t type) {
	_ASSERT(type < PT_PacketMax);
	if (type != PT_SyncRotation)
		printf("PACKET RECV %d\n", type);
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


REGISTER_HANDLER(CheckVersionRequest) {
	CheckVersionResponse response;

	if (packet->version == PACKET_VERSION)
		response.result = 1;

	client->sendPacket(response);
} END

REGISTER_HANDLER(LoginRequest) {
	printf("%u: %s %s\n", client->id, packet->id, packet->pw);
	LoginResponse response;
	response.result = 1;
	strcpy_s(response.nickname, "Anz");
	client->sendPacket(response);
} END


REGISTER_HANDLER(EnterRoom) {
	EnterNoti noti;
	auto gameroom = GameRoomManager::getInstance()->getAvailableGameRoom();
	NULLCHECK(gameroom);

	client->setGameRoomId(gameroom->id);
	gameroom->enter(client->id);

	noti.client_id = client->id;
	gameroom->sendPacket(noti);

	if (gameroom->size() >= 2) {
		ReadyRequest packet;
		gameroom->sendPacket(packet);
	}
} END

REGISTER_HANDLER(Ready) {
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(
		client->getGameRoomId());
	NULLCHECK(gameroom);

	gameroom->ready++;

	if (gameroom->ready != 2)
		return;

	gameroom->startGame();
} END


REGISTER_HANDLER(LeaveRoom) {
	LeaveNoti noti;
	noti.client_id = client->id;
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());
	NULLCHECK(gameroom);
	gameroom->sendPacket(noti);
	gameroom->leave(client->id);
} END


REGISTER_HANDLER(SpawnRequest) {
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());
	Player* player = (Player*)gameroom->getClientUnit(client->id);
	NULLCHECK(gameroom);
	NULLCHECK(player);
	auto type = (EnemyType)(packet->enemy_type - ENEMY_BASIC);
	auto spawner = player->stage->spawner;
	auto info = EnemyFactory::getInstance()->getEenmyInfo(type);

	if (player->getTrash() < info->cost)
		return;

	player->addTrash(-info->cost);
	Enemy* enemy = spawner->spawn(type);

	/*
	SpawnUnit noti;
	noti.id = enemy->id;
	noti.stage = enemy->stage->id;
	noti.x = enemy->position.x;
	noti.y = enemy->position.y;
	noti.unit_type = packet->unit_type;

	gameroom->sendPacket(noti);
	*/
} END


REGISTER_HANDLER(UseSkill) {
	auto gameroom =
		GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());
	NULLCHECK(gameroom);
	Player* player = (Player*)gameroom->getClientUnit(client->id);
	NULLCHECK(player);

	player->useSkill(packet->skill_id, Vec2(packet->x, packet->y));

	/*
	UseSkillNoti noti;
	noti.id = gameroom->getClientUnitId(client->id);
	noti.skill_id = packet->skill_id;
	noti.x = packet->x;
	noti.y = packet->y;

	gameroom->sendPacket(noti);
	*/
} END


REGISTER_HANDLER(Move) {
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());
	NULLCHECK(gameroom);
	Player* player = (Player*)gameroom->getClientUnit(client->id);
	NULLCHECK(player);
	player->moveDirection = Vec2(packet->direction_x, packet->direction_y).getNormalized();

	MoveNoti response;
	response.id = player->id;
	response.start_x = player->position.x;
	response.start_y = player->position.y;
	response.velocity_x = player->moveDirection.x * player->_ATTR(speed);
	response.velocity_y = player->moveDirection.y * player->_ATTR(speed);
	printf("MOVE %d pos:(%f, %f) v:(%f %f)\n", response.id, response.start_x, response.start_y, response.velocity_x, response.velocity_y);
	gameroom->sendPacket(response);
} END

REGISTER_HANDLER(SyncRotation) {
	auto gameroom =
		GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());
	NULLCHECK(gameroom);
	Unit* unit = gameroom->getClientUnit(client->id);
	NULLCHECK(unit);

	unit->direction = Vec2::UNIT_X.getRotated(Vec2::ZERO, packet->angle);

	SyncRotationNoti noti;
	noti.id = gameroom->getClientUnitId(client->id);
	noti.angle = packet->angle;

	gameroom->sendPacket(noti);
} END

REGISTER_HANDLER(UpgradeRequest) {
	static std::string attrs[] = { "", Attr::hp, Attr::attack, Attr::speed, Attr::range };
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());
	NULLCHECK(gameroom);
	Player* player = (Player*)gameroom->getClientUnit(client->id);
	NULLCHECK(player);

	if (player->upgrade(attrs[packet->upgrade_type])) {
		UpgradeNoti noti;
		noti.id = player->id;
		noti.upgrade_type = packet->upgrade_type;
		gameroom->sendPacket(noti);
	}
} END

REGISTER_HANDLER(ChatMessage) {
	auto gameroom = GameRoomManager::getInstance()->getGameRoom(client->getGameRoomId());
	NULLCHECK(gameroom);

	ChatNoti noti;
	strcat_s(noti.msg, packet->msg);

	gameroom->sendPacket(noti);
} END