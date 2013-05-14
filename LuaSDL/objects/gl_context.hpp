#ifndef LUA_SDL_OBJECTS_GL_CONTEXT_H
#define LUA_SDL_OBJECTS_GL_CONTEXT_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_GL_Context : public LObject<Lua_SDL_GL_Context, SDL_GLContext> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_GL_Context, SDL_GLContext, "GL_Context") {
		}

		void destructor(SDL_GLContext gl_context){
			assert(gl_context);
			SDL_GL_DeleteContext(gl_context);
		}
	};
}

#endif