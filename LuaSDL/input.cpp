#include "common.hpp"
#include "objects/window.hpp"
#include "objects/rect.hpp"

namespace LuaSDL {

	//Keyboard specific
	static int lua_SDL_GetKeyboardFocus(lutok::state& state){
		Lua_SDL_Window * w = LOBJECT_INSTANCE(Lua_SDL_Window);
		w->push(SDL_GetKeyboardFocus());
		return 1;
	}
	static int lua_SDL_GetKeyboardState_table(lutok::state& state){
		int numkeys = 0;
		if (state.is_number(2)){
			int key = state.to_integer(2);
			const Uint8 * keys = SDL_GetKeyboardState(&numkeys);
			if ((key >= 0) && (key < numkeys)){
				state.push_boolean(keys[key] == 1);
				return 1;
			}else{
				return 0;
			}
		}else{
			return 0;
		}
	}
	static int lua_SDL_GetKeyboardState(lutok::state& state){
		state.new_table();
			state.new_table();
				state.push_literal("__index");
				state.push_cxx_function(lua_SDL_GetKeyboardState_table);
				state.set_table();
			state.set_metatable(-2);
		return 1;
	}
	static int lua_SDL_GetKeyFromName(lutok::state& state){
		state.push_integer(SDL_GetKeyFromName(state.to_string(1).c_str()));
		return 1;
	}
	static int lua_SDL_GetKeyFromScancode(lutok::state& state){
		state.push_integer(SDL_GetKeyFromScancode((SDL_Scancode)state.to_integer(1)));
		return 1;
	}
	static int lua_SDL_GetKeyName(lutok::state& state){
		state.push_string(SDL_GetKeyName(state.to_integer(1)));
		return 1;
	}
	static int lua_SDL_GetModState(lutok::state& state){
		state.push_integer(SDL_GetModState());
		return 1;
	}
	static int lua_SDL_GetNumKeyboards(lutok::state& state){
		/*
		state.push_integer(SDL_GetNumKeyboards());
		return 1;
		*/
		return 0;
	}
	static int lua_SDL_GetScancodeFromKey(lutok::state& state){
		state.push_integer(SDL_GetScancodeFromKey(state.to_integer(1)));
		return 1;
	}
	static int lua_SDL_GetScancodeFromName(lutok::state& state){
		state.push_integer(SDL_GetScancodeFromName(state.to_string(1).c_str()));
		return 1;
	}
	static int lua_SDL_GetScancodeName(lutok::state& state){
		state.push_string(SDL_GetScancodeName((SDL_Scancode)state.to_integer(1)));
		return 1;
	}
	static int lua_SDL_SetModState(lutok::state& state){
		SDL_SetModState((SDL_Keymod)state.to_integer(1));
		return 0;
	}
	static int lua_SDL_SetTextInputRect(lutok::state& state){
		Lua_SDL_Rect * r = LOBJECT_INSTANCE(Lua_SDL_Rect);
		SDL_SetTextInputRect(r->check(1));
		return 0;
	}
	static int lua_SDL_StartTextInput(lutok::state& state){
		SDL_StartTextInput();
		return 0;
	}
	static int lua_SDL_StopTextInput(lutok::state& state){
		SDL_StopTextInput();
		return 0;
	}

	//Mouse specific
	static int lua_SDL_GetMouseFocus(lutok::state& state){
		Lua_SDL_Window * w = LOBJECT_INSTANCE(Lua_SDL_Window);
		w->push(SDL_GetMouseFocus());
		return 1;
	}
	static int lua_SDL_GetMouseState(lutok::state& state){
		int x,y;
		Uint8 buttons;

		buttons = SDL_GetMouseState(&x,&y);
		state.push_integer(x);
		state.push_integer(y);
		state.push_integer(buttons);
		return 3;
	}
	static int lua_SDL_GetRelativeMouseMode(lutok::state& state){
		state.push_boolean(SDL_GetRelativeMouseMode() == SDL_TRUE);
		return 1;
	}
	static int lua_SDL_GetRelativeMouseState(lutok::state& state){
		int x,y;
		Uint8 buttons;

		buttons = SDL_GetRelativeMouseState(&x,&y);
		state.push_integer(x);
		state.push_integer(y);
		state.push_integer(buttons);
		return 3;
	}
	static int lua_SDL_WarpMouseInWindow(lutok::state& state){
		Lua_SDL_Window * w = LOBJECT_INSTANCE(Lua_SDL_Window);
		SDL_WarpMouseInWindow(
			w->check(1),
			state.to_integer(2),
			state.to_integer(3));
		return 0;
	}
	static int lua_SDL_SetRelativeMouseMode(lutok::state& state){
		state.push_boolean(SDL_SetRelativeMouseMode((state.to_boolean(1)) ? SDL_TRUE : SDL_FALSE ) == 0);
		return 0;
	}

	//Joystick specific
	static int lua_SDL_JoystickOpen(lutok::state& state){

		return 1;
	}
	void init_input(moduleDef & module){
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