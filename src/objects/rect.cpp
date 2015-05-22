#include "objects/rect.hpp"
#include <lua.hpp>

static int lua_SDL_EnclosePoints(State & state){
	return 0;
}

static int lua_SDL_Rect(State & state){
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	r.push(new SDL_Rect);
	return 1;
}

void LuaSDL::init_rect(State & state, Module & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	module["Rect"] = lua_SDL_Rect;
	//module["enclosePoints"] = lua_SDL_EnclosePoints;
}
