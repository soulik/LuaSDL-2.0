#ifndef LUA_SDL_OBJECTS_JOYSTICK_H
#define LUA_SDL_OBJECTS_JOYSTICK_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_Joystick : public LObject<Lua_SDL_Joystick, SDL_Joystick *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_Joystick, SDL_Joystick *, "Joystick") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Joystick, "axis", getAxis);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Joystick, "ball", getBall);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Joystick, "button", getButton);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Joystick, "hat", getHat);

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Joystick, SDL_Joystick *, "index", getIndex, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Joystick, SDL_Joystick *, "name", getName, null_method);	

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Joystick, SDL_Joystick *, "numAxes", getNumAxes, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Joystick, SDL_Joystick *, "numBalls", getNumBalls, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Joystick, SDL_Joystick *, "numButtons", getNumButtons, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Joystick, SDL_Joystick *, "numHats", getNumHats, null_method);	
		}

		void destructor(SDL_Joystick * joystick){
			SDL_JoystickClose(joystick);
		}

		int LOBJECT_METHOD(getAxis, SDL_Joystick * joystick){
			state.push_integer(
				SDL_JoystickGetAxis(
					joystick,
					state.to_integer(1)));
			return 1;
		}
		int LOBJECT_METHOD(getBall, SDL_Joystick * joystick){
			int dx,dy;

			int retval = SDL_JoystickGetBall(
				joystick,
				state.to_integer(1),
				&dx, &dy
				);
			if (retval == 0){
				state.push_integer(dx);
				state.push_integer(dy);
				return 2;
			}else{
				return 0;
			}
		}
		int LOBJECT_METHOD(getButton, SDL_Joystick * joystick){
			state.push_boolean(
				SDL_JoystickGetButton(
					joystick,
					state.to_integer(1)) == 1);
			return 1;
		}
		int LOBJECT_METHOD(getHat, SDL_Joystick * joystick){
			state.push_integer(
				SDL_JoystickGetHat(
					joystick,
					state.to_integer(1)));
			return 1;
		}
		int LOBJECT_METHOD(getIndex, SDL_Joystick * joystick){
			//state.push_integer(SDL_JoystickIndex(joystick));
			return 0;
		}
		int LOBJECT_METHOD(getName, SDL_Joystick * joystick){
			state.push_string(SDL_JoystickName(joystick));
			return 1;
		}

		int LOBJECT_METHOD(getNumAxes, SDL_Joystick * joystick){
			state.push_integer(SDL_JoystickNumAxes(joystick));
			return 1;
		}
		int LOBJECT_METHOD(getNumBalls, SDL_Joystick * joystick){
			state.push_integer(SDL_JoystickNumBalls(joystick));
			return 1;
		}
		int LOBJECT_METHOD(getNumButtons, SDL_Joystick * joystick){
			state.push_integer(SDL_JoystickNumButtons(joystick));
			return 1;
		}
		int LOBJECT_METHOD(getNumHats, SDL_Joystick * joystick){
			state.push_integer(SDL_JoystickNumHats(joystick));
			return 1;
		}
	};
}

#endif
