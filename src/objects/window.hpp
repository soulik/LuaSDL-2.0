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
			LUTOK_METHOD("drawableSize", &Window::getDrawableSize);

			LUTOK_METHOD("maximize", &Window::maximize);
			LUTOK_METHOD("minimize", &Window::minimize);
			LUTOK_METHOD("restore", &Window::restore);
			LUTOK_METHOD("raise", &Window::raise);
			LUTOK_METHOD("fullscreen", &Window::setFullScreen);
			LUTOK_METHOD("setDisplayMode", &Window::setDisplayMode);
			LUTOK_METHOD("warpMouseInWindow", &Window::warpMouseInWindow);

			LUTOK_METHOD("getMinimumSize", &Window::getMinimumSize);
			LUTOK_METHOD("getMaximumsize", &Window::getMaximumSize);
			LUTOK_METHOD("setMinimumSize", &Window::setMinimumSize);
			LUTOK_METHOD("setMaximumsize", &Window::setMaximumSize);

			LUTOK_PROPERTY("surface", &Window::getWindowSurface, &Window::nullMethod);
			LUTOK_PROPERTY("displayMode", &Window::getWindowDisplayMode, &Window::setWindowDisplayMode);
			LUTOK_PROPERTY("title", &Window::getWindowTitle, &Window::setWindowTitle);
			LUTOK_PROPERTY("position", &Window::getWindowPosition, &Window::setWindowPosition);
			LUTOK_PROPERTY("size", &Window::getWindowSize, &Window::setWindowSize);
			LUTOK_PROPERTY("grab", &Window::getWindowGrab, &Window::setWindowGrab);
			LUTOK_PROPERTY("flags", &Window::getWindowFlags, &Window::nullMethod);
			LUTOK_PROPERTY("brightness", &Window::getWindowBrightness, &Window::setWindowBrightness);
			LUTOK_PROPERTY("bordered", &Window::nullMethod, &Window::setWindowBordered);
			LUTOK_PROPERTY("pixelFormat", &Window::getWindowPixelFormat, &Window::nullMethod);
			LUTOK_PROPERTY("displayIndex", &Window::getWindowDisplayIndex, &Window::nullMethod);
			LUTOK_PROPERTY("data", &Window::getWindowData, &Window::setWindowData);
			LUTOK_PROPERTY("icon", &Window::nullMethod, &Window::setWindowIcon);
			LUTOK_PROPERTY("id", &Window::getWindowID, &Window::nullMethod);

			LUTOK_PROPERTY("gammaRamp", &Window::nullMethod, &Window::nullMethod);

			LUTOK_PROPERTY("renderer", &Window::getRenderer, &Window::nullMethod);
		}

		//SDL_Window * constructor(State & state, bool & managed);
		void destructor(State & state, SDL_Window* window);

		int createRenderer(State & state, SDL_Window * window);

		int GLcreateContext(State & state, SDL_Window * window);
		int GLswapWindow(State & state, SDL_Window * window);
		int GLmakeCurrent(State & state, SDL_Window * window);
		int setDisplayMode(State & state, SDL_Window * window);

		int getRenderer(State & state, SDL_Window * window);

		int getDrawableSize(State & state, SDL_Window  * window);
		int inline setFullScreen(State & state, SDL_Window  * window);
		int inline show(State & state, SDL_Window  * window);
		int inline hide(State & state, SDL_Window  * window);
		int inline maximize(State & state, SDL_Window  * window);
		int inline minimize(State & state, SDL_Window  * window);
		int inline restore(State & state, SDL_Window  * window);
		int inline raise(State & state, SDL_Window  * window);
		int inline update(State & state, SDL_Window  * window);
		int updateRects(State & state, SDL_Window  * window);
		int inline warpMouseInWindow(State & state, SDL_Window  * window);
		int getWindowSurface(State & state, SDL_Window  * window);
		int inline getWindowDisplayMode(State & state, SDL_Window  * window);
		int inline setWindowDisplayMode(State & state, SDL_Window  * window);
		int inline getWindowData(State & state, SDL_Window  * window);
		int inline setWindowData(State & state, SDL_Window  * window);
		int inline getWindowTitle(State & state, SDL_Window  * window);
		int inline setWindowTitle(State & state, SDL_Window  * window);
		int inline getWindowID(State & state, SDL_Window  * window);
		int getWindowPosition(State & state, SDL_Window  * window);
		int setWindowPosition(State & state, SDL_Window  * window);
		int getWindowSize(State & state, SDL_Window  * window);
		int setWindowSize(State & state, SDL_Window  * window);
		int inline setWindowBordered(State & state, SDL_Window  * window);
		int inline getWindowGrab(State & state, SDL_Window  * window);
		int inline setWindowGrab(State & state, SDL_Window  * window);
		int inline getWindowFlags(State & state, SDL_Window  * window);
		int inline getWindowBrightness(State & state, SDL_Window  * window);
		int inline setWindowBrightness(State & state, SDL_Window  * window);
		int inline getWindowPixelFormat(State & state, SDL_Window  * window);
		int inline getWindowDisplayIndex(State & state, SDL_Window  * window);
		int inline getWindowWMinfo(State & state, SDL_Window  * window);
		int setWindowIcon(State & state, SDL_Window  * window);

		int getMinimumSize(State & state, SDL_Window  * window);
		int getMaximumSize(State & state, SDL_Window  * window);
		int setMinimumSize(State & state, SDL_Window  * window);
		int setMaximumSize(State & state, SDL_Window  * window);
	};
}

#endif