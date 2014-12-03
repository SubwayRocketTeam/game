module PacketProtocol
  def receive_data data
    (@buf||= '') << data

	while @buf.size >= 4
	  if @buf.size >= (size=@buf.unpack('I').first)
	    receive_packet @buf.slice! 0, size
	  end
	end
  end

  def send_packet packet
	send_data packet.serialize
  end
  def receive_packet packet
    # override me
  end
end