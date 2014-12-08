/* pgen auto-generated packets */
#pragma once

typedef int packet_type_t;
typedef int packet_size_t;

struct PacketHeader{
  packet_size_t size;
  packet_type_t type;
};
#define PACKET(name) \
  struct name : PacketHeader{\
    name(){ \
      memset(this, 0, sizeof(name)); \
      type = PT_##name; \
      size = sizeof(name); \
    };
#define END };

enum packet_id{

  PT_PacketNone = 0,
  PT_LoginRequest = 1,
  PT_LoginResponse = 2,
  PT_EnterRoom = 3,
  PT_LeaveRoom = 4,
  PT_EnterNoti = 5,
  PT_LeaveNoti = 6,
  PT_StartGame = 7,
  PT_SpawnUnit = 8,
  PT_MoveStart = 9,
  PT_MoveEnd = 10,
  PT_MoveStartNoti = 11,
  PT_MoveEndNoti = 12,
  PT_ChatMessage = 13,
  PT_ChatNoti = 14,

  PT_PacketMax
};

#pragma pack (push, 1)

PACKET(PacketNone)
END

PACKET(LoginRequest)
  char id[33];
  char pw[33];
END

PACKET(LoginResponse)
  int result;
  char nickname[33];
END

PACKET(EnterRoom)
END

PACKET(LeaveRoom)
END

PACKET(EnterNoti)
  int client_id;
END

PACKET(LeaveNoti)
  int client_id;
END

PACKET(StartGame)
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

PACKET(MoveEnd)
END

PACKET(MoveStartNoti)
  int id;
  float start_x;
  float start_y;
  float velocity_x;
  float velocity_y;
END

PACKET(MoveEndNoti)
  int id;
  float end_x;
  float end_y;
END

PACKET(ChatMessage)
  char msg[65];
END

PACKET(ChatNoti)
  char msg[65];
END

#pragma pack (pop)
