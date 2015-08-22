#ifndef LUA_SDL_OBJECTS_CURSOR_H
#define LUA_SDL_OBJECTS_CURSOR_H

#include "common.hpp"

namespace LuaSDL {

	class Cursor : public Object<SDL_Cursor> {
	public:
		explicit Cursor(State * state) : Object<SDL_Cursor>(state) {
			LUTOK_METHOD("set", &Cursor::setCursor);
		}

		void destructor(State & state, SDL_Cursor * cursor){
			SDL_FreeCursor(cursor);
		}

		int setCursor(State & state, SDL_Cursor * cursor);
	};
}

#endif
