#pragma once

#include "PacketMacro.h"

enum PacketID{
	id_login_request = 1,
	id_login_response
};

LENGTH(user_id, 32);
LENGTH(user_pw, 32);
LENGTH(user_nickname, 32);

PACKET(login_request)
	STRING(user_id);
	STRING(user_pw);
END

PACKET(login_response)
	INT(result);
	STRING(user_nickname);
END