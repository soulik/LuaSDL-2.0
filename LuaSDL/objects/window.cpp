#include "objects/displaymode.hpp"
#include "objects/window.hpp"
#include "objects/gl_context.hpp"
#include "objects/surface.hpp"
#include "objects/renderer.hpp"

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

static int lua_SDL_CreateWindow(lutok::state& state){
	SDL_Window * window = SDL_CreateWindow(
		state.to_string(1).c_str(),
		state.to_integer(2),
		state.to_integer(3),
		state.to_integer(4),
		state.to_integer(5),
		(Uint32)state.to_integer(6));
	if (window){
		LuaSDL::Lua_SDL_Window * w = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Window);
		w->push(window);
		return 1;
	}
	return 0;
}
static int lua_SDL_CreateWindowAndRenderer(lutok::state& state){

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;

	int retval = SDL_CreateWindowAndRenderer(
		state.to_integer(1),
		state.to_integer(2),
		(Uint32)state.to_integer(3),
		&window,
		&renderer
		);

	LuaSDL::Lua_SDL_Window * w = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Window);
	LuaSDL::Lua_SDL_Renderer * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Renderer);
	if (retval==0){
		if (window){
			w->push(window);
		}else{
			state.push_nil();
		}
		if (renderer){
			r->push(renderer);
		}else{
			state.push_nil();
		}
		return 2;
	}else{
		state.push_boolean(false);
		return 1;
	}
}
static int lua_SDL_CreateWindowFrom(lutok::state& state){
	SDL_Window * window = SDL_CreateWindowFrom(state.to_userdata<void>(1));
	if (window){
		LuaSDL::Lua_SDL_Window * w = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Window);
		w->push(window);
		return 1;
	}
	return 0;
}		
static int lua_SDL_GetWindowFromID(lutok::state& state){
	SDL_Window * window = SDL_GetWindowFromID(state.to_integer(1));
	if (window){
		LuaSDL::Lua_SDL_Window * w = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Window);
		w->push(window);
		return 1;
	}
	return 0;
}		
int LuaSDL::Lua_SDL_Window::LOBJECT_METHOD(getWindowSurface, SDL_Window * window){
	LuaSDL::Lua_SDL_Surface * s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	SDL_Surface * surface = SDL_GetWindowSurface(window);
	if (surface){
		s->push(surface);
		return 1;
	}else{
		return 0;
	}
}

int LuaSDL::Lua_SDL_Window::LOBJECT_METHOD(createRenderer, SDL_Window * window){
	LuaSDL::Lua_SDL_Renderer * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Renderer);
	int index = -1;
	Uint32 flags = 0;

	if (state.is_number(1)){
		index = state.to_integer(1);
	}
	if (state.is_number(2)){
		flags = state.to_integer(2);
	}

	SDL_Renderer * renderer = SDL_CreateRenderer(window, index, flags);
	if (renderer){
		r->push(renderer);
		return 1;
	}else{
		return 0;
	}
}

int LuaSDL::Lua_SDL_Window::LOBJECT_METHOD(getRenderer, SDL_Window * window){
	LuaSDL::Lua_SDL_Renderer * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Renderer);

	SDL_Renderer * renderer = SDL_GetRenderer(window);
	if (renderer){
		r->push(renderer, false);
	}else{
		state.push_boolean(false);
	}
	return 1;
}

void LuaSDL::init_window(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Window);
	module["createWindow"] = lua_SDL_CreateWindow;
	module["createWindowAndRenderer"] = lua_SDL_CreateWindowAndRenderer;
	module["createWindowFrom"] = lua_SDL_CreateWindowFrom;
	module["getWindowFromID"] = lua_SDL_GetWindowFromID;
}
