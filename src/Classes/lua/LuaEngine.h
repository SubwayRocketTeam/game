#pragma once

#include "lua.h"

class LuaEngine{
public:
	static LuaEngine *create();
	static LuaEngine *getInstance();

	lua_State *getLua();

private:
	bool initializePhysics();

private:
	lua_State *ls;
};