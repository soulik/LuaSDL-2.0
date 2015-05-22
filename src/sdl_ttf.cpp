#include "common.hpp"
#include "objects/surface.hpp"
#include "objects/ttf_font.hpp"

namespace LuaSDL {

	static int lua_TTF_Init(State & state){
		Stack * stack = state.stack;
		stack->push<bool>(TTF_Init() == 0);
		return 1;
	}
	static int lua_TTF_Quit(State & state){
		TTF_Quit();
		return 0;
	}
	static int lua_TTF_OpenFont(State & state){
		Stack * stack = state.stack;
		LuaSDL::Lua_SDL_TTF_Font & f = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_TTF_Font);
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TNUMBER>(2)){
			TTF_Font * font = NULL;
			
			if (stack->is<LUA_TNUMBER>(3)){
				font = TTF_OpenFontIndex(stack->to<const std::string>(1).c_str(), stack->to<int>(2), stack->to<int>(3));
			}else{
				font = TTF_OpenFont(stack->to<const std::string>(1).c_str(), stack->to<int>(2));
			}
			if (font){
				f.push(font);
			}else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}
	static int lua_TTF_GetError(State & state){
		Stack * stack = state.stack;
		stack->push<const std::string>(TTF_GetError());
		return 1;
	}
	static int lua_TTF_ByteSwappedUNICODE(State & state){
		Stack * stack = state.stack;
		int swapped = 0;
		if (stack->is<LUA_TNUMBER>(1) || stack->is<LUA_TBOOLEAN>(1)){
			swapped = stack->to<int>(1);
		}
		TTF_ByteSwappedUNICODE(swapped);
		return 0;
	}

	void init_sdl_ttf(Module & module){
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