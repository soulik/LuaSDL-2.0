#include "common.hpp"
#include "objects/surface.hpp"
#include "objects/ttf_font.hpp"

namespace LuaSDL {

	static int lua_TTF_Init(lutok::state& state){
		int result = TTF_Init();
		state.push_integer(result);
		return 1;
	}
	static int lua_TTF_Quit(lutok::state& state){
		TTF_Quit();
		return 0;
	}
	static int lua_TTF_OpenFont(lutok::state& state){
		LuaSDL::Lua_SDL_TTF_Font * f = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_TTF_Font);
		if (state.is_string(1) && state.is_number(2)){
			TTF_Font * font = NULL;
			
			if (state.is_number(3)){
				font = TTF_OpenFontIndex(state.to_string(1).c_str(), state.to_integer(2), state.to_integer(3));
			}else{
				font = TTF_OpenFont(state.to_string(1).c_str(), state.to_integer(2));
			}
			if (font){
				f->push(font);
			}else{
				state.push_boolean(false);
			}
			return 1;
		}
		return 0;
	}
	static int lua_TTF_GetError(lutok::state& state){
		state.push_string(TTF_GetError());
		return 1;
	}
	static int lua_TTF_ByteSwappedUNICODE(lutok::state& state){
		int swapped = 0;
		if (state.is_number(1) || state.is_boolean(1)){
			swapped = state.to_integer(1);
		}
		TTF_ByteSwappedUNICODE(swapped);
		return 0;
	}

	void init_sdl_ttf(moduleDef & module){
		module["ttfInit"] = lua_TTF_Init;
		module["ttfQuit"] = lua_TTF_Quit;

		//Loading
		module["ttfOpenFont"] = lua_TTF_OpenFont;

		//Errors
		module["ttfGetError"] = lua_TTF_GetError;

		//Misc
		module["ttfByteSwappedUNICODE"] = lua_TTF_ByteSwappedUNICODE;
	}
}