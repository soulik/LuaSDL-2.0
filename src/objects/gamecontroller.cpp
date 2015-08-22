#include "objects/gamecontroller.hpp"
#include <lua.hpp>

namespace LuaSDL {
	int GameController::getName(State & state, SDL_GameController * gamecontroller) {
		Stack * stack = state.stack;
		const char * name = SDL_GameControllerName(gamecontroller);
		if (name){
			stack->push<const std::string &>(name);
			return 1;
		}
		else{
			return 0;
		}
	}
	int GameController::isAttached(State & state, SDL_GameController * gamecontroller) {
		Stack * stack = state.stack;
		stack->push<bool>(SDL_GameControllerGetAttached(gamecontroller) == SDL_TRUE);
		return 1;
	}

	SDL_GameController * GameController::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		GameController * interfaceGameController = state.getInterface<GameController>("LuaSDL_GameController");
		SDL_GameController * gamecontroller = SDL_GameControllerOpen(stack->to<int>(1));
		return gamecontroller;
	}

	static int lua_SDL_GameControllerNameForIndex(State & state){
		Stack * stack = state.stack;
		const char * name = SDL_GameControllerNameForIndex(stack->to<int>(1));
		if (name){
			stack->push<const std::string &>(name);
			return 1;
		}
		else{
			return 0;
		}
	}

	static int lua_SDL_IsGameController(State & state){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_IsGameController(stack->to<int>(1)) == SDL_TRUE);
		return 1;
	}

	void initGameController(State * state, Module & module){
		INIT_OBJECT(GameController);
		//module["GameController"] = lua_SDL_GameControllerOpen;
		module["gameControllerNameForIndex"] = lua_SDL_GameControllerNameForIndex;
		module["isGameController"] = lua_SDL_IsGameController;
	}

};