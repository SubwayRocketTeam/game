class LoginRequest < Packet
  required
  string "id", 31
  string "pw", 31
end
class LoginResponse < Packet
  required
  int "result"
  string "nickname", 31
end