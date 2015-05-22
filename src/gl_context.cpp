#include "objects/gl_context.hpp"

namespace LuaSDL {
	void init_gl_context(State * state, Module & module){
		state->registerInterface<GLContext>("LuaSDL_GLContext");
	}
}

