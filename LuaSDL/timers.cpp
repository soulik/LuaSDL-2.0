#include "common.hpp"

namespace LuaSDL {

	static int lua_SDL_Delay(lutok::state& state){
		SDL_Delay(state.to_integer(1));
		return 0;
	}
	static int lua_SDL_GetTicks(lutok::state& state){
		state.push_integer(SDL_GetTicks());
		return 1;
	}
	static int lua_SDL_GetPerformanceCounter(lutok::state& state){
		Uint64 counter = SDL_GetPerformanceCounter();
		state.push_integer(counter & 0xFFFFFFFF);
		state.push_integer(counter >> 32);
		return 2;
	}
	static int lua_SDL_GetPerformanceFrequency(lutok::state& state){
		Uint64 freq = SDL_GetPerformanceFrequency();
		state.push_integer(freq & 0xFFFFFFFF);
		state.push_integer(freq >> 32);
		return 2;
	}

	void init_timers(moduleDef & module){
		module["delay"] = lua_SDL_Delay;
		module["getTicks"] = lua_SDL_GetTicks;
		module["getPerformanceCounter"] = lua_SDL_GetPerformanceCounter;
		module["getPerformanceFrequency"] = lua_SDL_GetPerformanceFrequency;
	}
}