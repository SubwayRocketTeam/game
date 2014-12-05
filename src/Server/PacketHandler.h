#pragma once

#include "PacketType.h"

struct PacketHeader;
struct Client;

typedef void PacketHandler(Client*, PacketHeader*);

class PacketHandlerMap {
public:
	static PacketHandler* function(packet_type_t type);
};

