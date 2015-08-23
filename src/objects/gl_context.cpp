#include "objects/gl_context.hpp"
#include "objects/window.hpp"
#include <lua.hpp>

namespace LuaSDL {
	void initGLContext(State * state, Module & module){
		INIT_OBJECT(GLContext);
	}
};

