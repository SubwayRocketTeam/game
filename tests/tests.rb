load 'test_unit.rb'
load '../packet_structure/packet_def.rb'

class LoginTest < RocketTestUnit
  def query
    p = LoginRequest.new
    p.id = "pjc0247"
    p.pw = "asdf1234"
    return p
  end
  def should
    p = LoginResponse.new
    p.nickname = SKIP
    p.result = 1
    return p
  end
end

class EnterRoomTest < RocketTestUnit
  def query
    p = EnterRoom.new
    return p
  end
  def should
    p = EnterNoti.new
    p.client_id = SKIP
    return p
  end
end


RocketTestPool.execute \
  [LoginTest, EnterRoomTest]
