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

#define PACKET_VERSION 2380389444

enum packet_id{
  PT_PacketNone = 0,
  PT_CheckVersionRequest = 1,
  PT_CheckVersionResponse = 2,
  PT_LoginRequest = 3,
  PT_LoginResponse = 4,
  PT_EnterRoom = 5,
  PT_LeaveRoom = 6,
  PT_EnterNoti = 7,
  PT_LeaveNoti = 8,
  PT_ReadyRequest = 9,
  PT_Ready = 10,
  PT_StartGame = 11,
  PT_SpawnUnit = 12,
  PT_RemoveUnit = 13,
  PT_FireBullet = 14,
  PT_FireBulletNoti = 15,
  PT_MoveStart = 16,
  PT_MoveEnd = 17,
  PT_MoveStartNoti = 18,
  PT_MoveEndNoti = 19,
  PT_ChatMessage = 20,
  PT_ChatNoti = 21,

  PT_PacketMax
};

/* ENUMS */
enum UnitType_{
  
  NONE,
  PLAYER,
};

/* PACKETS */
#pragma pack (push, 1)

PACKET(PacketNone)
END

PACKET(CheckVersionRequest)
  int version;
END

PACKET(CheckVersionResponse)
  int result;
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

PACKET(ReadyRequest)
END

PACKET(Ready)
END

PACKET(StartGame)
  int seed;
  int team;
END

PACKET(SpawnUnit)
  int id;
  int unit_type;
  int stage;
  float x;
  float y;
END

PACKET(RemoveUnit)
  int id;
END

PACKET(FireBullet)
  int bullet_type;
  float x;
  float y;
  float direction_x;
  float direction_y;
END

PACKET(FireBulletNoti)
  int id;
  int team;
  int bullet_type;
  float x;
  float y;
  float velocity_x;
  float velocity_y;
END

PACKET(MoveStart)
  float direction_x;
  float direction_y;
END

PACKET(MoveEnd)
END

PACKET(MoveStartNoti)
  int id;
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
