#ifndef LUA_SDL_OBJECTS_WINDOW_H
#define LUA_SDL_OBJECTS_WINDOW_H

#include "common.hpp"

namespace LuaSDL {

	class Window : public Object<SDL_Window> {
	public:
		explicit Window(State * state) : Object<SDL_Window>(state){
			LUTOK_METHOD("createRenderer", &Window::createRenderer);
			
			LUTOK_METHOD("GL_createContext", &Window::GLcreateContext);
			LUTOK_METHOD("GL_swap", &Window::GLswapWindow);
			LUTOK_METHOD("GL_makeCurrent", &Window::GLmakeCurrent);
			LUTOK_METHOD("show", &Window::show);
			LUTOK_METHOD("hide", &Window::hide);
			LUTOK_METHOD("update", &Window::update);
			LUTOK_METHOD("updateRects", &Window::updateRects);

			LUTOK_METHOD("maximize", &Window::maximize);
			LUTOK_METHOD("minimize", &Window::minimize);
			LUTOK_METHOD("restore", &Window::restore);
			LUTOK_METHOD("raise", &Window::raise);
			LUTOK_METHOD("fullscreen", &Window::setFullScreen);
			LUTOK_METHOD("setDisplayMode", &Window::setDisplayMode);
			LUTOK_METHOD("warpMouseInWindow", &Window::warpMouseInWindow);

			LUTOK_PROPERTY("surface", &Window::getWindowSurface, &Window::nullMethod);
			LUTOK_PROPERTY("display", &Window::getWindowDisplay, &Window::setWindowDisplay);
			LUTOK_PROPERTY("title", &Window::getWindowTitle, &Window::setWindowTitle);
			LUTOK_PROPERTY("position", &Window::getWindowPosition, &Window::setWindowPosition);
			LUTOK_PROPERTY("size", &Window::getWindowSize, &Window::setWindowSize);
			LUTOK_PROPERTY("grab", &Window::getWindowGrab, &Window::setWindowGrab);
			LUTOK_PROPERTY("flags", &Window::getWindowFlags, &Window::nullMethod);
			LUTOK_PROPERTY("brightness", &Window::getWindowBrightness, &Window::setWindowBrightness);
			LUTOK_PROPERTY("pixelFormat", &Window::getWindowPixelFormat, &Window::nullMethod);
			LUTOK_PROPERTY("displayIndex", &Window::getWindowDisplayIndex, &Window::nullMethod);
			LUTOK_PROPERTY("data", &Window::getWindowData, &Window::setWindowData);
			
			LUTOK_PROPERTY("gammaRamp", &Window::nullMethod, &Window::nullMethod);

			LUTOK_PROPERTY("renderer", &Window::getRenderer, &Window::nullMethod);
		}

		SDL_Window * constructor(State & state, bool & managed);
		void destructor(State & state, SDL_Window* window);

		int createRenderer(State & state, SDL_Window * window);

		int GLcreateContext(State & state, SDL_Window * window);
		int GLswapWindow(State & state, SDL_Window * window);
		int GLmakeCurrent(State & state, SDL_Window * window);
		int setDisplayMode(State & state, SDL_Window * window);

		int getRenderer(State & state, SDL_Window * window);

		int inline setFullScreen(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			stack->push<bool>(SDL_SetWindowFullscreen(window, stack->to<bool>(1)) == 0);
			return 1;
		}
		int inline show(State & state, SDL_Window  * window){
			SDL_ShowWindow(window);
			return 0;
		}
		int inline hide(State & state, SDL_Window  * window){
			SDL_HideWindow(window);
			return 0;
		}
		int inline maximize(State & state, SDL_Window  * window){
			SDL_MaximizeWindow(window);
			return 0;
		}
		int inline minimize(State & state, SDL_Window  * window){
			SDL_MinimizeWindow(window);
			return 0;
		}
		int inline restore(State & state, SDL_Window  * window){
			SDL_RestoreWindow(window);
			return 0;
		}
		int inline raise(State & state, SDL_Window  * window){
			SDL_RaiseWindow(window);
			return 0;
		}
		int inline update(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			stack->push<bool>(SDL_UpdateWindowSurface(window) == 0);
			return 1;
		}
		int updateRects(State & state, SDL_Window  * window){
			/*
			const SDL_Rect * rects= nullptr;
			int num_rects=0;
			stack->push<bool>(SDL_UpdateWindowSurfaceRects(window, rects, num_rects) == 0);
			return 1;
			*/
			return 0;
		}
		int inline warpMouseInWindow(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			SDL_WarpMouseInWindow(window, stack->to<int>(1), stack->to<int>(2));
			return 0;
		}
		int getWindowSurface(State & state, SDL_Window  * window);
		int inline getWindowDisplay(State & state, SDL_Window  * window){
			//stack->push_lightuserdata(SDL_GetWindowDisplay(window, stack->stack->to<const std::string &>(1).c_str()));
			//SDL_GetWindowDisplay();
			return 0;
		}
		int inline setWindowDisplay(State & state, SDL_Window  * window){
			//stack->push_lightuserdata(SDL_GetWindowDisplay(window, stack->stack->to<const std::string &>(1).c_str()));
			//SDL_GetWindowDisplay();
			return 0;
		}
		int inline getWindowData(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			stack->push<void*>(SDL_GetWindowData(window, stack->to<const std::string &>(1).c_str()));
			return 1;
		}
		int inline setWindowData(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			SDL_SetWindowData(window, stack->to<const std::string &>(1).c_str(), (void *)(stack->to<void*>(1)));
			return 0;
		}
		int inline getWindowTitle(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			stack->push<const std::string &>(SDL_GetWindowTitle(window));
			return 1;
		}
		int inline setWindowTitle(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			if (stack->is<LUA_TSTRING>(1)){
				SDL_SetWindowTitle(window, stack->to<const std::string &>(1).c_str());
			}
			return 0;
		}
		int getWindowPosition(State & state, SDL_Window  * window){
			int x,y;
			SDL_GetWindowPosition(window, &x, &y);
			Stack * stack = state.stack;
			stack->newTable();
				stack->push<int>(x);
				stack->setField("x");
				stack->push<int>(y);
				stack->setField("y");
			return 1;
		}
		int setWindowPosition(State & state, SDL_Window  * window){
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
		int getWindowSize(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			int w, h;
			SDL_GetWindowSize(window, &w, &h);
			stack->newTable();
				stack->push<int>(w);
				stack->setField("w");
				stack->push<int>(h);
				stack->setField("h");
			return 1;
		}
		int setWindowSize(State & state, SDL_Window  * window){
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
		int inline getWindowGrab(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			stack->push<bool>((SDL_GetWindowGrab(window) == SDL_TRUE));
			return 1;
		}
		int inline setWindowGrab(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			SDL_SetWindowGrab(window, (stack->to<bool>(1)) ? SDL_TRUE : SDL_FALSE);
			return 0;
		}
		int inline getWindowFlags(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			stack->push<int>(SDL_GetWindowFlags(window));
			return 1;
		}
		int inline getWindowBrightness(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			stack->push<LUA_NUMBER>(SDL_GetWindowBrightness(window));
			return 1;
		}
		int inline setWindowBrightness(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			SDL_SetWindowBrightness(window, static_cast<float>(stack->to<LUA_NUMBER>(1)));
			return 0;
		}
		int inline getWindowPixelFormat(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			stack->push<LUA_NUMBER>(SDL_GetWindowPixelFormat(window));
			return 1;
		}
		int inline getWindowDisplayIndex(State & state, SDL_Window  * window){
			Stack * stack = state.stack;
			stack->push<int>(SDL_GetWindowDisplayIndex(window));
			return 1;
		}
		int inline getWindowWMinfo(State & state, SDL_Window  * window){
			/*
			assert(window);
			SDL_SysWMinfo info;
			SDL_GetWindowWMInfo(window, &info);
			*/
			return 0;
		}

	};
}

#endif