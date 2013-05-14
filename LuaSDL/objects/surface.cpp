#include "objects/surface.hpp"
#include <lua.hpp>

void LuaSDL::init_surface(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	//module["enclosePoints"] = lua_SDL_EnclosePoints;
}
