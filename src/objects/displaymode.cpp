#include "objects/displaymode.hpp"
#include <lua.hpp>

static int lua_getPixelFormatName(State & state){
	switch (stack->to<int>(1)){
	case SDL_PIXELFORMAT_INDEX1LSB:
		stack->push<const std::string>("Indexed 1-bit LSB"); break;
	case SDL_PIXELFORMAT_INDEX1MSB:
		stack->push<const std::string>("Indexed 1-bit MSB"); break;
	case SDL_PIXELFORMAT_INDEX4LSB:
		stack->push<const std::string>("Indexed 4-bit LSB"); break;
	case SDL_PIXELFORMAT_INDEX4MSB:
		stack->push<const std::string>("Indexed 4-bit LSB"); break;
	case SDL_PIXELFORMAT_INDEX8:
		stack->push<const std::string>("Indexed 8-bit"); break;
	case SDL_PIXELFORMAT_RGB332:
		stack->push<const std::string>("8-bit RGB 332"); break;
	case SDL_PIXELFORMAT_RGB444:
		stack->push<const std::string>("12-bit RGB 444"); break;
	case SDL_PIXELFORMAT_RGB555:
		stack->push<const std::string>("15-bit RGB 555"); break;
	case SDL_PIXELFORMAT_BGR555:
		stack->push<const std::string>("15-bit BGR 555"); break;
	case SDL_PIXELFORMAT_ARGB4444:
		stack->push<const std::string>("16-bit ARGB 4444"); break;
	case SDL_PIXELFORMAT_RGBA4444:
		stack->push<const std::string>("16-bit RGBA 4444"); break;
	case SDL_PIXELFORMAT_ABGR4444:
		stack->push<const std::string>("16-bit ABGR 4444"); break;
	case SDL_PIXELFORMAT_BGRA4444:
		stack->push<const std::string>("16-bit BGRA 4444"); break;
	case SDL_PIXELFORMAT_ARGB1555:
		stack->push<const std::string>("16-bit ARGB 1555"); break;
	case SDL_PIXELFORMAT_RGBA5551:
		stack->push<const std::string>("16-bit RGBA 5551"); break;
	case SDL_PIXELFORMAT_ABGR1555:
		stack->push<const std::string>("16-bit ABGR 1555"); break;
	case SDL_PIXELFORMAT_BGRA5551:
		stack->push<const std::string>("16-bit BGRA 5551"); break;
	case SDL_PIXELFORMAT_RGB565:
		stack->push<const std::string>("16-bit RGB 565"); break;
	case SDL_PIXELFORMAT_BGR565:
		stack->push<const std::string>("16-bit BGR 565"); break;
	case SDL_PIXELFORMAT_RGB24:
		stack->push<const std::string>("24-bit RGB"); break;
	case SDL_PIXELFORMAT_BGR24:
		stack->push<const std::string>("24-bit BGR"); break;
	case SDL_PIXELFORMAT_RGB888:
		stack->push<const std::string>("24-bit RGB 888"); break;
	case SDL_PIXELFORMAT_RGBX8888:
		stack->push<const std::string>("32-bit RGBX 8888"); break;
	case SDL_PIXELFORMAT_BGR888:
		stack->push<const std::string>("24-bit BGR 888"); break;
	case SDL_PIXELFORMAT_BGRX8888:
		stack->push<const std::string>("32-bit BGRX 8888"); break;
	case SDL_PIXELFORMAT_ARGB8888:
		stack->push<const std::string>("32-bit ARGB 8888"); break;
	case SDL_PIXELFORMAT_RGBA8888:
		stack->push<const std::string>("32-bit RGBA 8888"); break;
	case SDL_PIXELFORMAT_ABGR8888:
		stack->push<const std::string>("32-bit ABGR 8888"); break;
	case SDL_PIXELFORMAT_BGRA8888:
		stack->push<const std::string>("32-bit BGRA 8888"); break;
	case SDL_PIXELFORMAT_ARGB2101010:
		stack->push<const std::string>("32-bit ARGB 2101010"); break;
	case SDL_PIXELFORMAT_YV12:
		stack->push<const std::string>("YV12"); break;
	case SDL_PIXELFORMAT_IYUV:
		stack->push<const std::string>("IYUV"); break;
	case SDL_PIXELFORMAT_YUY2:
		stack->push<const std::string>("YUY2"); break;
	case SDL_PIXELFORMAT_UYVY:
		stack->push<const std::string>("UYVY"); break;
	case SDL_PIXELFORMAT_YVYU:
		stack->push<const std::string>("YVYU"); break;
	default:
		stack->push<const std::string>("unknown");
	}

	return 1;
}

void LuaSDL::init_displaymode(State & state, Module & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_DisplayMode);
	module["getPixelFormatName"] = lua_getPixelFormatName;
}

