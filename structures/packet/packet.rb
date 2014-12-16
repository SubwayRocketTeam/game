$_packets = Array.new

class Packet
  def initialize
    self.class.items.each do |item|
      instance_variable_set ("@" + item[0]).to_sym, item[1]

      self.class.class_eval {
        attr_accessor (item[0]).to_sym
      }
    end
  end

  def serialize
    header = Array.new
    ary = Array.new
    size = 0

    self.class.items.each do |item|
      key = item[0]; value = item[1]
      type = item[2]

      ary.push instance_variable_get ("@"+key).to_sym

      case type
        when "int"
          size += 4
        when "string"
          size += item[3]+1
		when "float"
		  size += 4
      end
      
    end

    header.push size + 8
    header.push self.class.id
    
    (header+ary).pack self.class.fmt
  end

  def self.dump
    body = "PACKET(#{self.name})\n"

    self.items.each do |item|
      key = item[0]; value = item[1]
      type = item[2]

      case type
		when "string"
          body += "  char #{key}[#{item[3]+1}];\n"
	    else
          body += "  #{type} #{key};\n"	
      end
	end

    body += "END"
    return body
  end

  def self.unserialize data
    result = data.unpack(self.fmt)

    obj = self.new
    for i in 0..result.size-3
      key = self.items[i][0]
      
      obj.instance_variable_set ("@"+key).to_sym, result[i+2]
    end

    return obj
  end

  def self.required
    $_packets << self
    
    id = $_packets.size - 1
    items = Array.new
    fmt = String.new("II")
    define_singleton_method "id" do
      return id
    end
    define_singleton_method "items" do
      return items
    end
    define_singleton_method "fmt" do
      return fmt
    end
  end

  def self.int key, value=0
    self.fmt.concat "I"
    self.items.push([key, value, "int"])
  end
  def self.string key, size, value=""
    self.fmt.concat "a"+(size+1).to_s
    self.items.push([key, value, "string", size])
  end
  def self.float key, value=0
	self.fmt.concat "F"
	self.items.push([key, value, "float"])
  end
end