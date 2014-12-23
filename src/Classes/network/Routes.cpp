#include "pch.h"
#include "Network.h"

using namespace std;

#define _ROUTE(name) \
	route<name>(PT_##name, \
		std::bind(&Network::handle##name, this, placeholders::_1));

void Network::initHandlers(){

	route<EnterNoti>(PT_EnterNoti, 
		std::bind(&Network::handleEnterRoomNoti, this, placeholders::_1));
	route<LeaveNoti>(PT_LeaveNoti,
		std::bind(&Network::handleLeaveRoomNoti, this, placeholders::_1));
	route<ReadyRequest>(PT_ReadyRequest,
		std::bind(&Network::handleReadyRequest, this, placeholders::_1));
	route<StartGame>(PT_StartGame,
		std::bind(&Network::handleStartGame, this, placeholders::_1));
	route<SpawnUnit>(PT_SpawnUnit,
		std::bind(&Network::handleSpawn, this, placeholders::_1));

	_ROUTE(UseSkillNoti);
	_ROUTE(AddPassiveNoti);
	_ROUTE(Attack);

	_ROUTE(SyncRotationNoti);

	route<RemoveUnit>(PT_RemoveUnit,
		std::bind(&Network::handleRemoveUnit, this, placeholders::_1));
	route<SetPhysics>(PT_SetPhysics,
		std::bind(&Network::handleSetPhysics, this, placeholders::_1));
	route<Vacuum>(PT_Vacuum,
		std::bind(&Network::handleVacuum, this, placeholders::_1));
	route<MoveNoti>(PT_MoveNoti,
		std::bind(&Network::handleMove, this, placeholders::_1));
	route<ChatNoti>(PT_ChatNoti,
		std::bind(&Network::handleChatNoti, this, placeholders::_1));
	route<UpgradeNoti>(PT_UpgradeNoti,
		std::bind(&Network::handleUpgrade, this, placeholders::_1));
}