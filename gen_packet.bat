cd packet_struct
ruby pgen.rb -s packet_def.rb -d ..\src\server\Packet.h,..\src\Classes\network\Packet.h
pause
