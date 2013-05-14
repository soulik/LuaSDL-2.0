#include "objects/displaymode.hpp"
#include <lua.hpp>

static int lua_getPixelFormatName(lutok::state& state){
	switch (state.to_integer(1)){
	case SDL_PIXELFORMAT_INDEX1LSB:
		state.push_string("Indexed 1-bit LSB"); break;
	case SDL_PIXELFORMAT_INDEX1MSB:
		state.push_string("Indexed 1-bit MSB"); break;
	case SDL_PIXELFORMAT_INDEX4LSB:
		state.push_string("Indexed 4-bit LSB"); break;
	case SDL_PIXELFORMAT_INDEX4MSB:
		state.push_string("Indexed 4-bit LSB"); break;
	case SDL_PIXELFORMAT_INDEX8:
		state.push_string("Indexed 8-bit"); break;
	case SDL_PIXELFORMAT_RGB332:
		state.push_string("8-bit RGB 332"); break;
	case SDL_PIXELFORMAT_RGB444:
		state.push_string("12-bit RGB 444"); break;
	case SDL_PIXELFORMAT_RGB555:
		state.push_string("15-bit RGB 555"); break;
	case SDL_PIXELFORMAT_BGR555:
		state.push_string("15-bit BGR 555"); break;
	case SDL_PIXELFORMAT_ARGB4444:
		state.push_string("16-bit ARGB 4444"); break;
	case SDL_PIXELFORMAT_RGBA4444:
		state.push_string("16-bit RGBA 4444"); break;
	case SDL_PIXELFORMAT_ABGR4444:
		state.push_string("16-bit ABGR 4444"); break;
	case SDL_PIXELFORMAT_BGRA4444:
		state.push_string("16-bit BGRA 4444"); break;
	case SDL_PIXELFORMAT_ARGB1555:
		state.push_string("16-bit ARGB 1555"); break;
	case SDL_PIXELFORMAT_RGBA5551:
		state.push_string("16-bit RGBA 5551"); break;
	case SDL_PIXELFORMAT_ABGR1555:
		state.push_string("16-bit ABGR 1555"); break;
	case SDL_PIXELFORMAT_BGRA5551:
		state.push_string("16-bit BGRA 5551"); break;
	case SDL_PIXELFORMAT_RGB565:
		state.push_string("16-bit RGB 565"); break;
	case SDL_PIXELFORMAT_BGR565:
		state.push_string("16-bit BGR 565"); break;
	case SDL_PIXELFORMAT_RGB24:
		state.push_string("24-bit RGB"); break;
	case SDL_PIXELFORMAT_BGR24:
		state.push_string("24-bit BGR"); break;
	case SDL_PIXELFORMAT_RGB888:
		state.push_string("24-bit RGB 888"); break;
	case SDL_PIXELFORMAT_RGBX8888:
		state.push_string("32-bit RGBX 8888"); break;
	case SDL_PIXELFORMAT_BGR888:
		state.push_string("24-bit BGR 888"); break;
	case SDL_PIXELFORMAT_BGRX8888:
		state.push_string("32-bit BGRX 8888"); break;
	case SDL_PIXELFORMAT_ARGB8888:
		state.push_string("32-bit ARGB 8888"); break;
	case SDL_PIXELFORMAT_RGBA8888:
		state.push_string("32-bit RGBA 8888"); break;
	case SDL_PIXELFORMAT_ABGR8888:
		state.push_string("32-bit ABGR 8888"); break;
	case SDL_PIXELFORMAT_BGRA8888:
		state.push_string("32-bit BGRA 8888"); break;
	case SDL_PIXELFORMAT_ARGB2101010:
		state.push_string("32-bit ARGB 2101010"); break;
	case SDL_PIXELFORMAT_YV12:
		state.push_string("YV12"); break;
	case SDL_PIXELFORMAT_IYUV:
		state.push_string("IYUV"); break;
	case SDL_PIXELFORMAT_YUY2:
		state.push_string("YUY2"); break;
	case SDL_PIXELFORMAT_UYVY:
		state.push_string("UYVY"); break;
	case SDL_PIXELFORMAT_YVYU:
		state.push_string("YVYU"); break;
	default:
		state.push_string("unknown");
	}

	return 1;
}

void LuaSDL::init_displaymode(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_DisplayMode);
	module["getPixelFormatName"] = lua_getPixelFormatName;
}

