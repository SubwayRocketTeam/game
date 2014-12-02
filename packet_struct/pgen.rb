require 'optparse'
require 'erb'
load 'packet.rb'

src = nil
dsts = nil
OptionParser.new do |opts|
  opts.banner = "Usage: pgen.rb def_file"

  opts.on("-s src", "source file path") do |path|
    src = path
  end
  opts.on("-d path1,path2,...", "specify destination path") do |paths|
    dsts = paths.split(",")
  end
end.parse!

if src == nil or dsts == nil
  exit
end

load src
erb = ERB.new(File.read("outform.erb"))

dsts.each do |outpath|
  puts "out - #{outpath}"
  fp = File.new(outpath, "w:utf-8")
    fp.write erb.result
  fp.close
end