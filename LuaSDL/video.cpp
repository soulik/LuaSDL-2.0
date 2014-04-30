#include "common.hpp"
#include "objects/window.hpp"
#include "objects/displaymode.hpp"
#include "objects/rect.hpp"

namespace LuaSDL {

	static int lua_SDL_VideoInit(lutok::state& state){
		if(state.is_string(1)){
			state.push_boolean(SDL_VideoInit(state.to_string(1).c_str()) == 0);
		}else{
			state.push_boolean(SDL_VideoInit(NULL)==0);
		}
		return 1;
	}
	static int lua_SDL_VideoQuit(lutok::state& state){
		SDL_VideoQuit();
		return 0;
	}
	static int lua_SDL_GetVideoDrivers(lutok::state& state){
		state.new_table();
		for (int i=0; i<SDL_GetNumVideoDrivers(); i++){
			state.push_integer(i+1);
			state.push_string(SDL_GetVideoDriver(i));
			state.set_table();
		}
		return 1;
	}
	static int lua_SDL_GetDisplayModes(lutok::state& state){
		Lua_SDL_DisplayMode & dm = LOBJECT_INSTANCE(Lua_SDL_DisplayMode);
		Lua_SDL_Rect & r = LOBJECT_INSTANCE(Lua_SDL_Rect);

		state.new_table();// displays
		for (int display=0; display < SDL_GetNumVideoDisplays(); display++){
			state.push_integer(display+1);
			state.new_table(); //display
			int modes=1;
			state.push_literal("modes");
			state.new_table(); //modes
			for (int i=0; i<SDL_GetNumDisplayModes(display); i++){
				SDL_DisplayMode * mode = new SDL_DisplayMode;
				if (SDL_GetDisplayMode(display, i, mode) == 0){	
					state.push_integer(modes++);
					dm.push(mode);
					state.set_table();
				}else{
					delete mode;
				}
			}
			state.set_table();

			SDL_Rect * rect = new SDL_Rect;
			SDL_GetDisplayBounds(display, rect);
			
			state.push_literal("bounds");
			r.push(rect);
			state.set_table();

			state.set_table();
		}
		return 1;
	}

	static int lua_SDL_EnableScreenSaver(lutok::state& state){
		SDL_EnableScreenSaver();
		return 0;
	}
	static int lua_SDL_DisableScreenSaver(lutok::state& state){
		SDL_DisableScreenSaver();
		return 0;
	}
	static int lua_SDL_IsScreenSaverEnabled(lutok::state& state){
		state.push_boolean((SDL_IsScreenSaverEnabled() == SDL_FALSE));
		return 1;
	}

	static int lua_SDL_GetCurrentDisplayMode(lutok::state& state){
		Lua_SDL_DisplayMode & dm = LOBJECT_INSTANCE(Lua_SDL_DisplayMode);
		SDL_DisplayMode * mode = new SDL_DisplayMode;

		if (SDL_GetCurrentDisplayMode(state.to_integer(1), mode) == 0){
			dm.push(mode);
			return 1;
		}else{
			delete mode;
			return 0;
		}
	}
	static int lua_SDL_GetDesktopDisplayMode(lutok::state& state){
		Lua_SDL_DisplayMode & dm = LOBJECT_INSTANCE(Lua_SDL_DisplayMode);
		SDL_DisplayMode * mode = new SDL_DisplayMode;

		if (SDL_GetDesktopDisplayMode(state.to_integer(1), mode) == 0){
			dm.push(mode);
			return 1;
		}else{
			delete mode;
			return 0;
		}
	}
	static int lua_SDL_GetClosestDisplayMode(lutok::state& state){
		Lua_SDL_DisplayMode & dm = LOBJECT_INSTANCE(Lua_SDL_DisplayMode);
		SDL_DisplayMode * mode = new SDL_DisplayMode;

		if (SDL_GetClosestDisplayMode(
			state.to_integer(1),
			dm.check(2),
			mode) == 0){
				dm.push(mode);
				return 1;
		}else{
			delete mode;
			return 0;
		}
	}
	static int lua_SDL_GetDisplayBounds(lutok::state& state){
		Lua_SDL_Rect & r = LOBJECT_INSTANCE(Lua_SDL_Rect);
		SDL_Rect * rect = new SDL_Rect;
		if (SDL_GetDisplayBounds(state.to_integer(1), rect) == 0){
			r.push(rect);
			return 1;
		}else{
			return 0;
		}
	}
	static int lua_SDL_GetCurrentVideoDriver(lutok::state& state){
		const char * driver = SDL_GetCurrentVideoDriver();
		if (driver){
			state.push_string(driver);
			return 1;
		}else{
			return 0;
		}
	}

	static int lua_SDL_GetClipboardText(lutok::state& state){
		state.push_string(SDL_GetClipboardText());
		return 1;
	}
	static int lua_SDL_HasClipboardText(lutok::state& state){
		state.push_boolean(SDL_HasClipboardText() == SDL_TRUE);
		return 1;
	}
	static int lua_SDL_SetClipboardText(lutok::state& state){
		state.push_boolean(SDL_SetClipboardText(state.to_string().c_str()) == 0);
		return 1;
	}
	static int lua_SDL_GL_GetSwapInterval(lutok::state& state){
		int retval = SDL_GL_GetSwapInterval();
		if (retval>=0){
			state.push_boolean(retval == 1);
			return 1;
		}else{
			return 0;
		}
	}
	static int lua_SDL_GL_SetSwapInterval(lutok::state& state){
		state.push_boolean(SDL_GL_SetSwapInterval((state.to_boolean(1)) ? 1 : 0) == 0);
		return 1;
	}

	static int lua_SDL_GL_SetAttribute(lutok::state& state){
		state.push_boolean(SDL_GL_SetAttribute((SDL_GLattr)state.to_integer(1),  state.to_integer(2)) == 0);
		return 1;
	}
	static int lua_SDL_GL_GetAttribute(lutok::state& state){
		int value = 0;
		int result = SDL_GL_GetAttribute((SDL_GLattr)state.to_integer(1), &value);
		if (result==0){
			state.push_integer(value);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}

	void init_video(moduleDef & module){
		module["videoInit"] = lua_SDL_VideoInit;
		module["videoQuit"] = lua_SDL_VideoQuit;
		module["getVideoDrivers"] = lua_SDL_GetVideoDrivers;
		module["getDisplayModes"] = lua_SDL_GetDisplayModes;
		module["enableScreenSaver"] = lua_SDL_EnableScreenSaver;
		module["disableScreenSaver"] = lua_SDL_DisableScreenSaver;
		module["isScreenSaverEnabled"] = lua_SDL_IsScreenSaverEnabled;

		module["getCurrentDisplayMode"] = lua_SDL_GetCurrentDisplayMode;
		module["getDesktopDisplayMode"] = lua_SDL_GetDesktopDisplayMode;
		module["getCurrentVideoDriver"] = lua_SDL_GetCurrentVideoDriver;
		module["getClosestDisplayMode"] = lua_SDL_GetClosestDisplayMode;
		module["getDisplayBounds"] = lua_SDL_GetDisplayBounds;

		module["hasClipboardText"] = lua_SDL_HasClipboardText;
		module["getClipboardText"] = lua_SDL_GetClipboardText;
		module["setClipboardText"] = lua_SDL_SetClipboardText;

		module["GLgetSwapInterval"] = lua_SDL_GL_GetSwapInterval;
		module["GLsetSwapInterval"] = lua_SDL_GL_SetSwapInterval;

		module["GLgetAttribute"] = lua_SDL_GL_GetAttribute;
		module["GLsetAttribute"] = lua_SDL_GL_SetAttribute;
	}

}