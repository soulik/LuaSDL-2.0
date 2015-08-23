#ifndef LUA_SDL_OBJECTS_JOYSTICK_H
#define LUA_SDL_OBJECTS_JOYSTICK_H

#include "common.hpp"

namespace LuaSDL {

	class Joystick : public Object<SDL_Joystick> {
	public:
		explicit Joystick(State * state) : Object<SDL_Joystick>(state) {
			LUTOK_METHOD("axis", &Joystick::getAxis);
			LUTOK_METHOD("ball", &Joystick::getBall);
			LUTOK_METHOD("button", &Joystick::getButton);
			LUTOK_METHOD("hat", &Joystick::getHat);

			LUTOK_PROPERTY("index", &Joystick::getIndex, &Joystick::nullMethod);	
			LUTOK_PROPERTY("name", &Joystick::getName, &Joystick::nullMethod);	

			LUTOK_PROPERTY("numAxes", &Joystick::getNumAxes, &Joystick::nullMethod);	
			LUTOK_PROPERTY("numBalls", &Joystick::getNumBalls, &Joystick::nullMethod);	
			LUTOK_PROPERTY("numButtons", &Joystick::getNumButtons, &Joystick::nullMethod);	
			LUTOK_PROPERTY("numHats", &Joystick::getNumHats, &Joystick::nullMethod);
			LUTOK_PROPERTY("haptic", &Joystick::getHaptic, &Joystick::nullMethod);
			LUTOK_PROPERTY("isHaptic", &Joystick::isHaptic, &Joystick::nullMethod);
		}

		SDL_Joystick * constructor(State & state, bool & managed);

		void destructor(State & state, SDL_Joystick * joystick){
			if (SDL_JoystickGetAttached(joystick)){
				SDL_JoystickClose(joystick);
			}
		}

		int getAxis(State & state, SDL_Joystick * joystick);
		int getBall(State & state, SDL_Joystick * joystick);
		int getButton(State & state, SDL_Joystick * joystick);
		int getHat(State & state, SDL_Joystick * joystick);
		int getIndex(State & state, SDL_Joystick * joystick);
		int getName(State & state, SDL_Joystick * joystick);

		int getNumAxes(State & state, SDL_Joystick * joystick);
		int getNumBalls(State & state, SDL_Joystick * joystick);
		int getNumButtons(State & state, SDL_Joystick * joystick);
		int getNumHats(State & state, SDL_Joystick * joystick);

		int getHaptic(State & state, SDL_Joystick * joystick);
		int isHaptic(State & state, SDL_Joystick * joystick);
	};
}

#endif
