﻿class PacketNone < Packet
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
    :NONE,
    :PLAYER
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

class FireBullet < Packet
  required
  int "bullet_type"
  float "x"
  float "y"
  float "direction_x"
  float "direction_y"
end
class FireBulletNoti < Packet
  required
  int "id"
  int "team"
  int "bullet_type"
  float "x"
  float "y"
  float "velocity_x"
  float "velocity_y"
end

# MOVE
class MoveStart < Packet
  required
  float "direction_x"
  float "direction_y"
end
class MoveEnd < Packet
  required
end
class MoveStartNoti < Packet
  required
  int "id"
  float "velocity_x"
  float "velocity_y"
end
class MoveEndNoti < Packet
  required
  int "id"
  float "end_x"
  float "end_y"
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

# CHAT
class ChatMessage < Packet
  required
  string "msg", 64
end
class ChatNoti < Packet
  required
  string "msg", 64
end