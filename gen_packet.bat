cd packet_struct
ruby pgen.rb -s packet_def.rb -d ..\src\server\PacketType.h,..\src\Classes\network\Packet.h
pause
