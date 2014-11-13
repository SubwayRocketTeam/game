#pragma once

#include "PacketMacro.h"

enum PacketID{
	id_login_request = 1,
	id_login_response,

	id_room_enter = 100,
	id_room_entered,
	id_room_leave,
	id_room_left,

	id_move_start = 200,
	id_move_end,

	id_unit_spawn = 300,
	id_unit_remove,

	id_sync_position = 400
};

LENGTH(user_id, 32);
LENGTH(user_pw, 32);
LENGTH(user_nickname, 32);

/* LOGIN */
PACKET(login_request)
	STRING(user_id);
	STRING(user_pw);
END
PACKET(login_response)
	INT(result);
	STRING(user_nickname);
END

/* ROOM */
PACKET(room_enter)
END
PACKET(room_entered)
	INT(room_id);
	INT(user_id);
END
PACKET(room_leave)
END
PACKET(room_left)
	INT(room_id);
	INT(user_id);
END

/* MOVE */
PACKET(move_start)
	INT(x);
	INT(y);
	INT(timestamp);
END
PACKET(move_end)
	INT(timestamp);
END

/* UNIT */
PACKET(unit_spawn)
	INT(id);
	INT(type);
	INT(x);
	INT(y);
END
PACKET(unit_remove)
	INT(id);
END

PACKET(sync_position)
	INT(user_id);
	INT(x);
	INT(y);
END