class PacketNone < Packet
  required
end

# INIT
class CheckVersionRequest < Packet
  required
  int "version"
end
class CheckVersionResponse < Packet
  required
  int "result"
end

# LOGIN
class LoginRequest < Packet
  required
  string "nickname", 32
end
class LoginResponse < Packet
  required
  int "client_id"  # 0이면 실패
end

# ROOM
class RoomRequest < Packet
  required
end
class RoomResponse < Packet
  required
  int "room_num"
  string "room_list", 32  # 배열이 없어서 string으로 함
end
class EnterRoom < Packet
  required
  int "room_id"
end
class EnterResponse < Packet
  required
  int "room_id"  # 실패하면 0
end
class EnterNoti < Packet
  required
  int "client_id"
  string "nickname", 32
  int "team_id"
  int "robot_id"
  int "ready"
end
class LeaveRoom < Packet
  required
end
class LeaveNoti < Packet
  required
  int "client_id"
end

# GAME
class SelectRobot < Packet
  required
  int "robot_id"
end
class SelectRobotNoti < Packet
  required
  int "client_id"
  int "robot_id"
end
class SelectTeam < Packet
  required
  int "team_id"
end
class SelectTeamNoti < Packet
  required
  int "client_id"
  int "team_id"
end
class ReadyRequest < Packet
  required
  int "ready"
end
class ReadyNoti < Packet
  required
  int "client_id"
  int "ready"
end
class StartGame < Packet
  required
end
class GameOver < Packet
  required
  int "win_team"
end

# UNIT
class UnitType_ < Enum
  required

  keys [
    :UNIT_NONE,

  :UNIT_PLAYER,
  :UNIT_PLAYER_ME,
  
  :UNIT_TRASH,

  :UNIT_ENEMY,
  :UNIT_REPAIR_AREA,

  :UNIT_MAX
  ]
end

class PlayerType_ < Enum
  required

  keys [
    :PLAYER_NONE,

  :PLAYER_TYPE1,
  :PLAYER_TYPE2,
  :PLAYER_TYPE3,

  :PLAYER_MAX
  ]
end

class EnemyType_ < Enum
  required

  keys [
    :ENEMY_NONE,

  :ENEMY_BASIC,
  :ENEMY_FOLLOW,
  :ENEMY_SPIRAL,
  :ENEMY_EXPLODE,
  :ENEMY_5,
  :ENEMY_6,

  :ENEMY_MAX
  ]
end

class SpawnUnit < Packet
  required
  int "id"
  int "unit_type"
  int "sub_type"
  int "stage"
  float "x"
  float "y"
end
class RemoveUnit < Packet
  required
  int "id"
end

class SetPhysics < Packet
  required
  int "id"
  float "velocity_x"
  float "velocity_y"
  float "acceleration_x"
  float "acceleration_y"
  float "friction"
end

# 쓰레기 이용해서 적 생성 요청
class SpawnRequest < Packet
  required
  int "enemy_type"
end

# BATTLE
class UseSkill < Packet
  required
  int "skill_id"
  float "x"
  float "y"
end
class UseSkillNoti < Packet
  required
  int "id"
  int "skill_id"
  float "x"
  float "y"
end

class AddPassiveNoti < Packet
  required
  int "id"
  int "skill_id"
end

class RemovePassiveNoti < Packet
  required
  int "id"
  int "skill_id"
end

class Attack < Packet
  required
  int "attacker_id"
  int "target_id"
  float "knockback_x"
  float "knockback_y"
  float "attack_position_x"
  float "attack_position_y"
  float "damage"
  float "aggro"
end

# MOVE
class Move < Packet
  required
  float "direction_x"
  float "direction_y"
end
class MoveNoti < Packet
  required
  int "id"
  float "start_x"
  float "start_y"
  float "velocity_x"
  float "velocity_y"
end

class SyncRotation < Packet
  required
  float "angle"
end
class SyncRotationNoti < Packet
  required
  int "id"
  float "angle"
end

class Vacuum < Packet
  required
  int "trash_id"
  int "unit_id"
end

# UPGRADE
class UpgradeType < Enum
  required

  keys [
    :ATTR_NONE,
    :ATTR_HP,
  :ATTR_ATTACK,
  :ATTR_SPEED,
  :ATTR_RANGE
  ]
end

class UpgradeRequest < Packet
  required
  int "upgrade_type"
end

class UpgradeNoti < Packet
  required
  int "id"
  int "upgrade_type"
end

# CHAT
class ChatMessage < Packet
  required
  string "msg", 64
end
class ChatNoti < Packet
  required
  string "msg", 64
end