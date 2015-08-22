#include "objects/displaymode.hpp"
#include "objects/window.hpp"
#include "objects/gl_context.hpp"
#include "objects/surface.hpp"
#include "objects/renderer.hpp"

namespace LuaSDL {
	void Window::destructor(State & s, SDL_Window* window){
		SDL_DestroyWindow(window);
	}

	int Window::GLcreateContext(State & state, SDL_Window  * window){
		GLContext * interfaceGLContext = state.getInterface<GLContext>("LuaSDL_GL_Context");
		SDL_GLContext _context = SDL_GL_CreateContext(window);
		if (_context){
			SDL_GLContext * context = new SDL_GLContext;
			*context = _context;
			interfaceGLContext->push(context, true);
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

		SDL_GLContext * c = interfaceGLContext->get(1);
		if (c){
			stack->push<bool>(
				(SDL_GL_MakeCurrent(
				window,
				*c) == 0));
			return 1;
		}
		return 0;
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
		if (stack->is<LUA_TSTRING>(1)){
			const std::string title = stack->to<const std::string>(1);
			SDL_Window * window = SDL_CreateWindow(
				title.c_str(),
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
		Window * interfaceWindow = state.getInterface<Window>("LuaSDL_Window");
		if (stack->is<LUA_TLIGHTUSERDATA>(1)){
			void * data = stack->to<void*>(1);
			if (data){
				SDL_Window * window = SDL_CreateWindowFrom(data);
				if (window){
					interfaceWindow->push(window);
					return 1;
				}
			}
		}
		return 0;
	}
	static int lua_SDL_GetWindowFromID(State & state){
		Stack * stack = state.stack;
		Window * interfaceWindow = state.getInterface<Window>("LuaSDL_Window");
		SDL_Window * window = SDL_GetWindowFromID(stack->to<int>(1));
		if (window){
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

	int inline Window::setFullScreen(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_SetWindowFullscreen(window, stack->to<bool>(1)) == 0);
		return 1;
	}
	int inline Window::show(State & state, SDL_Window  * window){
		SDL_ShowWindow(window);
		return 0;
	}
	int inline Window::hide(State & state, SDL_Window  * window){
		SDL_HideWindow(window);
		return 0;
	}
	int inline Window::maximize(State & state, SDL_Window  * window){
		SDL_MaximizeWindow(window);
		return 0;
	}
	int inline Window::minimize(State & state, SDL_Window  * window){
		SDL_MinimizeWindow(window);
		return 0;
	}
	int inline Window::restore(State & state, SDL_Window  * window){
		SDL_RestoreWindow(window);
		return 0;
	}
	int inline Window::raise(State & state, SDL_Window  * window){
		SDL_RaiseWindow(window);
		return 0;
	}
	int inline Window::update(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_UpdateWindowSurface(window) == 0);
		return 1;
	}
	int Window::updateRects(State & state, SDL_Window  * window){
		/*
		const SDL_Rect * rects= nullptr;
		int num_rects=0;
		stack->push<bool>(SDL_UpdateWindowSurfaceRects(window, rects, num_rects) == 0);
		return 1;
		*/
		return 0;
	}
	int inline Window::warpMouseInWindow(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		SDL_WarpMouseInWindow(window, stack->to<int>(1), stack->to<int>(2));
		return 0;
	}

	int inline Window::getWindowDisplay(State & state, SDL_Window  * window){
		//stack->push_lightuserdata(SDL_GetWindowDisplay(window, stack->stack->to<const std::string &>(1).c_str()));
		//SDL_GetWindowDisplay();
		return 0;
	}
	int inline Window::setWindowDisplay(State & state, SDL_Window  * window){
		//stack->push_lightuserdata(SDL_GetWindowDisplay(window, stack->stack->to<const std::string &>(1).c_str()));
		//SDL_GetWindowDisplay();
		return 0;
	}
	int inline Window::getWindowData(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			const std::string name = stack->to<const std::string>(1);
			stack->push<void*>(SDL_GetWindowData(window, name.c_str()));
			return 1;
		}
		return 0;
	}
	int inline Window::setWindowData(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TLIGHTUSERDATA>(2)){
			const std::string name = stack->to<const std::string>(1);
			SDL_SetWindowData(window, name.c_str(), stack->to<void*>(2));
		}
		return 0;
	}
	int inline Window::getWindowTitle(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		stack->push<const std::string &>(SDL_GetWindowTitle(window));
		return 1;
	}
	int inline Window::setWindowTitle(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			const std::string name = stack->to<const std::string>(1);
			SDL_SetWindowTitle(window, name.c_str());
		}
		return 0;
	}
	int Window::getWindowPosition(State & state, SDL_Window  * window){
		int x, y;
		SDL_GetWindowPosition(window, &x, &y);
		Stack * stack = state.stack;
		stack->newTable();
		stack->setField<int>("x", x, -2);
		stack->setField<int>("y", y, -2);
		return 1;
	}
	int Window::setWindowPosition(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		if (stack->is<LUA_TTABLE>(1)){
			stack->getField("x", 1);
			stack->getField("y", 1);

			if (stack->is<LUA_TNUMBER>(-2) && stack->is<LUA_TNUMBER>(-1)){
				SDL_SetWindowPosition(window, stack->to<int>(-2), stack->to<int>(-1));
			}
			stack->pop(2);
		}
		return 0;
	}
	int Window::getWindowSize(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		stack->newTable();
		stack->setField<int>("w", w, -2);
		stack->setField<int>("h", h, -2);
		return 1;
	}
	int Window::setWindowSize(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		if (stack->is<LUA_TTABLE>(1)){
			stack->getField("w", 1);
			stack->getField("h", 1);

			if (stack->is<LUA_TNUMBER>(-2) && stack->is<LUA_TNUMBER>(-1)){
				SDL_SetWindowSize(window, stack->to<int>(-2), stack->to<int>(-1));
			}
			stack->pop(2);
		}
		return 0;
	}
	int inline Window::getWindowGrab(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		stack->push<bool>((SDL_GetWindowGrab(window) == SDL_TRUE));
		return 1;
	}
	int inline Window::setWindowGrab(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		SDL_SetWindowGrab(window, (stack->to<bool>(1)) ? SDL_TRUE : SDL_FALSE);
		return 0;
	}
	int inline Window::getWindowFlags(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		stack->push<int>(SDL_GetWindowFlags(window));
		return 1;
	}
	int inline Window::getWindowBrightness(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(SDL_GetWindowBrightness(window));
		return 1;
	}
	int inline Window::setWindowBrightness(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		SDL_SetWindowBrightness(window, static_cast<float>(stack->to<LUA_NUMBER>(1)));
		return 0;
	}
	int inline Window::getWindowPixelFormat(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(SDL_GetWindowPixelFormat(window));
		return 1;
	}
	int inline Window::getWindowDisplayIndex(State & state, SDL_Window  * window){
		Stack * stack = state.stack;
		stack->push<int>(SDL_GetWindowDisplayIndex(window));
		return 1;
	}
	int inline Window::getWindowWMinfo(State & state, SDL_Window  * window){
		/*
		assert(window);
		SDL_SysWMinfo info;
		SDL_GetWindowWMInfo(window, &info);
		*/
		return 0;
	}
	void initWindow(State * state, Module & module){
		INIT_OBJECT(Window);
		module["createWindow"] = lua_SDL_CreateWindow;
		module["createWindowAndRenderer"] = lua_SDL_CreateWindowAndRenderer;
		module["createWindowFrom"] = lua_SDL_CreateWindowFrom;
		module["getWindowFromID"] = lua_SDL_GetWindowFromID;
	}
}