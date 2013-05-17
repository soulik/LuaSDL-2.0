#include "objects/cursor.hpp"
#include <lua.hpp>

static int lua_SDL_CreateColorCursor(lutok::state& state){
	LuaSDL::Lua_SDL_Surface * s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	LuaSDL::Lua_SDL_Cursor * c = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Cursor);
	c->push(
		SDL_CreateColorCursor(
			s->check(1),
			state.to_integer(2),
			state.to_integer(3)));
	return 1;
}
static int lua_SDL_CreateCursor(lutok::state& state){
	LuaSDL::Lua_SDL_Cursor * c = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Cursor);

	c->push(
		SDL_CreateCursor(
			(const Uint8* )state.to_lightuserdata(1),
			(const Uint8* )state.to_lightuserdata(2),
			state.to_integer(3),
			state.to_integer(4),
			state.to_integer(5),
			state.to_integer(6)
		));
	return 1;
}
static int lua_SDL_GetCursor(lutok::state& state){
	LuaSDL::Lua_SDL_Cursor * c = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Cursor);
	c->push(SDL_GetCursor());
	return 1;
}
static int lua_SDL_ShowCursor(lutok::state& state){
	int retval = SDL_ShowCursor(state.to_integer(1));
	if (retval >=0){
		state.push_boolean(retval == 1);
		return 1;
	}else{
		return 0;
	}
}


void LuaSDL::init_cursor(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Cursor);
	module["createCursor"] = lua_SDL_CreateCursor;
	module["createColorCursor"] = lua_SDL_CreateColorCursor;
	module["getCursor"] = lua_SDL_GetCursor;
	module["showCursor"] = lua_SDL_ShowCursor;
}
