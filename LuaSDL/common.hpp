#ifndef LUA_SDL_COMMON_H
#define LUA_SDL_COMMON_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <string>

#include <lutok/exceptions.hpp>
#include <lutok/operations.hpp>
#include <lutok/state.ipp>
#include <lutok/lobject.hpp>
#include <lutok/luna.hpp>

#include <lua.hpp>

#include <SDL.h>

namespace LuaSDL{
	
	typedef std::map< std::string, lutok::cxx_function > moduleDef;

	void init_basic(moduleDef & module);
	void init_video(moduleDef & module);
	void init_input(moduleDef & module);
	void init_timers(moduleDef & module);
	void init_audio(moduleDef & module);
	void init_constants(lutok::state &);

	//objects
	void init_window(lutok::state &, moduleDef & module);
	void init_gl_context(lutok::state &, moduleDef & module);
	void init_displaymode(lutok::state &, moduleDef & module);
	void init_rect(lutok::state &, moduleDef & module);
	void init_surface(lutok::state &, moduleDef & module);
	void init_pixelformat(lutok::state &, moduleDef & module);
	void init_event(lutok::state &, moduleDef & module);
	void init_input(lutok::state &, moduleDef & module);
	void init_cursor(lutok::state & state, moduleDef & module);
	void init_joystick(lutok::state & state, moduleDef & module);
	void init_gamecontroller(lutok::state & state, moduleDef & module);
	void init_timer(lutok::state & state, moduleDef & module);
	void init_audiodevice(lutok::state & state, moduleDef & module);
	void init_audiospec(lutok::state & state, moduleDef & module);
	void init_audiobuffer(lutok::state & state, moduleDef & module);
}

#endif