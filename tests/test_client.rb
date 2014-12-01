require 'eventmachine'
load 'packet.rb'

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

class EnterRoom < Packet
  id 4
end

class EnterNoti < Packet
  id 5
  int "client_id"
end

class LeaveNoti < Packet
  id 6
  int "client_id"
end

module GeniusProtocol
  def receive_data data
    (@buf||= '') << data

	while @buf.size >= 4
	  if @buf.size >= (size=@buf.unpack('I').first)
	    receive_packet @buf.slice! 0, size
	  end
	end
  end

  def receive_packet packet
    # override me
  end
end

module TestClient
  include GeniusProtocol

  def post_init
    puts "connected"

    a = LoginRequest.new
    a.id = "pjc0247"
    a.pw = "1234"
    send_data a.serialize

    a = EnterRoom.new
    send_data a.serialize

  end
  def unbind
    puts "disconnected"
  end

  def receive_packet data
    size, id = data.unpack("II")
    case id
      when 3
        r = LoginResponse.unserialize data
        puts "login result #{r.result} / #{r.nickname}"
	  when 5
        r = EnterNoti.unserialize data
        puts "Enter #{r.client_id}"
	  when 6
        r = LeaveNoti.unserialize data
        puts "Leave #{r.client_id}"
    end
  end
end

EventMachine.run {
  EventMachine.connect "localhost", 4321, TestClient
}
