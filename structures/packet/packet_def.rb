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
  string "id", 32
  string "pw", 32
end
class LoginResponse < Packet
  required
  int "result"
  string "nickname", 32
end

# ROOM
class EnterRoom < Packet
  required
end
class LeaveRoom < Packet
  required
end
class EnterNoti < Packet
  required
  int "client_id"
  string "nickname", 32
end
class LeaveNoti < Packet
  required
  int "client_id"
end

# GAME
class ReadyRequest < Packet
  required
end
class Ready < Packet
  required
  int "robot_id"
end
class StartGame < Packet
  required
  int "seed" # 랜덤 시드
  int "team" # 팀 넘버 0~1
end

# UNIT
class UnitType_ < Enum
  required

  keys [
    :UNIT_NONE,

	:UNIT_PLAYER,
	:UNIT_PLAYER_ME,
	
	:UNIT_TRASH,
	
	:UNIT_BULLET_PLAYER,
	:UNIT_BULLET_ENEMY,
	
	:UNIT_ENEMY_BASIC,
	:UNIT_ENEMY_FOLLOW,
	:UNIT_ENEMY_SPIRAL,
	:UNIT_ENEMY_EXPLODE,
	:UNIT_ENEMY_5,
	:UNIT_ENEMY_6,

	:UNIT_MAX
  ]
end

class SpawnUnit < Packet
  required
  int "id"
  int "unit_type"
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
  int "unit_type"
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

class Attack < Packet
  required
  int "attacker_id"
  int "target_id"
  float "target_position_x"
  float "target_position_y"
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