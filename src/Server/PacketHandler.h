#pragma once

#include "PacketType.h"

struct PacketHeader;
class Client;

typedef void PacketHandler(Client*, PacketHeader*);

class PacketHandlerMap {
public:
	static PacketHandler* function(packet_type_t type);
};

