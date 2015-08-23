#ifndef LUA_SDL_OBJECTS_DISPLAYMODE_H
#define LUA_SDL_OBJECTS_DISPLAYMODE_H

#include "common.hpp"

namespace LuaSDL {

	class DisplayMode : public Object<SDL_DisplayMode> {
	public:
		explicit DisplayMode(State * state) : Object<SDL_DisplayMode>(state) {
			LUTOK_METHOD("closestDisplayMode", &DisplayMode::getClosestDisplayMode);

			LUTOK_PROPERTY("format", &DisplayMode::getFormat, &DisplayMode::setFormat);
			LUTOK_PROPERTY("w", &DisplayMode::getW, &DisplayMode::setW);
			LUTOK_PROPERTY("h", &DisplayMode::getH, &DisplayMode::setH);
			LUTOK_PROPERTY("refreshRate", &DisplayMode::getRefreshRate, &DisplayMode::setRefreshRate);	
			LUTOK_PROPERTY("driverdata", &DisplayMode::getDriverData, &DisplayMode::setDriverData);
		}

		void destructor(State & state, SDL_DisplayMode * displayMode){
			delete displayMode;
		}

		int getClosestDisplayMode(State & state, SDL_DisplayMode * displayMode);

		int inline getFormat(State & state, SDL_DisplayMode * displayMode);
		int inline setFormat(State & state, SDL_DisplayMode * displayMode);
		int inline getW(State & state, SDL_DisplayMode * displayMode);
		int inline setW(State & state, SDL_DisplayMode * displayMode);
		int inline getH(State & state, SDL_DisplayMode * displayMode);
		int inline setH(State & state, SDL_DisplayMode * displayMode);
		int inline getRefreshRate(State & state, SDL_DisplayMode * displayMode);
		int inline setRefreshRate(State & state, SDL_DisplayMode * displayMode);
		int inline getDriverData(State & state, SDL_DisplayMode * displayMode);
		int inline setDriverData(State & state, SDL_DisplayMode * displayMode);

	};
}

#endif