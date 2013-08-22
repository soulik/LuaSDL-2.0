#include "common.hpp"

namespace LuaSDL {
	static int lua_SDL_GetPlatform(lutok::state& state){
		state.push_string(SDL_GetPlatform());
		return 1;
	}

	void init_platform(moduleDef & module){
		module["platform"] = lua_SDL_GetPlatform;
	}
}
