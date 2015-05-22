#include "objects/pixelformat.hpp"
#include <lua.hpp>

static int lua_SDL_AllocFormat(State & state){
	LuaSDL::Lua_SDL_PixelFormat & pf = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_PixelFormat);
	Uint32 pname;
	if (stack->is<LUA_TNUMBER>(1)){
		pname = (Uint32) stack->to<int>(1);
	}else{
		pname = SDL_PIXELFORMAT_UNKNOWN;
	}
	SDL_PixelFormat * pixelformat = SDL_AllocFormat(pname);
	if (pixelformat){
		pf.push(pixelformat);
	}else{
		stack->push<bool>(false);
	}
	return 1;
}

static int lua_SDL_MasksToPixelFormatEnum(State & state){
	if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2) && stack->is<LUA_TNUMBER>(3) && stack->is<LUA_TNUMBER>(4) && stack->is<LUA_TNUMBER>(5)){
		int bpp = stack->to<int>(1);
		Uint32 Rmask = stack->to<int>(1);
		Uint32 Gmask = stack->to<int>(2);
		Uint32 Bmask = stack->to<int>(3);
		Uint32 Amask = stack->to<int>(4);
		Uint32 format = SDL_MasksToPixelFormatEnum(bpp, Rmask, Gmask, Bmask, Amask);
		stack->push<int>(format);
		return 1;
	}
	return 0;
}

static int lua_SDL_PixelFormatEnumToMasks(State & state){
	if (stack->is<LUA_TNUMBER>(1)){
		Uint32 format = 0;
		int bpp;
		Uint32 Rmask, Gmask, Bmask, Amask;
		if (SDL_PixelFormatEnumToMasks(format, &bpp, &Rmask, &Gmask, &Bmask, &Amask) == SDL_TRUE){
			stack->push<int>(bpp);
			stack->push<int>(Rmask);
			stack->push<int>(Gmask);
			stack->push<int>(Bmask);
			stack->push<int>(Amask);
			return 5;
		}else{
			stack->push<bool>(false);
			return 1;
		}
	}
	return 0;
}


void LuaSDL::init_pixelformat(State & state, Module & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_PixelFormat);
	module["allocFormat"] = lua_SDL_AllocFormat;
	module["masksToPixelFormatEnum"] = lua_SDL_MasksToPixelFormatEnum;
	module["pixelFormatEnumToMasks"] = lua_SDL_PixelFormatEnumToMasks;
}

