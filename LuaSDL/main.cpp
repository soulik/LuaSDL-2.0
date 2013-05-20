#include "common.hpp"



extern "C" LUA_API int luaopen_LuaSDL(void * current_state){

	lutok::state state(current_state);
    LuaSDL::moduleDef module;

    LuaSDL::init_basic(module);
	LuaSDL::init_video(module);
	LuaSDL::init_input(module);
	LuaSDL::init_timers(module);
	
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

    lutok::registerLib(state, "SDL", module);
	LuaSDL::init_constants(state);
	return 1;
 }
