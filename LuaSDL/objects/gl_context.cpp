#include "objects/window.hpp"
#include <lua.hpp>

void LuaSDL::init_gl_context(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_GL_Context);
}

