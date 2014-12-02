#include "pch.h"
#include "Network.h"

using namespace std;

void Network::initHandlers(){
	//route(PT_LoginResponse, &Network::handleLoginResponse);
	route<EnterNoti>(PT_EnterNoti, 
		std::bind(&Network::handleEnterRoomNoti, this, placeholders::_1));
	route<LeaveNoti>(PT_LeaveNoti,
		std::bind(&Network::handleLeaveRoomNoti, this, placeholders::_1));
}