#include "common.hpp"

namespace LuaSDL {
	static int lua_SDL_GetPowerInfo(lutok::state& state){
		int secs = 0, pct = 0;

		SDL_PowerState powerState = SDL_GetPowerInfo(&secs, &pct);
		
		state.push_integer(powerState);
		if (secs != -1){
			state.push_integer(secs);
		}else{
			state.push_boolean(false);
		}
		if (pct != -1){
			state.push_integer(pct);
		}else{
			state.push_boolean(false);
		}
		return 3;
	}

	void init_power(moduleDef & module){
		module["powerInfo"] = lua_SDL_GetPowerInfo;
	}
}
