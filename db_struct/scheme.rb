require 'data-mapper'

class Account
  include DataMapper::Resource

  property :id, Serial
  property :user_id, String, :length => 32
  property :user_pw, String, :length => 32
  property :nickname, String, :length => 16

  has n, :battlelogs
end

class Battlelog
  include DataMapper::Resource

  property :id, Serial
  property :timestamp, DateTime

  belongs_to :account
end