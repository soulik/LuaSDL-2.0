#include "common.hpp"
#include "objects/window.hpp"
#include "objects/displaymode.hpp"
#include "objects/rect.hpp"

namespace LuaSDL {

	static int lua_SDL_VideoInit(State & state){
		Stack * stack = state.stack;
		if(stack->is<LUA_TSTRING>(1)){
			stack->push<bool>(SDL_VideoInit(stack->to<const std::string>(1).c_str()) == 0);
		}else{
			stack->push<bool>(SDL_VideoInit(NULL)==0);
		}
		return 1;
	}
	static int lua_SDL_VideoQuit(State & state){
		SDL_VideoQuit();
		return 0;
	}
	static int lua_SDL_GetVideoDrivers(State & state){
		Stack * stack = state.stack;
		stack->newTable();
		for (int i=0; i<SDL_GetNumVideoDrivers(); i++){
			stack->push<int>(i+1);
			stack->push<const std::string>(SDL_GetVideoDriver(i));
			stack->setTable();
		}
		return 1;
	}
	static int lua_SDL_GetDisplayModes(State & state){
		Stack * stack = state.stack;
		Lua_SDL_DisplayMode & dm = LOBJECT_INSTANCE(Lua_SDL_DisplayMode);
		Lua_SDL_Rect & r = LOBJECT_INSTANCE(Lua_SDL_Rect);

		stack->newTable();// displays
		for (int display=0; display < SDL_GetNumVideoDisplays(); display++){
			stack->push<int>(display+1);
			stack->newTable(); //display
			int modes=1;
			state.push_literal("modes");
			stack->newTable(); //modes
			for (int i=0; i<SDL_GetNumDisplayModes(display); i++){
				SDL_DisplayMode * mode = new SDL_DisplayMode;
				if (SDL_GetDisplayMode(display, i, mode) == 0){	
					stack->push<int>(modes++);
					dm.push(mode);
					stack->setTable();
				}else{
					delete mode;
				}
			}
			stack->setTable();

			SDL_Rect * rect = new SDL_Rect;
			SDL_GetDisplayBounds(display, rect);
			
			state.push_literal("bounds");
			r.push(rect);
			stack->setTable();

			stack->setTable();
		}
		return 1;
	}

	static int lua_SDL_EnableScreenSaver(State & state){
		SDL_EnableScreenSaver();
		return 0;
	}
	static int lua_SDL_DisableScreenSaver(State & state){
		SDL_DisableScreenSaver();
		return 0;
	}
	static int lua_SDL_IsScreenSaverEnabled(State & state){
		Stack * stack = state.stack;
		stack->push<bool>((SDL_IsScreenSaverEnabled() == SDL_FALSE));
		return 1;
	}

	static int lua_SDL_GetCurrentDisplayMode(State & state){
		Stack * stack = state.stack;
		Lua_SDL_DisplayMode & dm = LOBJECT_INSTANCE(Lua_SDL_DisplayMode);
		SDL_DisplayMode * mode = new SDL_DisplayMode;

		if (SDL_GetCurrentDisplayMode(stack->to<int>(1), mode) == 0){
			dm.push(mode);
			return 1;
		}else{
			delete mode;
			return 0;
		}
	}
	static int lua_SDL_GetDesktopDisplayMode(State & state){
		Stack * stack = state.stack;
		Lua_SDL_DisplayMode & dm = LOBJECT_INSTANCE(Lua_SDL_DisplayMode);
		SDL_DisplayMode * mode = new SDL_DisplayMode;

		if (SDL_GetDesktopDisplayMode(stack->to<int>(1), mode) == 0){
			dm.push(mode);
			return 1;
		}else{
			delete mode;
			return 0;
		}
	}
	static int lua_SDL_GetClosestDisplayMode(State & state){
		Stack * stack = state.stack;
		Lua_SDL_DisplayMode & dm = LOBJECT_INSTANCE(Lua_SDL_DisplayMode);
		SDL_DisplayMode * mode = new SDL_DisplayMode;

		if (SDL_GetClosestDisplayMode(
			stack->to<int>(1),
			dm.check(2),
			mode) == 0){
				dm.push(mode);
				return 1;
		}else{
			delete mode;
			return 0;
		}
	}
	static int lua_SDL_GetDisplayBounds(State & state){
		Stack * stack = state.stack;
		Lua_SDL_Rect & r = LOBJECT_INSTANCE(Lua_SDL_Rect);
		SDL_Rect * rect = new SDL_Rect;
		if (SDL_GetDisplayBounds(stack->to<int>(1), rect) == 0){
			r.push(rect);
			return 1;
		}else{
			return 0;
		}
	}
	static int lua_SDL_GetCurrentVideoDriver(State & state){
		Stack * stack = state.stack;
		const char * driver = SDL_GetCurrentVideoDriver();
		if (driver){
			stack->push<const std::string>(driver);
			return 1;
		}else{
			return 0;
		}
	}

	static int lua_SDL_GetClipboardText(State & state){
		Stack * stack = state.stack;
		stack->push<const std::string>(SDL_GetClipboardText());
		return 1;
	}
	static int lua_SDL_HasClipboardText(State & state){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_HasClipboardText() == SDL_TRUE);
		return 1;
	}
	static int lua_SDL_SetClipboardText(State & state){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_SetClipboardText(stack->to<const std::string>().c_str()) == 0);
		return 1;
	}
	static int lua_SDL_GL_GetSwapInterval(State & state){
		Stack * stack = state.stack;
		int retval = SDL_GL_GetSwapInterval();
		if (retval>=0){
			stack->push<bool>(retval == 1);
			return 1;
		}else{
			return 0;
		}
	}
	static int lua_SDL_GL_SetSwapInterval(State & state){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_GL_SetSwapInterval((stack->to<bool>(1)) ? 1 : 0) == 0);
		return 1;
	}

	static int lua_SDL_GL_SetAttribute(State & state){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_GL_SetAttribute((SDL_GLattr)stack->to<int>(1),  stack->to<int>(2)) == 0);
		return 1;
	}
	static int lua_SDL_GL_GetAttribute(State & state){
		Stack * stack = state.stack;
		int value = 0;
		int result = SDL_GL_GetAttribute((SDL_GLattr)stack->to<int>(1), &value);
		if (result==0){
			stack->push<int>(value);
		}else{
			stack->push<bool>(false);
		}
		return 1;
	}

	void init_video(Module & module){
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