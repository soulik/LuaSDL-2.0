#include "common.hpp"

namespace LuaSDL {
	static int lua_SDL_GetPowerInfo(State & state){
		int secs = 0, pct = 0;
		Stack * stack = state.stack;
		SDL_PowerState powerState = SDL_GetPowerInfo(&secs, &pct);
		
		stack->push<int>(powerState);
		if (secs != -1){
			stack->push<int>(secs);
		}else{
			stack->push<bool>(false);
		}
		if (pct != -1){
			stack->push<int>(pct);
		}else{
			stack->push<bool>(false);
		}
		return 3;
	}

	void initPower(Module & module){
		module["powerInfo"] = lua_SDL_GetPowerInfo;
	}
}
