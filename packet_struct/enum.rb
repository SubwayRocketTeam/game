$_enums = Array.new

class Enum
  def self.required
    $_enums << self

    items = Array.new

    define_singleton_method "items" do
      return items
    end
  end

  def self.keys ary
    self.items.concat ary
  end
end

