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

			LUTOK_METHOD("axis", &GameController::getAxis);
			LUTOK_METHOD("button", &GameController::getButton);
			
			LUTOK_METHOD("bindForAxis", &GameController::getBindForAxis);
			LUTOK_METHOD("bindForButton", &GameController::getBindForButton);

			LUTOK_PROPERTY("joystick", &GameController::getJoystick, &GameController::nullMethod);
			LUTOK_PROPERTY("mapping", &GameController::getMapping, &GameController::setMapping);
		}

		SDL_GameController * constructor(State & state, bool & managed);

		void destructor(State & state, SDL_GameController * gamecontroller){
			if (SDL_GameControllerGetAttached(gamecontroller)){
				SDL_GameControllerClose(gamecontroller);
			}
		}

		int getName(State & state, SDL_GameController * gamecontroller);
		int isAttached(State & state, SDL_GameController * gamecontroller);

		int getAxis(State & state, SDL_GameController * gamecontroller);
		int getButton(State & state, SDL_GameController * gamecontroller);

		int getBindForAxis(State & state, SDL_GameController * gamecontroller);
		int getBindForButton(State & state, SDL_GameController * gamecontroller);

		int getJoystick(State & state, SDL_GameController * gamecontroller);

		int getMapping(State & state, SDL_GameController * gamecontroller);
		int setMapping(State & state, SDL_GameController * gamecontroller);
	};
}

#endif
