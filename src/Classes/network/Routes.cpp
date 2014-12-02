#include "pch.h"
#include "Network.h"

using namespace std;

void Network::initHandlers(){
	//route(PT_LoginResponse, &Network::handleLoginResponse);
	route<EnterNoti>(PT_EnterNoti, 
		std::bind(&Network::handleEnterRoomNoti, this, placeholders::_1));
	route<LeaveNoti>(PT_LeaveNoti,
		std::bind(&Network::handleLeaveRoomNoti, this, placeholders::_1));
	route<Spawn>(PT_Spawn,
		std::bind(&Network::handleSpawn, this, placeholders::_1));
	route<MoveStartResponse>(PT_MoveStartResponse,
		std::bind(&Network::handleMoveStart, this, placeholders::_1));
	route<MoveEndResponse>(PT_MoveEndResponse,
		std::bind(&Network::handleMoveEnd, this, placeholders::_1));
}