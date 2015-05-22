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

#include <lutok2/lutok2.hpp>

#include "utils.hpp"

/* libSDL 2.0 */
#include <SDL.h>
#include <SDL_main.h>

/* SDL Mixer 2.0 */
#include <SDL_mixer.h>
/* SDL Image 2.0 */
#include <SDL_image.h>
/* SDL TTF 2.0 */
#include <SDL_ttf.h>

using namespace lutok2;

#define getObject(n) *(static_cast<void**>(stack->to<void*>((n))))

namespace LuaSDL{
	void init_basic(Module & module);
	void init_video(Module & module);
	void init_input(Module & module);
	void init_timers(Module & module);
	void init_audio(Module & module);
	void init_constants(State &);
	void init_power(Module & module);
	void init_platform(Module & module);

	//objects
	void initWindow(State &, Module & module);
	void init_gl_context(State &, Module & module);
	void init_displaymode(State &, Module & module);
	void init_rect(State &, Module & module);
	void init_surface(State &, Module & module);
	void init_pixelformat(State &, Module & module);
	void init_event(State &, Module & module);
	void init_input(State &, Module & module);
	void init_cursor(State & state, Module & module);
	void init_joystick(State & state, Module & module);
	void init_gamecontroller(State & state, Module & module);
	void init_timer(State & state, Module & module);
	void init_audiodevice(State & state, Module & module);
	void init_audiospec(State & state, Module & module);
	void init_audiobuffer(State & state, Module & module);
	void init_thread(State & state, Module & module);
	void init_renderer(State & state, Module & module);
	void init_texture(State & state, Module & module);

	//SDL_mixer
	void init_sdl_mixer(Module & module);
	void init_mix_chunk(State & state, Module & module);
	void init_mix_music(State & state, Module & module);

	//SDL_image
	void init_sdl_image(Module & module);

	//SDL_ttf
	void init_sdl_ttf(Module & module);
	void init_ttf_font(State & state, Module & module);

	//SDL iconv
	void init_iconv(State & state, Module & module);

}

#endif