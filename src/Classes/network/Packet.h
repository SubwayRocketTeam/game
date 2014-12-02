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

	PT_SpawnUnit,

	PT_MoveStart,
	PT_MoveStartNoti,
	PT_MoveEnd,
	PT_MoveEndNoti,

	PT_ChatMessage,
	PT_ChatNoti,

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


PACKET(SpawnUnit)
	int id;
	int unit_type;
	float x;
	float y;
END


PACKET(MoveStart)
	float direction_x;
	float direction_y;
END

PACKET(MoveStartNoti)
	int id;
	float start_x;
	float start_y;
	float velocity_x;
	float velocity_y;
END

PACKET(MoveEnd)
	float delta;
END

PACKET(MoveEndNoti)
	int id;
	float end_x;
	float end_y;
END

PACKET(ChatMessage)
	char msg[64];
END
PACKET(ChatNoti)
	char msg[64];
END

#pragma pack (pop)