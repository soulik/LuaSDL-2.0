#include "objects/pixelformat.hpp"
#include <lua.hpp>

static int lua_SDL_AllocFormat(lutok::state& state){
	LuaSDL::Lua_SDL_PixelFormat * pf = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_PixelFormat);
	SDL_PixelFormat * pixelformat = SDL_AllocFormat(state.to_integer(1));
	if (pixelformat){
		pf->push(pixelformat);
	}else{
		state.push_boolean(false);
	}
	return 1;
}


void LuaSDL::init_pixelformat(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_PixelFormat);
	module["allocFormat"] = lua_SDL_AllocFormat;
}

