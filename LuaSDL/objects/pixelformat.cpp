#include "objects/pixelformat.hpp"
#include <lua.hpp>

static int lua_SDL_AllocFormat(lutok::state& state){
	LuaSDL::Lua_SDL_PixelFormat * pf = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_PixelFormat);
	SDL_PixelFormat * pixelformat = SDL_AllocFormat(state.to_integer(1));
	if (pixelformat){
		pf->push(pixelformat);
	}else{
		state.push_boolean(false);
	}
	return 1;
}

static int lua_SDL_MasksToPixelFormatEnum(lutok::state& state){
	if (state.is_number(1) && state.is_number(2) && state.is_number(3) && state.is_number(4) && state.is_number(5)){
		int bpp = state.to_integer(1);
		Uint32 Rmask = state.to_integer(1);
		Uint32 Gmask = state.to_integer(2);
		Uint32 Bmask = state.to_integer(3);
		Uint32 Amask = state.to_integer(4);
		Uint32 format = SDL_MasksToPixelFormatEnum(bpp, Rmask, Gmask, Bmask, Amask);
		state.push_integer(format);
		return 1;
	}
	return 0;
}

static int lua_SDL_PixelFormatEnumToMasks(lutok::state& state){
	if (state.is_number(1)){
		Uint32 format = 0;
		int bpp;
		Uint32 Rmask, Gmask, Bmask, Amask;
		if (SDL_PixelFormatEnumToMasks(format, &bpp, &Rmask, &Gmask, &Bmask, &Amask) == SDL_TRUE){
			state.push_integer(bpp);
			state.push_integer(Rmask);
			state.push_integer(Gmask);
			state.push_integer(Bmask);
			state.push_integer(Amask);
			return 5;
		}else{
			state.push_boolean(false);
			return 1;
		}
	}
	return 0;
}


void LuaSDL::init_pixelformat(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_PixelFormat);
	module["allocFormat"] = lua_SDL_AllocFormat;
	module["masksToPixelFormatEnum"] = lua_SDL_MasksToPixelFormatEnum;
	module["pixelFormatEnumToMasks"] = lua_SDL_PixelFormatEnumToMasks;
}

