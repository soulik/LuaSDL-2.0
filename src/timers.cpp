#include "common.hpp"

namespace LuaSDL {

	static int lua_SDL_Delay(State & state){
		Stack * stack = state.stack;
		SDL_Delay(stack->to<int>(1));
		return 0;
	}
	static int lua_SDL_GetTicks(State & state){
		Stack * stack = state.stack;
		stack->push<int>(SDL_GetTicks());
		return 1;
	}
	static int lua_SDL_GetPerformanceCounter(State & state){
		Stack * stack = state.stack;
		Uint64 counter = SDL_GetPerformanceCounter();
		stack->push<int>(counter & 0xFFFFFFFF);
		stack->push<int>(counter >> 32);
		return 2;
	}
	static int lua_SDL_GetPerformanceFrequency(State & state){
		Stack * stack = state.stack;
		Uint64 freq = SDL_GetPerformanceFrequency();
		stack->push<int>(freq & 0xFFFFFFFF);
		stack->push<int>(freq >> 32);
		return 2;
	}

	void initTimers(Module & module){
		module["delay"] = lua_SDL_Delay;
		module["getTicks"] = lua_SDL_GetTicks;
		module["getPerformanceCounter"] = lua_SDL_GetPerformanceCounter;
		module["getPerformanceFrequency"] = lua_SDL_GetPerformanceFrequency;
	}
}