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

#define PACKET_VERSION 1504106776

enum packet_id{
  PT_PacketNone = 0,
  PT_CheckVersionRequest = 1,
  PT_CheckVersionResponse = 2,
  PT_LoginRequest = 3,
  PT_LoginResponse = 4,
  PT_RoomRequest = 5,
  PT_RoomResponse = 6,
  PT_EnterRoom = 7,
  PT_EnterResponse = 8,
  PT_EnterNoti = 9,
  PT_LeaveRoom = 10,
  PT_LeaveNoti = 11,
  PT_SelectRobot = 12,
  PT_SelectRobotNoti = 13,
  PT_SelectTeam = 14,
  PT_SelectTeamNoti = 15,
  PT_ReadyRequest = 16,
  PT_ReadyNoti = 17,
  PT_StartGame = 18,
  PT_GameOver = 19,
  PT_SpawnUnit = 20,
  PT_RemoveUnit = 21,
  PT_SetPhysics = 22,
  PT_SpawnRequest = 23,
  PT_UseSkill = 24,
  PT_UseSkillNoti = 25,
  PT_AddPassiveNoti = 26,
  PT_RemovePassiveNoti = 27,
  PT_Attack = 28,
  PT_Move = 29,
  PT_MoveNoti = 30,
  PT_SyncRotation = 31,
  PT_SyncRotationNoti = 32,
  PT_Vacuum = 33,
  PT_UpgradeRequest = 34,
  PT_UpgradeNoti = 35,
  PT_ChatMessage = 36,
  PT_ChatNoti = 37,

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
  char nickname[33];
END

PACKET(LoginResponse)
  int client_id;
END

PACKET(RoomRequest)
END

PACKET(RoomResponse)
  int room_num;
  char room_list[33];
END

PACKET(EnterRoom)
  int room_id;
END

PACKET(EnterResponse)
  int room_id;
END

PACKET(EnterNoti)
  int client_id;
  char nickname[33];
  int team_id;
END

PACKET(LeaveRoom)
END

PACKET(LeaveNoti)
  int client_id;
END

PACKET(SelectRobot)
  int robot_id;
END

PACKET(SelectRobotNoti)
  int client_id;
  int robot_id;
END

PACKET(SelectTeam)
  int team_id;
END

PACKET(SelectTeamNoti)
  int client_id;
  int team_id;
END

PACKET(ReadyRequest)
  int ready;
END

PACKET(ReadyNoti)
  int client_id;
  int ready;
END

PACKET(StartGame)
END

PACKET(GameOver)
  int win_team;
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
