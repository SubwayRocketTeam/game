#include "LuaEngine.h"

static LuaEngine *instance = nullptr;

LuaEngine *LuaEngine::create(){
	instance - new LuaEngine();

	instance->initializePhysics();

	return instance;
}
LuaEngine *LuaEngine::getInstance(){
	return instance;
}

lua_State *LuaEngine::getLua(){
	return ls;
}
