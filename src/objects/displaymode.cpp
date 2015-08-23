#include "objects/displaymode.hpp"

namespace LuaSDL {
	static int lua_getPixelFormatName(State & state){
		Stack * stack = state.stack;

		switch (stack->to<int>(1)){
		case SDL_PIXELFORMAT_INDEX1LSB:
			stack->push<const std::string &>("Indexed 1-bit LSB"); break;
		case SDL_PIXELFORMAT_INDEX1MSB:
			stack->push<const std::string &>("Indexed 1-bit MSB"); break;
		case SDL_PIXELFORMAT_INDEX4LSB:
			stack->push<const std::string &>("Indexed 4-bit LSB"); break;
		case SDL_PIXELFORMAT_INDEX4MSB:
			stack->push<const std::string &>("Indexed 4-bit LSB"); break;
		case SDL_PIXELFORMAT_INDEX8:
			stack->push<const std::string &>("Indexed 8-bit"); break;
		case SDL_PIXELFORMAT_RGB332:
			stack->push<const std::string &>("8-bit RGB 332"); break;
		case SDL_PIXELFORMAT_RGB444:
			stack->push<const std::string &>("12-bit RGB 444"); break;
		case SDL_PIXELFORMAT_RGB555:
			stack->push<const std::string &>("15-bit RGB 555"); break;
		case SDL_PIXELFORMAT_BGR555:
			stack->push<const std::string &>("15-bit BGR 555"); break;
		case SDL_PIXELFORMAT_ARGB4444:
			stack->push<const std::string &>("16-bit ARGB 4444"); break;
		case SDL_PIXELFORMAT_RGBA4444:
			stack->push<const std::string &>("16-bit RGBA 4444"); break;
		case SDL_PIXELFORMAT_ABGR4444:
			stack->push<const std::string &>("16-bit ABGR 4444"); break;
		case SDL_PIXELFORMAT_BGRA4444:
			stack->push<const std::string &>("16-bit BGRA 4444"); break;
		case SDL_PIXELFORMAT_ARGB1555:
			stack->push<const std::string &>("16-bit ARGB 1555"); break;
		case SDL_PIXELFORMAT_RGBA5551:
			stack->push<const std::string &>("16-bit RGBA 5551"); break;
		case SDL_PIXELFORMAT_ABGR1555:
			stack->push<const std::string &>("16-bit ABGR 1555"); break;
		case SDL_PIXELFORMAT_BGRA5551:
			stack->push<const std::string &>("16-bit BGRA 5551"); break;
		case SDL_PIXELFORMAT_RGB565:
			stack->push<const std::string &>("16-bit RGB 565"); break;
		case SDL_PIXELFORMAT_BGR565:
			stack->push<const std::string &>("16-bit BGR 565"); break;
		case SDL_PIXELFORMAT_RGB24:
			stack->push<const std::string &>("24-bit RGB"); break;
		case SDL_PIXELFORMAT_BGR24:
			stack->push<const std::string &>("24-bit BGR"); break;
		case SDL_PIXELFORMAT_RGB888:
			stack->push<const std::string &>("24-bit RGB 888"); break;
		case SDL_PIXELFORMAT_RGBX8888:
			stack->push<const std::string &>("32-bit RGBX 8888"); break;
		case SDL_PIXELFORMAT_BGR888:
			stack->push<const std::string &>("24-bit BGR 888"); break;
		case SDL_PIXELFORMAT_BGRX8888:
			stack->push<const std::string &>("32-bit BGRX 8888"); break;
		case SDL_PIXELFORMAT_ARGB8888:
			stack->push<const std::string &>("32-bit ARGB 8888"); break;
		case SDL_PIXELFORMAT_RGBA8888:
			stack->push<const std::string &>("32-bit RGBA 8888"); break;
		case SDL_PIXELFORMAT_ABGR8888:
			stack->push<const std::string &>("32-bit ABGR 8888"); break;
		case SDL_PIXELFORMAT_BGRA8888:
			stack->push<const std::string &>("32-bit BGRA 8888"); break;
		case SDL_PIXELFORMAT_ARGB2101010:
			stack->push<const std::string &>("32-bit ARGB 2101010"); break;
		case SDL_PIXELFORMAT_YV12:
			stack->push<const std::string &>("YV12"); break;
		case SDL_PIXELFORMAT_IYUV:
			stack->push<const std::string &>("IYUV"); break;
		case SDL_PIXELFORMAT_YUY2:
			stack->push<const std::string &>("YUY2"); break;
		case SDL_PIXELFORMAT_UYVY:
			stack->push<const std::string &>("UYVY"); break;
		case SDL_PIXELFORMAT_YVYU:
			stack->push<const std::string &>("YVYU"); break;
		default:
			stack->push<const std::string &>("unknown");
		}

		return 1;
	}

	int inline DisplayMode::getFormat(State & state, SDL_DisplayMode * displayMode) {
		Stack * stack = state.stack;
		stack->push<int>(displayMode->format);
		return 1;
	}
	int inline DisplayMode::setFormat(State & state, SDL_DisplayMode * displayMode) {
		Stack * stack = state.stack;
		displayMode->format = stack->to<int>(1);
		return 0;
	}
	int inline DisplayMode::getW(State & state, SDL_DisplayMode * displayMode) {
		Stack * stack = state.stack;
		stack->push<int>(displayMode->w);
		return 1;
	}
	int inline DisplayMode::setW(State & state, SDL_DisplayMode * displayMode) {
		Stack * stack = state.stack;
		displayMode->w = stack->to<int>(1);
		return 0;
	}
	int inline DisplayMode::getH(State & state, SDL_DisplayMode * displayMode) {
		Stack * stack = state.stack;
		stack->push<int>(displayMode->h);
		return 1;
	}
	int inline DisplayMode::setH(State & state, SDL_DisplayMode * displayMode) {
		Stack * stack = state.stack;
		displayMode->h = stack->to<int>(1);
		return 0;
	}
	int inline DisplayMode::getRefreshRate(State & state, SDL_DisplayMode * displayMode) {
		Stack * stack = state.stack;
		stack->push<int>(displayMode->refresh_rate);
		return 1;
	}
	int inline DisplayMode::setRefreshRate(State & state, SDL_DisplayMode * displayMode) {
		Stack * stack = state.stack;
		displayMode->refresh_rate = stack->to<int>(1);
		return 0;
	}

	int inline DisplayMode::getDriverData(State & state, SDL_DisplayMode * displayMode) {
		Stack * stack = state.stack;
		stack->push<void*>(displayMode->driverdata);
		return 1;
	}

	int inline DisplayMode::setDriverData(State & state, SDL_DisplayMode * displayMode) {
		Stack * stack = state.stack;
		displayMode->driverdata = (void*)stack->to<void*>(1);
		return 0;
	}

	int DisplayMode::getClosestDisplayMode(State & state, SDL_DisplayMode * displayMode){
		Stack * stack = state.stack;
		DisplayMode * interfaceDisplayMode = state.getInterface<DisplayMode>("LuaSDL_DisplayMode");
		int displayIndex = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			displayIndex = stack->to<int>(1);
		}
		SDL_DisplayMode * closest = new SDL_DisplayMode;
		SDL_DisplayMode * closestOut = SDL_GetClosestDisplayMode(displayIndex, displayMode, closest);
		if (closestOut){
			interfaceDisplayMode->push(closestOut, true);
			return 1;
		}
		else{
			delete closest;
		}
		return 0;
	}

	void initDisplayMode(State * state, Module & module){
		INIT_OBJECT(DisplayMode);
		module["getPixelFormatName"] = lua_getPixelFormatName;
	}
};
