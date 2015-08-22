#ifndef LUA_SDL_OBJECTS_GL_CONTEXT_H
#define LUA_SDL_OBJECTS_GL_CONTEXT_H

#include "common.hpp"

namespace LuaSDL {

	class GLContext : public Object<SDL_GLContext> {
	public:
		explicit GLContext(State * state) : Object<SDL_GLContext>(state){
		}

		void destructor(State & state, SDL_GLContext * gl_context){
			SDL_GL_DeleteContext(*gl_context);
			delete gl_context;
		}
	};
}

#endif