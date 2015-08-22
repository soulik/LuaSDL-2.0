#include "objects/cursor.hpp"
#include "objects/surface.hpp"
#include <lua.hpp>

namespace LuaSDL {
	int Cursor::setCursor(State & state, SDL_Cursor * cursor) {
		Stack * stack = state.stack;
		SDL_SetCursor(cursor);
		return 0;
	}

	static int lua_SDL_CreateColorCursor(State & state){
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		Cursor * interfaceCursor = state.getInterface<Cursor>("LuaSDL_Cursor");

		SDL_Surface * s = interfaceSurface->get(1);
		if (s){
			interfaceCursor->push(
				SDL_CreateColorCursor(
				s,
				stack->to<int>(2),
				stack->to<int>(3)), true
			);
			return 1;
		}
		return 0;
	}
	static int lua_SDL_CreateCursor(State & state){
		Stack * stack = state.stack;
		Cursor * interfaceCursor = state.getInterface<Cursor>("LuaSDL_Cursor");

		interfaceCursor->push(
			SDL_CreateCursor(
			(const Uint8*)stack->to<void*>(1),
			(const Uint8*)stack->to<void*>(2),
			stack->to<int>(3),
			stack->to<int>(4),
			stack->to<int>(5),
			stack->to<int>(6)
			), true
		);
		return 1;
	}

	static int lua_SDL_GetCursor(State & state){
		Stack * stack = state.stack;
		Cursor * interfaceCursor = state.getInterface<Cursor>("LuaSDL_Cursor");
		interfaceCursor->push(SDL_GetCursor());
		return 1;
	}

	static int lua_SDL_ShowCursor(State & state){
		Stack * stack = state.stack;
		int retval = SDL_ShowCursor(stack->to<int>(1));
		if (retval >= 0){
			stack->push<bool>(retval == 1);
			return 1;
		}
		else{
			return 0;
		}
	}


	void initCursor(State * state, Module & module){
		INIT_OBJECT(Cursor);
		module["createCursor"] = lua_SDL_CreateCursor;
		module["createColorCursor"] = lua_SDL_CreateColorCursor;
		module["getCursor"] = lua_SDL_GetCursor;
		module["showCursor"] = lua_SDL_ShowCursor;
	}

};
