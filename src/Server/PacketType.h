#pragma once

typedef unsigned int packet_size_t;
typedef unsigned int packet_type_t;

enum PacketType {
	PT_NONE,
	PT_EXAMPLE,
	PT_LOGIN_REQUEST,
	PT_LOGIN_RESPONSE
};

#pragma pack(push, 1)

struct PacketHeader {
	packet_size_t size;
	packet_type_t type;
};

struct Packet_Example : PacketHeader {
	float x;
	float y;
};

struct Packet_LoginRequest : PacketHeader {
	char id[32];
	char pw[32];
};

struct Packet_LoginResponse : PacketHeader {
	int result;
	char nickname[32];
};

#pragma pack(pop)