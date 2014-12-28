#include "pch.h"
#include "Network.h"

using namespace std;

#define _ROUTE(name) \
	route<name>(PT_##name, \
		std::bind(&Network::handle##name, this, placeholders::_1));

void Network::initHandlers(){

	_ROUTE(RoomResponse);
	_ROUTE(EnterResponse);
	_ROUTE(EnterNoti);
	_ROUTE(LeaveNoti);
	_ROUTE(SelectRobotNoti);
	_ROUTE(SelectTeamNoti);
	_ROUTE(ReadyNoti);
	_ROUTE(StartGame);
	_ROUTE(GameOver);
	
	route<SpawnUnit>(PT_SpawnUnit,
		std::bind(&Network::handleSpawn, this, placeholders::_1));

	_ROUTE(UseSkillNoti);
	_ROUTE(AddPassiveNoti);
	_ROUTE(RemovePassiveNoti);
	_ROUTE(Attack);

	_ROUTE(SyncRotationNoti);

	_ROUTE(RemoveUnit);
	_ROUTE(SetPhysics);
	_ROUTE(Vacuum);

	route<MoveNoti>(PT_MoveNoti,
		std::bind(&Network::handleMove, this, placeholders::_1));

	_ROUTE(ChatNoti);

	route<UpgradeNoti>(PT_UpgradeNoti,
		std::bind(&Network::handleUpgrade, this, placeholders::_1));
}