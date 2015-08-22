#ifndef LUA_SDL_OBJECTS_GAMECONTROLLER_H
#define LUA_SDL_OBJECTS_GAMECONTROLLER_H

#include "common.hpp"

namespace LuaSDL {

	class GameController : public Object<SDL_GameController> {
	public:
		explicit GameController(State * state) : Object<SDL_GameController>(state) {
			//LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_GameController, "", null_method);
			LUTOK_PROPERTY("name", &GameController::getName, &GameController::nullMethod);	
			LUTOK_PROPERTY("attached", &GameController::isAttached, &GameController::nullMethod);	
		}

		SDL_GameController * constructor(State & state, bool & managed);

		void destructor(State & state, SDL_GameController * gamecontroller){
			SDL_GameControllerClose(gamecontroller);
		}

		int getName(State & state, SDL_GameController * gamecontroller);
		int isAttached(State & state, SDL_GameController * gamecontroller);
	};
}

#endif
