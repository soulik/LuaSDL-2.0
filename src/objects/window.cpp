#include "objects/displaymode.hpp"
#include "objects/window.hpp"
#include "objects/gl_context.hpp"
#include "objects/surface.hpp"
#include "objects/renderer.hpp"

namespace LuaSDL {
	void initWindow(State * state, Module & module){
		state->registerInterface<Window>("LuaSDL_Window");
		module["createWindow"] = lua_SDL_CreateWindow;
		module["createWindowAndRenderer"] = lua_SDL_CreateWindowAndRenderer;
		module["createWindowFrom"] = lua_SDL_CreateWindowFrom;
		module["getWindowFromID"] = lua_SDL_GetWindowFromID;
	}

	void Window::destructor(State & s, SDL_Window* window){
		SDL_DestroyWindow(window);
	}

	int Window::GLcreateContext(State & state, SDL_Window  * window){
		SDL_GLContext context = SDL_GL_CreateContext(window);
		if (context){
			GLContext * interfaceGLContext = state.getInterface<GLContext>("LuaSDL_GL_Context");
			interfaceGLContext->push(context, false);
			return 1;
		}
		else{
			return 0;
		}
	}

	int Window::GLswapWindow(State & state, SDL_Window  * window){
		SDL_GL_SwapWindow(window);
		return 0;
	}

	int Window::GLmakeCurrent(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		GLContext * interfaceGLContext = state.getInterface<GLContext>("LuaSDL_GL_Context");

		stack->push<bool>(
			(SDL_GL_MakeCurrent(
			window,
			c->get(1)) == 0));
		return 1;
	}

	int Window::setDisplayMode(State & state, SDL_Window  * window){
		DisplayMode * interfaceDisplayMode = state.getInterface<DisplayMode>("LuaSDL_DisplayMode");
		Stack * stack = state.stack;
		stack->push<bool>(
			SDL_SetWindowDisplayMode(
			window,
			interfaceDisplayMode->get(1)
			) == 0);
		return 1;
	}

	static int lua_SDL_CreateWindow(State & state){
		Stack * stack = state.stack;
		SDL_Window * window = SDL_CreateWindow(
			stack->to<const std::string>(1).c_str(),
			stack->to<int>(2),
			stack->to<int>(3),
			stack->to<int>(4),
			stack->to<int>(5),
			(Uint32)stack->to<int>(6));
		if (window){
			Window * interfaceWindow = state.getInterface<Window>("LuaSDL_Window");
			interfaceWindow->push(window);
			return 1;
		}
		return 0;
	}
	static int lua_SDL_CreateWindowAndRenderer(State & state){
		Stack * stack = state.stack;
		SDL_Window * window = NULL;
		SDL_Renderer * renderer = NULL;

		int retval = SDL_CreateWindowAndRenderer(
			stack->to<int>(1),
			stack->to<int>(2),
			(Uint32)stack->to<int>(3),
			&window,
			&renderer
			);
		Window * interfaceWindow = state.getInterface<Window>("LuaSDL_Window");
		Renderer * interfaceRenderer = state.getInterface<Renderer>("LuaSDL_Renderer");
		if (retval == 0){
			if (window){
				interfaceWindow->push(window);
			}
			else{
				stack->pushNil();
			}
			if (renderer){
				interfaceRenderer->push(renderer);
			}
			else{
				stack->pushNil();
			}
			return 2;
		}
		else{
			stack->push<bool>(false);
			return 1;
		}
	}
	static int lua_SDL_CreateWindowFrom(State & state){
		Stack * stack = state.stack;
		SDL_Window * window = SDL_CreateWindowFrom(state.to_userdata<void>(1));
		if (window){
			Window * interfaceWindow = state.getInterface<Window>("LuaSDL_Window");
			interfaceWindow->push(window);
			return 1;
		}
		return 0;
	}
	static int lua_SDL_GetWindowFromID(State & state){
		Stack * stack = state.stack;
		SDL_Window * window = SDL_GetWindowFromID(stack->to<int>(1));
		if (window){
			Window * interfaceWindow = state.getInterface<Window>("LuaSDL_Window");
			interfaceWindow->push(window);
			return 1;
		}
		return 0;
	}
	int Window::getWindowSurface(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		SDL_Surface * surface = SDL_GetWindowSurface(window);
		if (surface){
			interfaceSurface->push(surface);
			return 1;
		}
		else{
			return 0;
		}
	}

	int Window::createRenderer(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		Renderer * interfaceRenderer = state.getInterface<Renderer>("LuaSDL_Renderer");
		int index = -1;
		Uint32 flags = 0;

		if (stack->is<LUA_TNUMBER>(1)){
			index = stack->to<int>(1);
		}
		if (stack->is<LUA_TNUMBER>(2)){
			flags = stack->to<int>(2);
		}

		SDL_Renderer * renderer = SDL_CreateRenderer(window, index, flags);
		if (renderer){
			interfaceRenderer->push(renderer);
			return 1;
		}
		else{
			return 0;
		}
	}

	int Window::getRenderer(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		Renderer * interfaceRenderer = state.getInterface<Renderer>("LuaSDL_Renderer");

		SDL_Renderer * renderer = SDL_GetRenderer(window);
		if (renderer){
			interfaceRenderer->push(renderer, false);
		}
		else{
			stack->push<bool>(false);
		}
		return 1;
	}
}