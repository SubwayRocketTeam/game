require 'optparse'
require 'erb'
load 'packet.rb'

src = nil
dsts = nil
preview = false
OptionParser.new do |opts|
  opts.banner = "Usage: pgen.rb def_file"

  opts.on("-s src", "source file path") do |path|
    src = path
  end
  opts.on("-d path1,path2,...", "specify destination path") do |paths|
    dsts = paths.split(",")
  end
  opts.on("-p", "preview result") do |v|
    preview = v
  end
end.parse!

if src == nil
  exit
end

load src

puts "PACKETS"
$_packets.each do |packet|
  puts "  %2d - %15s" % [packet.id, packet.name]	
end
puts "\n"

erb = ERB.new(File.read("outform.erb"))

if preview == true
  puts "PREVIEW"
  puts erb.result
  puts "\n"
end

puts "OUTPUTS"
dsts.each do |outpath|
  puts "out - #{outpath}"
  fp = File.new(outpath, "w:utf-8")
    fp.write erb.result
  fp.close
end
