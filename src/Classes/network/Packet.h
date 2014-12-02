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

	PT_Spawn,

	PT_MoveStartRequest,
	PT_MoveStartResponse,
	PT_MoveEndRequest,
	PT_MoveEndResponse,

	PT_MAX
};

#pragma pack (push, 1)

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


PACKET(Spawn)
	int id;
	float x;
	float y;
END


PACKET(MoveStartRequest)
	int id;
	float direction_x;
	float direction_y;
END

PACKET(MoveStartResponse)
	int id;
	float start_x;
	float start_y;
	float velocity_x;
	float velocity_y;
END

PACKET(MoveEndRequest)
	int id;
END

PACKET(MoveEndResponse)
	int id;
	float end_x;
	float end_y;
END

#pragma pack (pop)