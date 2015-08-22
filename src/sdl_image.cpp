#include "common.hpp"
#include "objects/surface.hpp"

namespace LuaSDL {

	static int lua_IMG_Init(State & state){
		Stack * stack = state.stack;
		int result = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			result = IMG_Init(stack->to<int>(1));
		}else{
			result = IMG_Init(0);
		}
		stack->push<int>(result);
		return 1;
	}
	static int lua_IMG_Quit(State & state){
		IMG_Quit();
		return 0;
	}
	static int lua_IMG_Load(State & state){
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		if (stack->is<LUA_TSTRING>(1)){
			const std::string fileName = stack->to<const std::string>(1);
			SDL_Surface * surface = IMG_Load(fileName.c_str());
			if (surface){
				interfaceSurface->push(surface, true);
			}else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}
	static int lua_IMG_GetError(State & state){
		Stack * stack = state.stack;
		stack->push<const std::string &>(IMG_GetError());
		return 1;
	}

	void initSDLimage(Module & module){
		module["imageInit"] = lua_IMG_Init;
		module["imageQuit"] = lua_IMG_Quit;

		//Loading
		module["imageLoad"] = lua_IMG_Load;

		//Errors
		module["imageGetError"] = lua_IMG_GetError;
	}
}