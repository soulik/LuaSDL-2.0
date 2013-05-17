#include "objects/joystick.hpp"
#include <lua.hpp>

static int lua_SDL_JoystickOpen(lutok::state& state){
	LuaSDL::Lua_SDL_Joystick * j = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Joystick);
	SDL_Joystick * joystick = SDL_JoystickOpen(state.to_integer(1));
	if (joystick){
		j->push(joystick);
		return 1;
	}else{
		return 0;
	}
}

static int lua_SDL_NumJoysticks(lutok::state& state){
	state.push_integer(SDL_NumJoysticks());
	return 1;
}

static int lua_SDL_JoystickOpened(lutok::state& state){
	/*
	int retval = SDL_JoystickOpened(state.to_integer(1));
	if (retval>=0){
		state.push_boolean(retval == 1);
	}else{
		return 0;
	}
	*/
	return 0;
}

static int lua_SDL_JoystickUpdate(lutok::state& state){
	SDL_JoystickUpdate();
	return 0;
}

static int lua_SDL_JoystickNameForIndex(lutok::state& state){
	state.push_string(SDL_JoystickNameForIndex(state.to_integer(1)));
	return 1;
}

void LuaSDL::init_joystick(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Joystick);

	module["Joystick"] = lua_SDL_JoystickOpen;
	module["numJoysticks"] = lua_SDL_NumJoysticks;
	module["joystickUpdate"] = lua_SDL_JoystickUpdate;
	module["joystickNameForIndex"] = lua_SDL_JoystickNameForIndex;

}
