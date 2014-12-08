require 'eventmachine'
load 'packet.rb'
load 'packet_protocol.rb'

class RocketTestPool
  def self.tests
  	return @@tests
  end
  def self.passed
  	return @@passed
  end
  def self.passed= v
  	return @@passed = v
  end
  def self.failed
  	return @@failed
  end
  def self.failed= v
  	return @@failed = v
  end

  def self.execute tests
    @@passed = 0
    @@failed = 0
    @@tests = tests

  	EventMachine.run {
     EventMachine.connect "localhost", 4321, TestClient
     tests.first.new.execute
    }
  end
end

module TestClient
  include PacketProtocol
  attr_accessor :should
  attr_accessor :callback

  def post_init
    $_client = self
  end
  def unbind
  end

  def receive_packet data
    size, id = data.unpack("II")
    
    if @should.class.id == id
      @callback.call data
    end
  end
end

class RocketTestUnit
  SKIP = :skip_test

  def self.pre_test test
    
  end
  def self.post_test test
		
  end

  def query
  end
  def should
  end

  def check packet
    should_packet = should
    resp_packet = should_packet.class.unserialize packet
    passed = true

    should_packet.class.items.each do |var|
      sym = ("@" + var[0]).to_sym
      a = should_packet.instance_variable_get sym
      b = resp_packet.instance_variable_get sym

      next if a == SKIP

      if a != b
        puts \
          "Failed #{self.class.name} - " \
          "#{var[0]} is '#{b}' (expected '#{a}')"
        passed = false
      end
    end

    if passed == true
     puts \
        "Passed #{self.class.name} - " \
        "#{Time.new.to_f - @tick} sec"
        return true
    else
    	return false
    end
  end
  
  def post_test packet
    if check(packet) == true
      RocketTestPool.passed += 1
    else
      RocketTestPool.failed += 1
    end

    RocketTestPool.tests.shift
    test = RocketTestPool.tests.first
    if test == nil
      puts "Passed : #{RocketTestPool.passed} / Faild : #{RocketTestPool.failed}"
    else
      test.new.execute
    end
  end

  def execute
    qry_packet = query
    resp_packet = should
    
    @tick = Time.new.to_f
    $_client.should = resp_packet
    $_client.callback = method(:post_test)
    $_client.send_packet qry_packet
  end
end

RocketTestPool.execute \
  [LoginTest, EnterRoomTest]



