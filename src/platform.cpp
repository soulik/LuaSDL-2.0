#include "common.hpp"

namespace LuaSDL {
	static int lua_SDL_GetPlatform(State & state){
		state.stack->push<const std::string>(SDL_GetPlatform());
		return 1;
	}

	void init_platform(Module & module){
		module["platform"] = lua_SDL_GetPlatform;
	}
}
