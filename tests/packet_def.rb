class LoginRequest < Packet
  id 2
  string "id", 31
  string "pw", 31
end
class LoginResponse < Packet
  id 3
  int "result"
  string "nickname", 31
end