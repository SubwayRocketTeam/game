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

#define PACKET_VERSION 727443075

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
  PT_AddPassiveNoti = 18,
  PT_RemovePassiveNoti = 19,
  PT_Attack = 20,
  PT_Move = 21,
  PT_MoveNoti = 22,
  PT_SyncRotation = 23,
  PT_SyncRotationNoti = 24,
  PT_Vacuum = 25,
  PT_UpgradeRequest = 26,
  PT_UpgradeNoti = 27,
  PT_ChatMessage = 28,
  PT_ChatNoti = 29,

  PT_PacketMax
};

/* ENUMS */
enum UnitType_{
  
  UNIT_NONE,
  UNIT_PLAYER,
  UNIT_PLAYER_ME,
  UNIT_TRASH,
  UNIT_ENEMY,
  UNIT_REPAIR_AREA,
  UNIT_MAX,
};
enum PlayerType_{
  
  PLAYER_NONE,
  PLAYER_TYPE1,
  PLAYER_TYPE2,
  PLAYER_TYPE3,
  PLAYER_MAX,
};
enum EnemyType_{
  
  ENEMY_NONE,
  ENEMY_BASIC,
  ENEMY_FOLLOW,
  ENEMY_SPIRAL,
  ENEMY_EXPLODE,
  ENEMY_5,
  ENEMY_6,
  ENEMY_MAX,
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
  int sub_type;
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
  int enemy_type;
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

PACKET(AddPassiveNoti)
  int id;
  int skill_id;
END

PACKET(RemovePassiveNoti)
  int id;
  int skill_id;
END

PACKET(Attack)
  int attacker_id;
  int target_id;
  float knockback_x;
  float knockback_y;
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
