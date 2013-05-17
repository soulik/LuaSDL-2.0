#include "common.hpp"



extern "C" LUA_API int luaopen_LuaSDL(void * current_state){

    // Create a new Lua session and load the print() function.
	lutok::state state(current_state);
    // Construct a 'module' that contains an entry point to our native factorial
    // function.  A module is just a Lua table that contains a mapping of names
    // to functions.  Instead of creating a module by using our create_module()
    // helper function, we could have used push_cxx_function on the state to
    // define the function ourselves.
    LuaSDL::moduleDef module;

    LuaSDL::init_basic(module);
	LuaSDL::init_video(module);
	
	//objects
	LuaSDL::init_gl_context(state, module);
	LuaSDL::init_rect(state, module);
	LuaSDL::init_displaymode(state, module);
	LuaSDL::init_surface(state, module);
	LuaSDL::init_window(state, module);
	LuaSDL::init_event(state, module);

    lutok::registerLib(state, "SDL", module);
	LuaSDL::init_constants(state);
	return 1;
 }
