#ifndef LUA_SDL_OBJECTS_CURSOR_H
#define LUA_SDL_OBJECTS_CURSOR_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_Cursor : public LObject<Lua_SDL_Cursor, SDL_Cursor *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_Cursor, SDL_Cursor *, "Cursor") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Cursor, "set", setCursor);
			//LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Cursor, SDL_Cursor *, "", null_method, null_method);	
		}

		void destructor(lutok::state & s, SDL_Cursor * cursor){
			SDL_FreeCursor(cursor);
		}

		int LOBJECT_METHOD(setCursor, SDL_Cursor * cursor){
			SDL_SetCursor(cursor);
			return 0;
		}
	};
}

#endif
