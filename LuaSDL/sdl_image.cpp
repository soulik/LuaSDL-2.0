#include "common.hpp"
#include "objects/surface.hpp"

namespace LuaSDL {

	static int lua_IMG_Init(lutok::state& state){
		int result = 0;
		if (state.is_number(1)){
			result = IMG_Init(state.to_integer(1));
		}else{
			result = IMG_Init(0);
		}
		state.push_integer(result);
		return 1;
	}
	static int lua_IMG_Quit(lutok::state& state){
		IMG_Quit();
		return 0;
	}
	static int lua_IMG_Load(lutok::state& state){
		LuaSDL::Lua_SDL_Surface * s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
		if (state.is_string(1)){
			SDL_Surface * surface = IMG_Load(state.to_string(1).c_str());
			if (surface){
				s->push(surface);
			}else{
				state.push_boolean(false);
			}
			return 1;
		}
		return 0;
	}
	static int lua_IMG_GetError(lutok::state& state){
		state.push_string(IMG_GetError());
		return 1;
	}

	void init_sdl_image(moduleDef & module){
		module["imageInit"] = lua_IMG_Init;
		module["imageQuit"] = lua_IMG_Quit;

		//Loading
		module["imageLoad"] = lua_IMG_Load;

		//Errors
		module["imageGetError"] = lua_IMG_GetError;
	}
}