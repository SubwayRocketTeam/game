require 'eventmachine'
require 'packet.rb'

class Foo < Packet
  id 3
  int "a"
end

class LoginRequest < Packet
  id 1
  string "user_id", 32
  string "user_pw", 32
end

class LoginResponse < Packet
  id 4
  int "result"
  string "user_nickname", 32
end

module TestClient
  def post_init
    puts "connected"

    f = Foo.new 
    f.a = 5
    send_data f.serialize

    a = LoginRequest.new
    a.user_id = "pjc0247"
    a.user_pw = "asdf1234"
    send_data a.serialize
  end
  def unbind
    puts "disconnected"
  end

  def receive_data data
    size, id = data.unpack("II")

    case id
      when 3
        f = Foo.unserialize data
        puts "foo result #{f.a}"
      when 2
        r = LoginResponse.unserialize data
        puts "login result #{r.result} / #{r.user_nickname}"
    end
  end
end

EventMachine.run {
  EventMachine.connect "localhost", 9916, TestClient
}
