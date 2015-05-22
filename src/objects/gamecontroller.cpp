#include "objects/gamecontroller.hpp"
#include <lua.hpp>

static int lua_SDL_GameControllerOpen(State & state){
	LuaSDL::Lua_SDL_GameController & c = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_GameController);
	SDL_GameController * gamecontroller = SDL_GameControllerOpen(stack->to<int>(1));
	if (gamecontroller){
		c.push(gamecontroller);
		return 1;
	}else{
		return 0;
	}
}

static int lua_SDL_GameControllerNameForIndex(State & state){
	const char * name =SDL_GameControllerNameForIndex(stack->to<int>(1));
	if (name){
		stack->push<const std::string>(name);
		return 1;
	}else{
		return 0;
	}
}

static int lua_SDL_IsGameController(State & state){
	stack->push<bool>(SDL_IsGameController(stack->to<int>(1)) == SDL_TRUE);
	return 1;
}

void LuaSDL::init_gamecontroller(State & state, Module & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_GameController);
	module["GameController"] = lua_SDL_GameControllerOpen;
	module["gameControllerNameForIndex"] = lua_SDL_GameControllerNameForIndex;
	module["isGameController"] = lua_SDL_IsGameController;
}
