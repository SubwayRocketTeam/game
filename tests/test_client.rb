require 'eventmachine'
load 'packet.rb'

class LoginRequest < Packet
  id 5
  string "id", 31
  string "pw", 31
end

class LoginResponse < Packet
  id 6
  int "result"
  string "nickname", 31
end

class EnterRoom < Packet
  id 7
end

class EnterNoti < Packet
  id 8
  int "client_id"
end

class LeaveNoti < Packet
  id 6
  int "client_id"
end

class MoveStart < Packet
  id 11
  float "velocity_x"
  float "velocity_y"
end
class MoveStartNoti < Packet
  id 12
  int "user_id"
  float "start_x"
  float "start_y"
  float "velocity_x"
  float "velocity_y"
end

class MoveEnd < Packet
  id 13
  float "delta"
end
class MoveEndNoti < Packet
  id 14
  int "user_id"
  float "end_x"
  float "end_y"
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

	a = MoveStart.new
	a.velocity_x = 0.7
	a.velocity_y = 0.7
	send_data a.serialize

  end
  def unbind
    puts "disconnected"
  end

  def receive_packet data
    size, id = data.unpack("II")
    case id
      when 6
        r = LoginResponse.unserialize data
        puts "login result #{r.result} / #{r.nickname}"
	  when 8
        r = EnterNoti.unserialize data
        puts "Enter #{r.client_id}"
	  when 9
        r = LeaveNoti.unserialize data
        puts "Leave #{r.client_id}"
	  when 12
	    r = MoveStartNoti.unserialize data
		a = MoveEnd.new
		send_data a.serialize
		puts "Move Start Noti #{r.user_id}"
	  when 14
	    r = MoveEndNoti.unserialize data
		puts "Move End Noti #{r.end_x}, #{r.end_y}"
		a = MoveStart.new
		a.velocity_x = 0.7
		a.velocity_y = 0.7
		send_data a.serialize
    end
  end
end

EventMachine.run {
  EventMachine.connect "localhost", 4321, TestClient
}