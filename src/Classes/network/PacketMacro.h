#pragma once

struct packet_header{
	int size;
	int id;
};

#define PACKET(name) \
	struct name : packet_header{\
		name(){ \
			memset(this, 0, sizeof(name)); \
			id = id_##name; \
			size = sizeof(name); \
		};
#define END };

/* type macro */
#define STRING(name) char name[MAX_##name+1]
#define CSTRING(name) const char name[MAX_##name+1]
#define INT(name) int name
#define FLOAT(name) float name
#define CHAR(name) char name

#define LENGTH(name, len) const int MAX_##name = len