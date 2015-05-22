#ifndef LUA_SDL_OBJECTS_GAMECONTROLLER_H
#define LUA_SDL_OBJECTS_GAMECONTROLLER_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_GameController : public LObject<Lua_SDL_GameController, SDL_GameController *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_GameController, SDL_GameController *, "GameController") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_GameController, "", null_method);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_GameController, SDL_GameController *, "name", getName, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_GameController, SDL_GameController *, "attached", isAttached, null_method);	
		}

		void destructor(lutok::state & s, SDL_GameController * gamecontroller){
			SDL_GameControllerClose(gamecontroller);
		}

		int LOBJECT_METHOD(getName, SDL_GameController * gamecontroller){
			const char * name = SDL_GameControllerName(gamecontroller);
			if (name){
				state.push_string(name);
				return 1;
			}else{
				return 0;
			}
		}
		int LOBJECT_METHOD(isAttached, SDL_GameController * gamecontroller){
			state.push_boolean(SDL_GameControllerGetAttached(gamecontroller) == SDL_TRUE);
			return 1;
		}
	};
}

#endif
