#include "common.hpp"
#include "objects/window.hpp"
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

	static int lua_SDL_ShowSimpleMessageBox(lutok::state& state){
		if (state.is_number(1) && state.is_string(2) && state.is_string(3)){
			SDL_Window * window = NULL;
			if (!state.is_nil(4)){
				LuaSDL::Lua_SDL_Window * w = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Window);
				window = w->check(4);
			}
			state.push_boolean(SDL_ShowSimpleMessageBox(state.to_integer(1), state.to_string(2).c_str(), state.to_string(3).c_str(), window) == 0);
			return 1;
		}else{
			return 0;
		}
	}
	static int lua_SDL_ShowMessageBox(lutok::state& state){
		if (state.is_number(1) && state.is_string(2) && state.is_string(3)){
			SDL_MessageBoxData data;
			SDL_MessageBoxColorScheme colorScheme;
			SDL_MessageBoxButtonData * buttons=NULL;
			int button_id=0;
			
			if (!state.is_nil(4)){
				LuaSDL::Lua_SDL_Window * w = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Window);
				data.window = w->check(4);
			}else{
				data.window = NULL;
			}
			data.flags = state.to_integer(1);
			data.title = state.to_string(2).c_str();
			data.message = state.to_string(3).c_str();
			
			if (state.is_table(5)){
				int count = state.obj_len(5);
				int realCount = 0;
				buttons = new SDL_MessageBoxButtonData[count];

				for (int i=0; i<count; i++){
					state.push_integer(i+1);
					state.get_table(5);
					if (state.is_table()){
						state.get_field(-1, "flags");
						buttons[i].flags = state.to_integer(-1);
						state.get_field(-2, "id");
						buttons[i].buttonid = state.to_integer(-1);
						state.get_field(-3, "id");
						buttons[i].text = state.to_string(-1).c_str();
						state.pop(4);
						realCount++;
					}else{
						state.pop(1);
					}
				}
				data.buttons = buttons;
				data.numbuttons = realCount;
			}else{
				data.buttons = NULL;
				data.numbuttons = 0;
			}

			if (state.is_table(6)){
				int count = state.obj_len(6);
				if (count > SDL_MESSAGEBOX_COLOR_MAX) count = SDL_MESSAGEBOX_COLOR_MAX;
				int realCount = 0;
				for (int i=0; i<count; i++){
					state.push_integer(i+1);
					state.get_table(6);
					if (state.is_table()){
						state.get_field(-1, "r");
						colorScheme.colors[realCount].r = (Uint8)state.to_integer(-1);
						state.get_field(-2, "g");
						colorScheme.colors[realCount].g = (Uint8)state.to_integer(-1);
						state.get_field(-3, "g");
						colorScheme.colors[realCount].b = (Uint8)state.to_integer(-1);
						state.pop(4);
						realCount++;
					}else{
						state.pop(1);
					}
				}
				data.colorScheme = &colorScheme;
			}else{
				data.colorScheme = NULL;
			}

			state.push_boolean(SDL_ShowMessageBox(&data, &button_id) == 0);

			delete[] data.buttons;
			state.push_integer(button_id);
			return 1;
		}else{
			return 0;
		}
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
		module["showSimpleMessageBox"] = lua_SDL_ShowSimpleMessageBox;
		module["showMessageBox"] = lua_SDL_ShowMessageBox;
		
	}

}