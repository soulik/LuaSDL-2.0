#include "common.hpp"

extern "C" LUA_API int luaopen_LuaSDL(void * current_state){

	lutok::state state(current_state);
    LuaSDL::moduleDef module;

    LuaSDL::init_basic(module);
	LuaSDL::init_video(module);
	LuaSDL::init_input(module);
	LuaSDL::init_timers(module);
	LuaSDL::init_audio(module);
	LuaSDL::init_power(module);
	LuaSDL::init_platform(module);
	
	//objects
	LuaSDL::init_gl_context(state, module);
	LuaSDL::init_rect(state, module);
	LuaSDL::init_displaymode(state, module);
	LuaSDL::init_surface(state, module);
	LuaSDL::init_window(state, module);
	LuaSDL::init_event(state, module);
	LuaSDL::init_cursor(state, module);
	LuaSDL::init_joystick(state, module);
	LuaSDL::init_gamecontroller(state, module);
	LuaSDL::init_timer(state, module);
	LuaSDL::init_audiodevice(state, module);
	LuaSDL::init_audiospec(state, module);
	LuaSDL::init_audiobuffer(state, module);
	LuaSDL::init_thread(state, module);

	//SDL Mixer
	LuaSDL::init_sdl_mixer(module);
	LuaSDL::init_mix_chunk(state, module);
	LuaSDL::init_mix_music(state, module);

	//SDL Image
	LuaSDL::init_sdl_image(module);

	//SDL TTF
	LuaSDL::init_sdl_ttf(module);
	LuaSDL::init_ttf_font(state, module);

	//SDL iconv
	LuaSDL::init_iconv(state, module);

	lutok::registerLib(state, "SDL", module);
	LuaSDL::init_constants(state);
	SDL_SetMainReady();
	return 1;
 }
