#pragma once

struct packet_header{
	int size;
	int id;
};

#define PACKET(name) \
		struct Packet_##name : PacketHeader{\
		Packet_##name(){ \
			memset(this, 0, sizeof(Packet_##name)); \
			size = sizeof(Packet_##name); \
			type = PT_##name; \
		};
#define END };

/* type macro */
/*
#define STRING(name) char name[MAX_##name+1]
#define CSTRING(name) const char name[MAX_##name+1]
#define INT(name) int name
#define SHORT(name) short name
#define FLOAT(name) float name
#define CHAR(name) char name

#define LENGTH(name, len) const int MAX_##name = len
*/