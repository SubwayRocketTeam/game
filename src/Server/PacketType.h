#pragma once

typedef unsigned short packet_size_t;
typedef unsigned short packet_type_t;

enum PacketType {
	PT_NONE,
	PT_EXAMPLE
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

#pragma pack(pop)