#pragma once

#include "PacketMacro.h"

typedef unsigned int packet_size_t;
typedef unsigned int packet_type_t;

enum PacketType {
	PT_None,
	PT_Example,
	PT_LoginRequest,
	PT_LoginResponse
};

#pragma pack(push, 1)

struct PacketHeader {
	packet_size_t size;
	packet_type_t type;
};

PACKET(Example)
	float x;
	float y;
END

PACKET(LoginRequest)
	char id[32];
	char pw[32];
END

PACKET(LoginResponse)
	int result;
	char nickname[32];
END

#pragma pack(pop)