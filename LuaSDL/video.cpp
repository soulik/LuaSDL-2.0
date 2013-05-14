#include "common.hpp"

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

	static int lua_SDL_CreateWindow(lutok::state& state){
		SDL_Window * window = SDL_CreateWindow(
			state.to_string(1).c_str(),
			state.to_integer(2),
			state.to_integer(3),
			state.to_integer(4),
			state.to_integer(5),
			(Uint32)state.to_integer(6));
		if (window){
			Lua_SDL_Window * w = LOBJECT_INSTANCE(Lua_SDL_Window);
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

		state.push_integer(retval);
		Lua_SDL_Window * w = LOBJECT_INSTANCE(Lua_SDL_Window);
		w->push(window);
		state.push_lightuserdata(reinterpret_cast<void*>(renderer));
		return 3;
	}
	static int lua_SDL_CreateWindowFrom(lutok::state& state){
		SDL_Window * window = SDL_CreateWindowFrom(state.to_userdata<void>(1));
		if (window){
			Lua_SDL_Window * w = LOBJECT_INSTANCE(Lua_SDL_Window);
			w->push(window);
			return 1;
		}
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
		Lua_SDL_DisplayMode * dm = LOBJECT_INSTANCE(Lua_SDL_DisplayMode);
		Lua_SDL_Rect * r = LOBJECT_INSTANCE(Lua_SDL_Rect);

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
					dm->push(mode);
					state.set_table();
				}else{
					delete mode;
				}
			}
			state.set_table();

			SDL_Rect * rect = new SDL_Rect;
			SDL_GetDisplayBounds(display, rect);
			
			state.push_literal("bounds");
			r->push(rect);
			/*
			state.new_table();
				state.push_literal("x");
				state.push_integer(rect.x);
				state.set_table();
				state.push_literal("y");
				state.push_integer(rect.y);
				state.set_table();
				state.push_literal("w");
				state.push_integer(rect.w);
				state.set_table();
				state.push_literal("h");
				state.push_integer(rect.h);
				state.set_table();
				*/
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
		Lua_SDL_DisplayMode * dm = LOBJECT_INSTANCE(Lua_SDL_DisplayMode);
		SDL_DisplayMode * mode = new SDL_DisplayMode;

		if (SDL_GetCurrentDisplayMode(state.to_integer(1), mode) == 0){
			dm->push(mode);
			return 1;
		}else{
			delete mode;
			return 0;
		}
	}

	static int lua_SDL_GetDesktopDisplayMode(lutok::state& state){
		Lua_SDL_DisplayMode * dm = LOBJECT_INSTANCE(Lua_SDL_DisplayMode);
		SDL_DisplayMode * mode = new SDL_DisplayMode;

		if (SDL_GetDesktopDisplayMode(state.to_integer(1), mode) == 0){
			dm->push(mode);
			return 1;
		}else{
			delete mode;
			return 0;
		}
	}

	static int lua_SDL_GetClosestDisplayMode(lutok::state& state){
		Lua_SDL_DisplayMode * dm = LOBJECT_INSTANCE(Lua_SDL_DisplayMode);
		SDL_DisplayMode * mode = new SDL_DisplayMode;

		if (SDL_GetClosestDisplayMode(
			state.to_integer(1),
			dm->check(2),
			mode) == 0){
				dm->push(mode);
				return 1;
		}else{
			delete mode;
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


	void init_video(moduleDef & module){
		module["createWindow"] = lua_SDL_CreateWindow;
		module["createWindowAndRenderer"] = lua_SDL_CreateWindowAndRenderer;
		module["createWindowFrom"] = lua_SDL_CreateWindowFrom;
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

	}

}