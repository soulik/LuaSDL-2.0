#include "common.hpp"
#include "objects/window.hpp"
#include "objects/rect.hpp"

namespace LuaSDL {

	//Keyboard specific
	static int lua_SDL_GetKeyboardFocus(State & state){
		Lua_SDL_Window & w = LOBJECT_INSTANCE(Lua_SDL_Window);
		w.push(SDL_GetKeyboardFocus());
		return 1;
	}
	static int lua_SDL_GetKeyboardState_table(State & state){
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
		stack->newTable();
			stack->newTable();
				state.push_literal("__index");
				state.push_cxx_function(lua_SDL_GetKeyboardState_table);
				stack->setTable();
			state.set_metatable(-2);
		return 1;
	}
	static int lua_SDL_GetKeyFromName(State & state){
		stack->push<int>(SDL_GetKeyFromName(stack->to<const std::string>(1).c_str()));
		return 1;
	}
	static int lua_SDL_GetKeyFromScancode(State & state){
		stack->push<int>(SDL_GetKeyFromScancode((SDL_Scancode)stack->to<int>(1)));
		return 1;
	}
	static int lua_SDL_GetKeyName(State & state){
		stack->push<const std::string>(SDL_GetKeyName(stack->to<int>(1)));
		return 1;
	}
	static int lua_SDL_GetModState(State & state){
		stack->push<int>(SDL_GetModState());
		return 1;
	}
	static int lua_SDL_GetNumKeyboards(State & state){
		/*
		stack->push<int>(SDL_GetNumKeyboards());
		return 1;
		*/
		return 0;
	}
	static int lua_SDL_GetScancodeFromKey(State & state){
		stack->push<int>(SDL_GetScancodeFromKey(stack->to<int>(1)));
		return 1;
	}
	static int lua_SDL_GetScancodeFromName(State & state){
		stack->push<int>(SDL_GetScancodeFromName(stack->to<const std::string>(1).c_str()));
		return 1;
	}
	static int lua_SDL_GetScancodeName(State & state){
		stack->push<const std::string>(SDL_GetScancodeName((SDL_Scancode)stack->to<int>(1)));
		return 1;
	}
	static int lua_SDL_SetModState(State & state){
		SDL_SetModState((SDL_Keymod)stack->to<int>(1));
		return 0;
	}
	static int lua_SDL_SetTextInputRect(State & state){
		Lua_SDL_Rect & r = LOBJECT_INSTANCE(Lua_SDL_Rect);
		SDL_SetTextInputRect(r.check(1));
		return 0;
	}
	static int lua_SDL_StartTextInput(State & state){
		SDL_StartTextInput();
		return 0;
	}
	static int lua_SDL_StopTextInput(State & state){
		SDL_StopTextInput();
		return 0;
	}

	//Mouse specific
	static int lua_SDL_GetMouseFocus(State & state){
		Lua_SDL_Window & w = LOBJECT_INSTANCE(Lua_SDL_Window);
		w.push(SDL_GetMouseFocus());
		return 1;
	}
	static int lua_SDL_GetMouseState(State & state){
		int x,y;
		Uint8 buttons;

		buttons = SDL_GetMouseState(&x,&y);
		stack->push<int>(x);
		stack->push<int>(y);
		stack->push<int>(buttons);
		return 3;
	}
	static int lua_SDL_GetRelativeMouseMode(State & state){
		stack->push<bool>(SDL_GetRelativeMouseMode() == SDL_TRUE);
		return 1;
	}
	static int lua_SDL_GetRelativeMouseState(State & state){
		int x,y;
		Uint8 buttons;

		buttons = SDL_GetRelativeMouseState(&x,&y);
		stack->push<int>(x);
		stack->push<int>(y);
		stack->push<int>(buttons);
		return 3;
	}
	static int lua_SDL_WarpMouseInWindow(State & state){
		Lua_SDL_Window & w = LOBJECT_INSTANCE(Lua_SDL_Window);
		SDL_WarpMouseInWindow(
			w.check(1),
			stack->to<int>(2),
			stack->to<int>(3));
		return 0;
	}
	static int lua_SDL_SetRelativeMouseMode(State & state){
		stack->push<bool>(SDL_SetRelativeMouseMode((stack->to<bool>(1)) ? SDL_TRUE : SDL_FALSE ) == 0);
		return 0;
	}

	//Joystick specific
	static int lua_SDL_JoystickOpen(State & state){

		return 1;
	}
	void init_input(Module & module){
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