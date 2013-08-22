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

/* libSDL 2.0 */
#include <SDL.h>
#include <SDL_main.h>

/* SDL Mixer 2.0 */
#include <SDL_mixer.h>
/* SDL Image 2.0 */
#include <SDL_image.h>
/* SDL TTF 2.0 */
#include <SDL_ttf.h>

namespace LuaSDL{
	
	typedef std::map< std::string, lutok::cxx_function > moduleDef;

	void init_basic(moduleDef & module);
	void init_video(moduleDef & module);
	void init_input(moduleDef & module);
	void init_timers(moduleDef & module);
	void init_audio(moduleDef & module);
	void init_constants(lutok::state &);
	void init_power(moduleDef & module);
	void init_platform(moduleDef & module);

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
	void init_thread(lutok::state & state, moduleDef & module);
	void init_renderer(lutok::state & state, moduleDef & module);
	void init_texture(lutok::state & state, moduleDef & module);

	//SDL_mixer
	void init_sdl_mixer(moduleDef & module);
	void init_mix_chunk(lutok::state & state, moduleDef & module);
	void init_mix_music(lutok::state & state, moduleDef & module);

	//SDL_image
	void init_sdl_image(moduleDef & module);

	//SDL_ttf
	void init_sdl_ttf(moduleDef & module);
	void init_ttf_font(lutok::state & state, moduleDef & module);

	//SDL iconv
	void init_iconv(lutok::state & state, moduleDef & module);

}

#endif