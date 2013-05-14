#ifndef LUA_SDL_OBJECTS_DISPLAYMODE_H
#define LUA_SDL_OBJECTS_DISPLAYMODE_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_DisplayMode : public LObject<Lua_SDL_DisplayMode, SDL_DisplayMode *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_DisplayMode, SDL_DisplayMode *, "DisplayMode") {
			
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_DisplayMode, "fullscreen", null_method);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_DisplayMode, SDL_DisplayMode *, "format", getFormat, setFormat);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_DisplayMode, SDL_DisplayMode *, "w", getW, setW);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_DisplayMode, SDL_DisplayMode *, "h", getH, setH);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_DisplayMode, SDL_DisplayMode *, "refreshRate", getRefreshRate, setRefreshRate);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_DisplayMode, SDL_DisplayMode*, "driverdata", getDriverData, setDriverData);
		}

		void destructor(SDL_DisplayMode * displayMode){
			delete displayMode;
		}

		int inline LOBJECT_METHOD(getFormat, SDL_DisplayMode * displayMode){
			state.push_integer(displayMode->format);
			return 1;
		}
		int inline LOBJECT_METHOD(setFormat, SDL_DisplayMode * displayMode){
			displayMode->format = state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getW, SDL_DisplayMode * displayMode){
			state.push_integer(displayMode->w);
			return 1;
		}
		int inline LOBJECT_METHOD(setW, SDL_DisplayMode * displayMode){
			displayMode->w = state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getH, SDL_DisplayMode * displayMode){
			state.push_integer(displayMode->h);
			return 1;
		}
		int inline LOBJECT_METHOD(setH, SDL_DisplayMode * displayMode){
			displayMode->h = state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getRefreshRate, SDL_DisplayMode * displayMode){
			state.push_integer(displayMode->refresh_rate);
			return 1;
		}
		int inline LOBJECT_METHOD(setRefreshRate, SDL_DisplayMode * displayMode){
			displayMode->refresh_rate = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getDriverData, SDL_DisplayMode * displayMode){
			state.push_lightuserdata(displayMode->driverdata);
			return 1;
		}

		int inline LOBJECT_METHOD(setDriverData, SDL_DisplayMode * displayMode){
			displayMode->driverdata = (void*)state.to_lightuserdata(1);
			return 0;
		}

	};
}

#endif