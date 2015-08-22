#include "objects/joystick.hpp"
#include <lua.hpp>

namespace LuaSDL {
	int Joystick::getAxis(State & state, SDL_Joystick * joystick) {
		Stack * stack = state.stack;
		stack->push<int>(
			SDL_JoystickGetAxis(
			joystick,
			stack->to<int>(1)));
		return 1;
	}
	int Joystick::getBall(State & state, SDL_Joystick * joystick) {
		Stack * stack = state.stack;
		int dx, dy;

		int retval = SDL_JoystickGetBall(
			joystick,
			stack->to<int>(1),
			&dx, &dy
			);
		if (retval == 0){
			stack->push<int>(dx);
			stack->push<int>(dy);
			return 2;
		}
		else{
			return 0;
		}
	}
	int Joystick::getButton(State & state, SDL_Joystick * joystick) {
		Stack * stack = state.stack;
		stack->push<bool>(
			SDL_JoystickGetButton(
			joystick,
			stack->to<int>(1)) == 1);
		return 1;
	}
	int Joystick::getHat(State & state, SDL_Joystick * joystick) {
		Stack * stack = state.stack;
		stack->push<int>(
			SDL_JoystickGetHat(
			joystick,
			stack->to<int>(1)));
		return 1;
	}
	int Joystick::getIndex(State & state, SDL_Joystick * joystick) {
		Stack * stack = state.stack;
		//stack->push<int>(SDL_JoystickIndex(joystick));
		return 0;
	}
	int Joystick::getName(State & state, SDL_Joystick * joystick) {
		Stack * stack = state.stack;
		const char * name = SDL_JoystickName(joystick);
		if (name){
			stack->push<const std::string &>(name);
			return 1;
		}
		else{
			return 0;
		}
	}

	int Joystick::getNumAxes(State & state, SDL_Joystick * joystick) {
		Stack * stack = state.stack;
		stack->push<int>(SDL_JoystickNumAxes(joystick));
		return 1;
	}
	int Joystick::getNumBalls(State & state, SDL_Joystick * joystick) {
		Stack * stack = state.stack;
		stack->push<int>(SDL_JoystickNumBalls(joystick));
		return 1;
	}
	int Joystick::getNumButtons(State & state, SDL_Joystick * joystick) {
		Stack * stack = state.stack;
		stack->push<int>(SDL_JoystickNumButtons(joystick));
		return 1;
	}
	int Joystick::getNumHats(State & state, SDL_Joystick * joystick) {
		Stack * stack = state.stack;
		stack->push<int>(SDL_JoystickNumHats(joystick));
		return 1;
	}

	SDL_Joystick * Joystick::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		Joystick * interfaceJoystick = state.getInterface<Joystick>("LuaSDL_Joystick");
		SDL_Joystick * joystick = SDL_JoystickOpen(stack->to<int>(1));
		return joystick;
	}

	static int lua_SDL_NumJoysticks(State & state){
		Stack * stack = state.stack;
		stack->push<int>(SDL_NumJoysticks());
		return 1;
	}

	static int lua_SDL_JoystickOpened(State & state){
		Stack * stack = state.stack;
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
		Stack * stack = state.stack;
		SDL_JoystickUpdate();
		return 0;
	}

	static int lua_SDL_JoystickNameForIndex(State & state){
		Stack * stack = state.stack;
		stack->push<const std::string &>(SDL_JoystickNameForIndex(stack->to<int>(1)));
		return 1;
	}

	void initJoystick(State * state, Module & module){
		INIT_OBJECT(Joystick);

		//module["Joystick"] = lua_SDL_JoystickOpen;
		module["numJoysticks"] = lua_SDL_NumJoysticks;
		module["joystickUpdate"] = lua_SDL_JoystickUpdate;
		module["joystickNameForIndex"] = lua_SDL_JoystickNameForIndex;

	}
};


