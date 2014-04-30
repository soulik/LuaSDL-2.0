#include "objects/gamecontroller.hpp"
#include <lua.hpp>

static int lua_SDL_GameControllerOpen(lutok::state& state){
	LuaSDL::Lua_SDL_GameController & c = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_GameController);
	SDL_GameController * gamecontroller = SDL_GameControllerOpen(state.to_integer(1));
	if (gamecontroller){
		c.push(gamecontroller);
		return 1;
	}else{
		return 0;
	}
}

static int lua_SDL_GameControllerNameForIndex(lutok::state& state){
	const char * name =SDL_GameControllerNameForIndex(state.to_integer(1));
	if (name){
		state.push_string(name);
		return 1;
	}else{
		return 0;
	}
}

static int lua_SDL_IsGameController(lutok::state& state){
	state.push_boolean(SDL_IsGameController(state.to_integer(1)) == SDL_TRUE);
	return 1;
}

void LuaSDL::init_gamecontroller(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_GameController);
	module["GameController"] = lua_SDL_GameControllerOpen;
	module["gameControllerNameForIndex"] = lua_SDL_GameControllerNameForIndex;
	module["isGameController"] = lua_SDL_IsGameController;
}
