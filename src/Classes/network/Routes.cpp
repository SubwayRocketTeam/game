#include "pch.h"
#include "Network.h"

using namespace std;

void Network::initHandlers(){
	//route(PT_LoginResponse, &Network::handleLoginResponse);
	route<EnterNoti>(PT_EnterNoti, 
		std::bind(&Network::handleEnterRoomNoti, this, placeholders::_1));
	route<LeaveNoti>(PT_LeaveNoti,
		std::bind(&Network::handleLeaveRoomNoti, this, placeholders::_1));
	route<SpawnUnit>(PT_SpawnUnit,
		std::bind(&Network::handleSpawn, this, placeholders::_1));
	route<MoveStartNoti>(PT_MoveStartNoti,
		std::bind(&Network::handleMoveStart, this, placeholders::_1));
	route<MoveEndNoti>(PT_MoveEndNoti,
		std::bind(&Network::handleMoveEnd, this, placeholders::_1));
	route<ChatNoti>(PT_ChatNoti,
		std::bind(&Network::handleChatNoti, this, placeholders::_1));
}