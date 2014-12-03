/* pgen auto-generated packets */
#pragma once

struct PacketHeader{
  int size;
  int id;
};
#define PACKET(name) \
  struct name : PacketHeader{\
    name(){ \
      memset(this, 0, sizeof(name)); \
      id = id_##name; \
      size = sizeof(name); \
    };
#define END };

enum packet_id{

  id_LoginRequest = 1,
  id_LoginResponse = 2,
}

#pragma pack (push, 1)

PACKET(LoginRequest)
  char id[33];
  char pw[33];
END

PACKET(LoginResponse)
  int result;
  char nickname[33];
END

#pragma pack (pop)
