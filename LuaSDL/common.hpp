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
#include "objects/rect.hpp"
#include "objects/pixelformat.hpp"
#include "objects/displaymode.hpp"
#include "objects/surface.hpp"
#include "objects/gl_context.hpp"
#include "objects/window.hpp"
#include "objects/event.hpp"
#include "objects/cursor.hpp"
#include "objects/joystick.hpp"

namespace LuaSDL{
	
	typedef std::map< std::string, lutok::cxx_function > moduleDef;

	void init_basic(moduleDef & module);
	void init_video(moduleDef & module);
	void init_input(moduleDef & module);
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
}

#endif