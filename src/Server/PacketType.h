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

#define PACKET_VERSION 2650831630

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
  PT_SetPhysics = 14,
  PT_SpawnRequest = 15,
  PT_UseSkill = 16,
  PT_UseSkillNoti = 17,
  PT_Attack = 18,
  PT_Move = 19,
  PT_MoveNoti = 20,
  PT_SyncRotation = 21,
  PT_SyncRotationNoti = 22,
  PT_Vacuum = 23,
  PT_UpgradeRequest = 24,
  PT_UpgradeNoti = 25,
  PT_ChatMessage = 26,
  PT_ChatNoti = 27,

  PT_PacketMax
};

/* ENUMS */
enum UnitType_{
  
  UNIT_NONE,
  UNIT_PLAYER,
  UNIT_PLAYER_ME,
  UNIT_TRASH,
  UNIT_BULLET_PLAYER,
  UNIT_BULLET_ENEMY,
  UNIT_ENEMY_BASIC,
  UNIT_ENEMY_FOLLOW,
  UNIT_ENEMY_SPIRAL,
  UNIT_ENEMY_EXPLODE,
  UNIT_ENEMY_5,
  UNIT_ENEMY_6,
  UNIT_MAX,
};
enum UpgradeType{
  
  ATTR_NONE,
  ATTR_HP,
  ATTR_ATTACK,
  ATTR_SPEED,
  ATTR_RANGE,
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
  char nickname[33];
END

PACKET(LeaveNoti)
  int client_id;
END

PACKET(ReadyRequest)
END

PACKET(Ready)
  int robot_id;
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

PACKET(SetPhysics)
  int id;
  float velocity_x;
  float velocity_y;
  float acceleration_x;
  float acceleration_y;
  float friction;
END

PACKET(SpawnRequest)
  int unit_type;
END

PACKET(UseSkill)
  int skill_id;
  float x;
  float y;
END

PACKET(UseSkillNoti)
  int id;
  int skill_id;
  float x;
  float y;
END

PACKET(Attack)
  int attacker_id;
  int target_id;
  float target_position_x;
  float target_position_y;
  float attack_position_x;
  float attack_position_y;
  float damage;
  float aggro;
END

PACKET(Move)
  float direction_x;
  float direction_y;
END

PACKET(MoveNoti)
  int id;
  float start_x;
  float start_y;
  float velocity_x;
  float velocity_y;
END

PACKET(SyncRotation)
  float angle;
END

PACKET(SyncRotationNoti)
  int id;
  float angle;
END

PACKET(Vacuum)
  int trash_id;
  int unit_id;
END

PACKET(UpgradeRequest)
  int upgrade_type;
END

PACKET(UpgradeNoti)
  int id;
  int upgrade_type;
END

PACKET(ChatMessage)
  char msg[65];
END

PACKET(ChatNoti)
  char msg[65];
END

#pragma pack (pop)
