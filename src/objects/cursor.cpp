#include "objects/cursor.hpp"
#include "objects/surface.hpp"
#include <lua.hpp>

static int lua_SDL_CreateColorCursor(State & state){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	LuaSDL::Lua_SDL_Cursor & c = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Cursor);
	c.push(
		SDL_CreateColorCursor(
			s.check(1),
			stack->to<int>(2),
			stack->to<int>(3)));
	return 1;
}
static int lua_SDL_CreateCursor(State & state){
	LuaSDL::Lua_SDL_Cursor & c = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Cursor);

	c.push(
		SDL_CreateCursor(
			(const Uint8* )state.to_lightuserdata(1),
			(const Uint8* )state.to_lightuserdata(2),
			stack->to<int>(3),
			stack->to<int>(4),
			stack->to<int>(5),
			stack->to<int>(6)
		));
	return 1;
}
static int lua_SDL_GetCursor(State & state){
	LuaSDL::Lua_SDL_Cursor & c = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Cursor);
	c.push(SDL_GetCursor());
	return 1;
}
static int lua_SDL_ShowCursor(State & state){
	int retval = SDL_ShowCursor(stack->to<int>(1));
	if (retval >=0){
		stack->push<bool>(retval == 1);
		return 1;
	}else{
		return 0;
	}
}


void LuaSDL::init_cursor(State & state, Module & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Cursor);
	module["createCursor"] = lua_SDL_CreateCursor;
	module["createColorCursor"] = lua_SDL_CreateColorCursor;
	module["getCursor"] = lua_SDL_GetCursor;
	module["showCursor"] = lua_SDL_ShowCursor;
}
