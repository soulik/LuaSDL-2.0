#include "objects/joystick.hpp"
#include <lua.hpp>

static int lua_SDL_JoystickOpen(State & state){
	LuaSDL::Lua_SDL_Joystick & j = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Joystick);
	SDL_Joystick * joystick = SDL_JoystickOpen(stack->to<int>(1));
	if (joystick){
		j.push(joystick);
		return 1;
	}else{
		return 0;
	}
}

static int lua_SDL_NumJoysticks(State & state){
	stack->push<int>(SDL_NumJoysticks());
	return 1;
}

static int lua_SDL_JoystickOpened(State & state){
	/*
	int retval = SDL_JoystickOpened(stack->to<int>(1));
	if (retval>=0){
		stack->push<bool>(retval == 1);
	}else{
		return 0;
	}
	*/
	return 0;
}

static int lua_SDL_JoystickUpdate(State & state){
	SDL_JoystickUpdate();
	return 0;
}

static int lua_SDL_JoystickNameForIndex(State & state){
	stack->push<const std::string>(SDL_JoystickNameForIndex(stack->to<int>(1)));
	return 1;
}

void LuaSDL::init_joystick(State & state, Module & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Joystick);

	module["Joystick"] = lua_SDL_JoystickOpen;
	module["numJoysticks"] = lua_SDL_NumJoysticks;
	module["joystickUpdate"] = lua_SDL_JoystickUpdate;
	module["joystickNameForIndex"] = lua_SDL_JoystickNameForIndex;

}
