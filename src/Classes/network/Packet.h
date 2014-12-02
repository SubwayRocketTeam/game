#pragma once

#include "PacketMacro.h"

enum PacketID{
	PT_None,
	PT_Example,
	PT_LoginRequest,
	PT_LoginResponse,
	PT_EnterRoom,
	PT_EnterNoti,
	PT_LeaveNoti,
};

PACKET(LoginRequest)
	char id[32];
	char pw[32];
END

PACKET(LoginResponse)
	int result;
	char nickname[32];
END

PACKET(EnterRoom)
END

PACKET(EnterNoti)
	int clientId;
END

PACKET(LeaveNoti)
	int clientId;
END