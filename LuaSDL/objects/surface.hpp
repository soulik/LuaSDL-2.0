#ifndef LUA_SDL_OBJECTS_SURFACE_H
#define LUA_SDL_OBJECTS_SURFACE_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_Surface : public LObject<Lua_SDL_Surface, SDL_Surface*> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_Surface, SDL_Surface*, "Surface") {
			
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Surface, "hasIntersection", null_method);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Surface, SDL_Surface*, "x", null_method, null_method);	

		}

		void destructor(SDL_Surface* surface){
			SDL_FreeSurface(surface);
		}

		int inline LOBJECT_METHOD(equals, SDL_Surface * surface){
			return 0;
		}

	};
}

#endif