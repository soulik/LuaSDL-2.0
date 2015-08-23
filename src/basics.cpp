#include "common.hpp"
#include "objects/window.hpp"
#include <exception>

namespace LuaSDL {

	static int lua_SDL_Init(State & state){
		Stack * stack = state.stack;
		int retval=0;
		if (stack->is<LUA_TNUMBER>(1)){
			stack->push<bool>(SDL_Init(stack->to<int>(1))==0);
		}else{
			stack->push<bool>(SDL_Init(SDL_INIT_EVERYTHING)==0);
		}
		return 1;
	}
	static int lua_SDL_InitSubSystem(State & state){
		Stack * stack = state.stack;
		int retval = SDL_InitSubSystem(stack->to<int>(1));
		stack->push<bool>(retval == 0);
		return 1;
	}
	static int lua_SDL_Quit(State & state){
		Stack * stack = state.stack;
		try{
			SDL_Quit();
		}catch(std::exception *  e){
			stack->push<const std::string &>(e->what());
			return 1;
		}
		return 0;
	}
	static int lua_SDL_QuitSubSystem(State & state){
		Stack * stack = state.stack;
		SDL_QuitSubSystem(stack->to<int>(1));
		return 0;
	}
	static int lua_SDL_WasInit(State & state){
		Stack * stack = state.stack;
		Uint32 retval = SDL_WasInit(stack->to<int>(1));
		stack->push<int>(retval);
		return 1;
	}
	static int lua_SDL_ClearHints(State & state){
		Stack * stack = state.stack;
		SDL_ClearHints();
		return 0;
	}
	static int lua_SDL_GetHint(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			const std::string hintName = stack->to<const std::string>(1);
			const char * retval = SDL_GetHint(hintName.c_str());
			if (retval){
				stack->push<const std::string &>(retval);
				return 1;
			}
		}
		return 0;
	}
	static int lua_SDL_SetHint(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TSTRING>(2)){
			const std::string hintName = stack->to<const std::string>(1);
			const std::string hintValue = stack->to<const std::string>(2);
			stack->push<bool>(
				(SDL_SetHint(hintName.c_str(), hintName.c_str()
				) == SDL_TRUE));
			return 1;
		}
		return 0;
	}
	static int lua_SDL_SetHintWithPriority(State & state){
		Stack * stack = state.stack;

		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TSTRING>(2)){
			const std::string hintName = stack->to<const std::string>(1);
			const std::string hintValue = stack->to<const std::string>(2);

			stack->push<bool>(
				(SDL_SetHintWithPriority(hintName.c_str(), hintValue.c_str(), (SDL_HintPriority)stack->to<int>(3)
				) == SDL_TRUE));
			return 1;
		}
		return 0;
	}
	static int lua_SDL_ClearError(State & state){
		Stack * stack = state.stack;
		SDL_ClearError();
		return 0;
	}
	static int lua_SDL_GetError(State & state){
		Stack * stack = state.stack;
		stack->push<const std::string &>(SDL_GetError());
		return 1;
	}
	static int lua_SDL_SetError(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			const std::string fmt = stack->to<const std::string>(1);
			SDL_SetError("%s", fmt.c_str());
		}
		return 0;
	}
	static int lua_SDL_LogMessage(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(3)){
			const std::string text = stack->to<const std::string>(3);
			SDL_LogMessage(
				stack->to<int>(1),
				(SDL_LogPriority)stack->to<int>(2),
				"%s",
				text.c_str());
		}
		return 0;
	}
	static int lua_SDL_LogGetPriority(State & state){
		Stack * stack = state.stack;
		stack->push<int>(
			SDL_LogGetPriority(stack->to<int>(1)));
		return 0;
	}
	static int lua_SDL_LogResetPriorities(State & state){
		Stack * stack = state.stack;
		SDL_LogResetPriorities();
		return 0;
	}
	static int lua_SDL_LogSetAllPriority(State & state){
		Stack * stack = state.stack;
		SDL_LogSetAllPriority((SDL_LogPriority)stack->to<int>(1));
		return 0;
	}
	static int lua_SDL_LogSetPriority(State & state){
		Stack * stack = state.stack;
		SDL_LogSetPriority(stack->to<int>(1), (SDL_LogPriority) stack->to<int>(2));
		return 0;
	}
	static int lua_SDL_GetVersion(State & state){
		Stack * stack = state.stack;
		SDL_version ver;
		SDL_GetVersion(&ver);

		stack->newTable();
		stack->push<int>(1);
		stack->push<int>(ver.major);
		stack->setTable(-3);
		stack->push<int>(2);
		stack->push<int>(ver.minor);
		stack->setTable(-3);
		stack->push<int>(3);
		stack->push<int>(ver.patch);
		stack->setTable(-3);
		return 1;
	}

	static int lua_SDL_ShowSimpleMessageBox(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TSTRING>(2) && stack->is<LUA_TSTRING>(3)){
			SDL_Window * window = NULL;
			if (stack->is<LUA_TUSERDATA>(4)){
				Window * interfaceWindow = state.getInterface<Window>("LuaSDL_Window");
				window = interfaceWindow->get(4);
			}
			const std::string title = stack->to<const std::string>(2);
			const std::string message = stack->to<const std::string>(3);
			stack->push<bool>(SDL_ShowSimpleMessageBox(stack->to<int>(1), title.c_str(), message.c_str(), window) == 0);
			return 1;
		}else{
			return 0;
		}
	}
	static int lua_SDL_ShowMessageBox(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TSTRING>(2) && stack->is<LUA_TSTRING>(3)){
			SDL_MessageBoxData data;
			SDL_MessageBoxColorScheme colorScheme;
			SDL_MessageBoxButtonData * buttons=NULL;
			int button_id=0;
			
			if (!stack->is<LUA_TNIL>(4)){
				Window * interfaceWindow = state.getInterface<Window>("LuaSDL_Window");
				data.window = interfaceWindow->get(4);
			}else{
				data.window = NULL;
			}
			const std::string title = stack->to<const std::string>(2);
			const std::string message = stack->to<const std::string>(3);

			data.flags = stack->to<int>(1);
			data.title = title.c_str();
			data.message = message.c_str();
			
			if (stack->is<LUA_TTABLE>(5)){
				int count = stack->objLen(5);
				int realCount = 0;
				buttons = new SDL_MessageBoxButtonData[count];

				for (int i=0; i<count; i++){
					stack->push<int>(i+1);
					stack->getTable(5);
					if (stack->is<LUA_TTABLE>()){
						stack->getField("flags", -1);
						buttons[i].flags = stack->to<int>(-1);
						stack->getField("id", -2);
						buttons[i].buttonid = stack->to<int>(-1);
						stack->getField("id", -3);

						const std::string text = stack->toLString(-1);
						buttons[i].text = new const char[text.length()+1];
						memcpy(const_cast<void*>(static_cast<const void *>(buttons[i].text)), text.c_str(), text.length() + 1);
						stack->pop(4);
						realCount++;
					}else{
						stack->pop(1);
					}
				}
				data.buttons = buttons;
				data.numbuttons = realCount;
			}else{
				data.buttons = NULL;
				data.numbuttons = 0;
			}

			if (stack->is<LUA_TTABLE>(6)){
				int count = stack->objLen(6);
				if (count > SDL_MESSAGEBOX_COLOR_MAX) count = SDL_MESSAGEBOX_COLOR_MAX;
				int realCount = 0;
				for (int i=0; i<count; i++){
					stack->push<int>(i+1);
					stack->getTable(6);
					if (stack->is<LUA_TTABLE>()){
						stack->getField("r", -1);
						colorScheme.colors[realCount].r = (Uint8)stack->to<int>(-1);
						stack->getField("g", -2);
						colorScheme.colors[realCount].g = (Uint8)stack->to<int>(-1);
						stack->getField("g", -3);
						colorScheme.colors[realCount].b = (Uint8)stack->to<int>(-1);
						stack->pop(4);
						realCount++;
					}else{
						stack->pop(1);
					}
				}
				data.colorScheme = &colorScheme;
			}else{
				data.colorScheme = NULL;
			}

			stack->push<bool>(SDL_ShowMessageBox(&data, &button_id) == 0);

			for (size_t i = 0; i < data.numbuttons; i++){
				delete data.buttons[i].text;
			}
			delete[] data.buttons;
			stack->push<int>(button_id);
			return 1;
		}else{
			return 0;
		}
	}

	static int lua_SDL_GetBasePath(State & state){
		Stack * stack = state.stack;
		stack->push<const std::string &>(SDL_GetBasePath());
		return 1;
	}

	static int lua_SDL_GetPrefPath(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TSTRING>(2)){
			const std::string org = stack->to<const std::string>(1);
			const std::string app = stack->to<const std::string>(2);
			stack->push<const std::string &>(SDL_GetPrefPath(org.c_str(), app.c_str()));
			return 1;
		}
		else{
			return 0;
		}
	}

	void initBasic(Module & module){
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
		module["logSetPriority"] = lua_SDL_LogSetPriority;
		module["getVersion"] = lua_SDL_GetVersion;
		module["showSimpleMessageBox"] = lua_SDL_ShowSimpleMessageBox;
		module["showMessageBox"] = lua_SDL_ShowMessageBox;
		module["basePath"] = lua_SDL_GetBasePath;
		module["prefPath"] = lua_SDL_GetPrefPath;

	}

}