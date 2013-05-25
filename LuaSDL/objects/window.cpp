#include "objects/displaymode.hpp"
#include "objects/window.hpp"
#include "objects/gl_context.hpp"
#include <lua.hpp>

void LuaSDL::Lua_SDL_Window::destructor(lutok::state & s, SDL_Window* window){
	SDL_DestroyWindow(window);
}

int LuaSDL::Lua_SDL_Window::LOBJECT_METHOD(GLcreateContext, SDL_Window * window){
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context){
		Lua_SDL_GL_Context * c = LOBJECT_INSTANCE(Lua_SDL_GL_Context);
		c->push(context);
		return 1;
	}else{
		return 0;
	}
}

int LuaSDL::Lua_SDL_Window::LOBJECT_METHOD(GLswapWindow, SDL_Window * window){
	SDL_GL_SwapWindow(window);
	return 0;
}

int LuaSDL::Lua_SDL_Window::LOBJECT_METHOD(GLmakeCurrent, SDL_Window * window){
	Lua_SDL_GL_Context * c = LOBJECT_INSTANCE(Lua_SDL_GL_Context);
	
	state.push_boolean(
		(SDL_GL_MakeCurrent(
			window,
			c->check(1)) == 0));
	return 1;
}

int LuaSDL::Lua_SDL_Window::LOBJECT_METHOD(setDisplayMode, SDL_Window * window){
	Lua_SDL_DisplayMode * dm = LOBJECT_INSTANCE(Lua_SDL_DisplayMode);

	state.push_boolean(
		SDL_SetWindowDisplayMode(
			window,
			dm->check(1)
		) == 0);
	return 1;
}



void LuaSDL::init_window(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Window);
}
