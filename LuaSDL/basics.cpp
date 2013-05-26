#include "common.hpp"
#include <exception>

namespace LuaSDL {

	static int lua_SDL_Init(lutok::state& state){
		int retval=0;
		if (state.is_number(1)){
			state.push_boolean(SDL_Init(state.to_integer(1))==0);
		}else{
			state.push_boolean(SDL_Init(SDL_INIT_EVERYTHING)==0);
		}
		return 1;
	}
	static int lua_SDL_InitSubSystem(lutok::state& state){
		int retval = SDL_InitSubSystem(state.to_integer(1));
		state.push_boolean(retval == 0);
		return 1;
	}
	static int lua_SDL_Quit(lutok::state& state){
		try{
			SDL_Quit();
		}catch(std::exception *  e){
			state.push_string(e->what());
			return 1;
		}
		return 0;
	}
	static int lua_SDL_QuitSubSystem(lutok::state& state){
		SDL_QuitSubSystem(state.to_integer(1));
		return 0;
	}
	static int lua_SDL_WasInit(lutok::state& state){
		Uint32 retval = SDL_WasInit(state.to_integer(1));
		state.push_integer(retval);
		return 1;
	}
	static int lua_SDL_ClearHints(lutok::state& state){
		SDL_ClearHints();
		return 0;
	}
	static int lua_SDL_GetHint(lutok::state& state){
		const char * retval = SDL_GetHint(state.to_string(1).c_str());
		if (retval){
			state.push_string(retval);
			return 1;
		}else{
			return 0;
		}
	}
	static int lua_SDL_SetHint(lutok::state& state){
		state.push_boolean(
			(SDL_SetHint(
				state.to_string(1).c_str(),
				state.to_string(2).c_str()
			)==SDL_TRUE));
		return 1;
	}
	static int lua_SDL_SetHintWithPriority(lutok::state& state){
		state.push_boolean(
			(SDL_SetHintWithPriority(
				state.to_string(1).c_str(),
				state.to_string(2).c_str(),
				(SDL_HintPriority)state.to_integer(3)
			) == SDL_TRUE ));
		return 1;
	}
	static int lua_SDL_ClearError(lutok::state& state){
		SDL_ClearError();
		return 0;
	}
	static int lua_SDL_GetError(lutok::state& state){
		state.push_string(SDL_GetError());
		return 1;
	}
	static int lua_SDL_SetError(lutok::state& state){
		const char * fmt = state.to_string(1).c_str();
		SDL_SetError("%s", fmt);
		return 0;
	}
	static int lua_SDL_LogMessage(lutok::state& state){
		SDL_LogMessage(
			state.to_integer(1),
			(SDL_LogPriority) state.to_integer(2),
			"%s",
			state.to_string(3).c_str());
		return 0;
	}
	static int lua_SDL_LogGetPriority(lutok::state& state){
		state.push_integer(
			SDL_LogGetPriority(state.to_integer(1)));
		return 0;
	}
	static int lua_SDL_LogResetPriorities(lutok::state& state){
		SDL_LogResetPriorities();
		return 0;
	}
	static int lua_SDL_LogSetAllPriority(lutok::state& state){
		SDL_LogSetAllPriority((SDL_LogPriority)state.to_integer(1));
		return 0;
	}
	static int lua_SDL_LogSetPriority(lutok::state& state){
		SDL_LogSetPriority(state.to_integer(1), (SDL_LogPriority) state.to_integer(2));
		return 0;
	}
	static int lua_SDL_GetVersion(lutok::state& state){
		SDL_version ver;
		SDL_GetVersion(&ver);

		state.new_table();
		state.push_integer(1);
		state.push_integer(ver.major);
		state.set_table(-3);
		state.push_integer(2);
		state.push_integer(ver.minor);
		state.set_table(-3);
		state.push_integer(3);
		state.push_integer(ver.patch);
		state.set_table(-3);
		return 1;
	}

	void init_basic(moduleDef & module){
		module["init"] = lua_SDL_Init;
		module["initSubsystem"] = lua_SDL_InitSubSystem;
		module["quit"] = lua_SDL_Quit;
		module["quitSubsystem"] = lua_SDL_QuitSubSystem;
		module["wasInit"] = lua_SDL_WasInit;
		module["clearHints"] = lua_SDL_ClearHints;
		module["getHint"] = lua_SDL_GetHint;
		module["setHint"] = lua_SDL_SetHint;
		module["setHintWithPriority"] = lua_SDL_SetHintWithPriority;
		module["clearError"] = lua_SDL_ClearError;
		module["getError"] = lua_SDL_GetError;
		module["setError"] = lua_SDL_SetError;
		module["logMessage"] = lua_SDL_LogMessage;
		module["logGetPriority"] = lua_SDL_LogGetPriority;
		module["logResetPriorities"] = lua_SDL_LogResetPriorities;
		module["logSetAllPriority"] = lua_SDL_LogSetAllPriority;
		module["LogSetPriority"] = lua_SDL_LogSetPriority;
		module["getVersion"] = lua_SDL_GetVersion;
	}

}