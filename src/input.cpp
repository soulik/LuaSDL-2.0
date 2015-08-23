#include "common.hpp"
#include "objects/window.hpp"
#include "objects/rect.hpp"

namespace LuaSDL {

	//Keyboard specific
	static int lua_SDL_GetKeyboardFocus(State & state){
		Stack * stack = state.stack;
		Window * interfaceWindow = state.getInterface<Window>("LuaSDL_Window");
		interfaceWindow->push(SDL_GetKeyboardFocus());
		return 1;
	}
	static int lua_SDL_GetKeyboardState_table(State & state){
		Stack * stack = state.stack;
		int numkeys = 0;
		if (stack->is<LUA_TNUMBER>(2)){
			int key = stack->to<int>(2);
			const Uint8 * keys = SDL_GetKeyboardState(&numkeys);
			if ((key >= 0) && (key < numkeys)){
				stack->push<bool>(keys[key] == 1);
				return 1;
			}else{
				return 0;
			}
		}else{
			return 0;
		}
	}
	static int lua_SDL_GetKeyboardState(State & state){
		Stack * stack = state.stack;
		stack->newTable();
			stack->newTable();
				stack->push<const std::string &>("__index");
				stack->push<Function>(lua_SDL_GetKeyboardState_table);
				stack->setTable();
			stack->setMetatable();
		return 1;
	}
	static int lua_SDL_GetKeyFromName(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			const std::string name = stack->to<const std::string>(1);
			stack->push<int>(SDL_GetKeyFromName(name.c_str()));
			return 1;
		}
		return 0;
	}
	static int lua_SDL_GetKeyFromScancode(State & state){
		Stack * stack = state.stack;
		stack->push<int>(SDL_GetKeyFromScancode((SDL_Scancode)stack->to<int>(1)));
		return 1;
	}
	static int lua_SDL_GetKeyName(State & state){
		Stack * stack = state.stack;
		stack->push<const std::string &>(SDL_GetKeyName(stack->to<int>(1)));
		return 1;
	}
	static int lua_SDL_GetModState(State & state){
		Stack * stack = state.stack;
		stack->push<int>(SDL_GetModState());
		return 1;
	}
	static int lua_SDL_GetNumKeyboards(State & state){
		Stack * stack = state.stack;
		/*
		stack->push<int>(SDL_GetNumKeyboards());
		return 1;
		*/
		return 0;
	}
	static int lua_SDL_GetScancodeFromKey(State & state){
		Stack * stack = state.stack;
		stack->push<int>(SDL_GetScancodeFromKey(stack->to<int>(1)));
		return 1;
	}
	static int lua_SDL_GetScancodeFromName(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			const std::string name = stack->to<const std::string>(1);
			stack->push<int>(SDL_GetScancodeFromName(name.c_str()));
			return 1;
		}
		return 0;
	}
	static int lua_SDL_GetScancodeName(State & state){
		Stack * stack = state.stack;
		stack->push<const std::string &>(SDL_GetScancodeName((SDL_Scancode)stack->to<int>(1)));
		return 1;
	}
	static int lua_SDL_SetModState(State & state){
		Stack * stack = state.stack;
		SDL_SetModState((SDL_Keymod)stack->to<int>(1));
		return 0;
	}
	static int lua_SDL_SetTextInputRect(State & state){
		Stack * stack = state.stack;
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
		SDL_Rect * r = interfaceRect->get(1);
		if (r){
			SDL_SetTextInputRect(r);
		}
		return 0;
	}
	static int lua_SDL_StartTextInput(State & state){
		Stack * stack = state.stack;
		SDL_StartTextInput();
		return 0;
	}
	static int lua_SDL_StopTextInput(State & state){
		Stack * stack = state.stack;
		SDL_StopTextInput();
		return 0;
	}

	//Mouse specific
	static int lua_SDL_GetMouseFocus(State & state){
		Stack * stack = state.stack;
		Window * interfaceWindow = state.getInterface<Window>("LuaSDL_Window");
		interfaceWindow->push(SDL_GetMouseFocus());
		return 1;
	}
	static int lua_SDL_GetMouseState(State & state){
		Stack * stack = state.stack;
		int x, y;
		Uint8 buttons;

		buttons = SDL_GetMouseState(&x,&y);
		stack->push<int>(x);
		stack->push<int>(y);
		stack->push<int>(buttons);
		return 3;
	}
	static int lua_SDL_GetRelativeMouseMode(State & state){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_GetRelativeMouseMode() == SDL_TRUE);
		return 1;
	}
	static int lua_SDL_GetRelativeMouseState(State & state){
		Stack * stack = state.stack;
		int x, y;
		Uint8 buttons;

		buttons = SDL_GetRelativeMouseState(&x,&y);
		stack->push<int>(x);
		stack->push<int>(y);
		stack->push<int>(buttons);
		return 3;
	}
	static int lua_SDL_WarpMouseInWindow(State & state){
		Stack * stack = state.stack;
		Window * interfaceWindow = state.getInterface<Window>("LuaSDL_Window");
		SDL_Window * w = interfaceWindow->get(1);

		if (w){
			SDL_WarpMouseInWindow(
				w,
				stack->to<int>(2),
				stack->to<int>(3));
		}
		return 0;
	}
	static int lua_SDL_SetRelativeMouseMode(State & state){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_SetRelativeMouseMode((stack->to<bool>(1)) ? SDL_TRUE : SDL_FALSE) == 0);
		return 0;
	}

	void initInput(Module & module){
		//Keyboard specific
		module["getKeyboardFocus"] = lua_SDL_GetKeyboardFocus;
		module["getKeyboardState"] = lua_SDL_GetKeyboardState;
		module["getKeyFromName"] = lua_SDL_GetKeyFromName;
		module["getKeyFromScancode"] = lua_SDL_GetKeyFromScancode;
		module["getKeyName"] = lua_SDL_GetKeyName;
		module["getModState"] = lua_SDL_GetModState;
		module["getNumKeyboards"] = lua_SDL_GetNumKeyboards;
		module["getScancodeFromKey"] = lua_SDL_GetScancodeFromKey;
		module["getScancodeFromName"] = lua_SDL_GetScancodeFromName;
		module["getScancodeName"] = lua_SDL_GetScancodeName;
		module["setModState"] = lua_SDL_SetModState;
		module["setTextInputRect"] = lua_SDL_SetTextInputRect;
		module["startTextInput"] = lua_SDL_StartTextInput;
		module["stopTextInput"] = lua_SDL_StopTextInput;

		//Mouse specific
		module["getMouseFocus"] = lua_SDL_GetMouseFocus;
		module["getMouseState"] = lua_SDL_GetMouseState;
		module["getRelativeMouseMode"] = lua_SDL_GetRelativeMouseMode;
		module["getRelativeMouseState"] = lua_SDL_GetRelativeMouseState;
		module["warpMouseInWindow"] = lua_SDL_WarpMouseInWindow;
		module["setRelativeMouseMode"] = lua_SDL_SetRelativeMouseMode;
	}
}