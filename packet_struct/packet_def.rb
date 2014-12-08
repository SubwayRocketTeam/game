class PacketNone < Packet
  required
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
end
class StartGame < Packet
	required
end

# UNIT
class SpawnUnit < Packet
  required
  int "id"
  int "unit_type"
  float "x"
  float "y"
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
  float "start_x"
  float "start_y"
  float "velocity_x"
  float "velocity_y"
end
class MoveEndNoti < Packet
  required
  int "id"
  float "end_x"
  float "end_y"
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