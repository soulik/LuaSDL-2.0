#ifndef LUA_SDL_OBJECTS_WINDOW_H
#define LUA_SDL_OBJECTS_WINDOW_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_Window : public LObject<Lua_SDL_Window, SDL_Window*> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_Window, SDL_Window*, "Window") {
			
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "GL_createContext", GLcreateContext);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "GL_swap", GLswapWindow);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "GL_makeCurrent", GLmakeCurrent);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "show", show);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "hide", hide);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "update", update);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "updateRects", updateRects);

			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "maximize", maximize);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "minimize", minimize);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "restore", restore);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "raise", raise);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "fullscreen", setFullScreen);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "setDisplayMode", setDisplayMode);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Window, "warpMouseInWindow", warpMouseInWindow);

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Window, SDL_Window*, "surface", getWindowSurface, null_method);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Window, SDL_Window*, "display", getWindowDisplay, setWindowDisplay);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Window, SDL_Window*, "title", getWindowTitle, setWindowTitle);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Window, SDL_Window*, "position", getWindowPosition, setWindowPosition);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Window, SDL_Window*, "size", getWindowSize, setWindowSize);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Window, SDL_Window*, "grab", getWindowGrab, setWindowGrab);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Window, SDL_Window*, "flags", getWindowFlags, null_method);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Window, SDL_Window*, "brightness", getWindowBrightness, setWindowBrightness);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Window, SDL_Window*, "pixelFormat", getWindowPixelFormat, null_method);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Window, SDL_Window*, "displayIndex", getWindowDisplayIndex, null_method);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Window, SDL_Window*, "data", getWindowData, setWindowData);
			
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Window, SDL_Window*, "gammaRamp", null_method, null_method);
			
		}

		void destructor(lutok::state & s, SDL_Window* window);

		int LOBJECT_METHOD(GLcreateContext, SDL_Window*);
		int LOBJECT_METHOD(GLswapWindow, SDL_Window*);
		int LOBJECT_METHOD(GLmakeCurrent, SDL_Window*);
		int LOBJECT_METHOD(setDisplayMode, SDL_Window*);

		int inline LOBJECT_METHOD(setFullScreen,SDL_Window * window){
			state.push_boolean(SDL_SetWindowFullscreen(window, state.to_boolean(1)) == 0);
			return 1;
		}
		int inline LOBJECT_METHOD(show, SDL_Window * window){
			SDL_ShowWindow(window);
			return 0;
		}
		int inline LOBJECT_METHOD(hide, SDL_Window * window){
			SDL_HideWindow(window);
			return 0;
		}
		int inline LOBJECT_METHOD(maximize, SDL_Window * window){
			SDL_MaximizeWindow(window);
			return 0;
		}
		int inline LOBJECT_METHOD(minimize, SDL_Window * window){
			SDL_MinimizeWindow(window);
			return 0;
		}
		int inline LOBJECT_METHOD(restore, SDL_Window * window){
			SDL_RestoreWindow(window);
			return 0;
		}
		int inline LOBJECT_METHOD(raise, SDL_Window * window){
			SDL_RaiseWindow(window);
			return 0;
		}
		int inline LOBJECT_METHOD(update, SDL_Window * window){
			state.push_boolean(SDL_UpdateWindowSurface(window) == 0);
			return 1;
		}
		int LOBJECT_METHOD(updateRects, SDL_Window * window){
			/*
			const SDL_Rect * rects= nullptr;
			int num_rects=0;
			state.push_boolean(SDL_UpdateWindowSurfaceRects(window, rects, num_rects) == 0);
			return 1;
			*/
			return 0;
		}
		int inline LOBJECT_METHOD(warpMouseInWindow,SDL_Window * window){
			SDL_WarpMouseInWindow(window, state.to_integer(1), state.to_integer(2));
			return 0;
		}
		int LOBJECT_METHOD(getWindowSurface, SDL_Window * window);
		int inline LOBJECT_METHOD(getWindowDisplay, SDL_Window * window){
			//state.push_lightuserdata(SDL_GetWindowDisplay(window, state.to_string().c_str()));
			//SDL_GetWindowDisplay();
			return 0;
		}
		int inline LOBJECT_METHOD(setWindowDisplay, SDL_Window * window){
			//state.push_lightuserdata(SDL_GetWindowDisplay(window, state.to_string().c_str()));
			//SDL_GetWindowDisplay();
			return 0;
		}
		int inline LOBJECT_METHOD(getWindowData, SDL_Window * window){
			state.push_lightuserdata(SDL_GetWindowData(window, state.to_string().c_str()));
			return 1;
		}
		int inline LOBJECT_METHOD(setWindowData, SDL_Window * window){
			SDL_SetWindowData(window, state.to_string().c_str(), (void *)(state.to_lightuserdata(1)));
			return 0;
		}
		int inline LOBJECT_METHOD(getWindowTitle, SDL_Window * window){
			state.push_string(SDL_GetWindowTitle(window));
			return 1;
		}
		int inline LOBJECT_METHOD(setWindowTitle, SDL_Window * window){
			if (state.is_string(1)){
				SDL_SetWindowTitle(window, state.to_string(1).c_str());
			}
			return 0;
		}
		int LOBJECT_METHOD(getWindowPosition, SDL_Window * window){
			int x,y;
			SDL_GetWindowPosition(window, &x, &y);
			state.new_table();
				state.push_integer(x);
				state.set_field(-2, "x");
				state.push_integer(y);
				state.set_field(-2, "y");
			return 1;
		}
		int LOBJECT_METHOD(setWindowPosition, SDL_Window * window){
			if (state.is_table(1)){
				state.get_field(1, "x");
				state.get_field(1, "y");

				if (state.is_number(-2) && state.is_number(-1)){
					SDL_SetWindowPosition(window, state.to_integer(-2), state.to_integer(-1));
				}
				state.pop(2);
			}
			return 0;
		}
		int LOBJECT_METHOD(getWindowSize, SDL_Window * window){
			int w,h;
			SDL_GetWindowSize(window, &w, &h);
			state.new_table();
				state.push_integer(w);
				state.set_field(-2, "w");
				state.push_integer(h);
				state.set_field(-2, "h");
			return 1;
		}
		int LOBJECT_METHOD(setWindowSize, SDL_Window * window){
			if (state.is_table(1)){
				state.get_field(1, "w");
				state.get_field(1, "h");

				if (state.is_number(-2) && state.is_number(-1)){
					SDL_SetWindowSize(window, state.to_integer(-2), state.to_integer(-1));
				}
				state.pop(2);
			}
			return 0;
		}
		int inline LOBJECT_METHOD(getWindowGrab, SDL_Window * window){
			state.push_boolean((SDL_GetWindowGrab(window) == SDL_TRUE));
			return 1;
		}
		int inline LOBJECT_METHOD(setWindowGrab, SDL_Window * window){
			SDL_SetWindowGrab(window, (state.to_boolean(1)) ? SDL_TRUE : SDL_FALSE);
			return 0;
		}
		int inline LOBJECT_METHOD(getWindowFlags, SDL_Window * window){
			state.push_integer(SDL_GetWindowFlags(window));
			return 1;
		}
		int inline LOBJECT_METHOD(getWindowBrightness, SDL_Window * window){
			state.push_number( SDL_GetWindowBrightness(window) );
			return 1;
		}
		int inline LOBJECT_METHOD(setWindowBrightness, SDL_Window * window){
			SDL_SetWindowBrightness(window, static_cast<float>(state.to_number(1)));
			return 0;
		}
		int inline LOBJECT_METHOD(getWindowPixelFormat, SDL_Window * window){
			state.push_number( SDL_GetWindowPixelFormat(window) );
			return 1;
		}
		int inline LOBJECT_METHOD(getWindowDisplayIndex, SDL_Window * window){
			state.push_integer(SDL_GetWindowDisplayIndex(window));
			return 1;
		}
		int inline LOBJECT_METHOD(getWindowWMinfo, SDL_Window * window){
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