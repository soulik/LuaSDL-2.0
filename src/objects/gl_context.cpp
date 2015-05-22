#include "objects/gl_context.hpp"
#include <lua.hpp>

namespace LuaSDL {
	void init_gl_context(State & state, Module & module){
		GLcontext * interfaceGLcontext = state.getInterface<GLcontext>("LuaSDL_GLcontext");
	}
};

