#include "objects/pixelformat.hpp"
#include <lua.hpp>

namespace LuaSDL {
	int inline PixelFormat::mapRGB(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(
			SDL_MapRGB(
			format,
			(Uint8)stack->to<int>(1),
			(Uint8)stack->to<int>(2),
			(Uint8)stack->to<int>(3)
			));

		return 1;
	}

	int inline PixelFormat::mapRGBA(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(
			SDL_MapRGBA(
			format,
			(Uint8)stack->to<int>(1),
			(Uint8)stack->to<int>(2),
			(Uint8)stack->to<int>(3),
			(Uint8)stack->to<int>(4)
			));

		return 1;
	}

	int inline PixelFormat::getRGB(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		Uint8 r, g, b;

		SDL_GetRGB(
			stack->to<int>(1),
			format,
			&r, &g, &b);

		stack->push<int>(r);
		stack->push<int>(g);
		stack->push<int>(b);
		return 3;
	}

	int inline PixelFormat::getRGBA(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		Uint8 r, g, b, a;

		SDL_GetRGBA(
			stack->to<int>(1),
			format,
			&r, &g, &b, &a);

		stack->push<int>(r);
		stack->push<int>(g);
		stack->push<int>(b);
		stack->push<int>(a);
		return 4;
	}

	int inline PixelFormat::getName(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<const std::string &>(SDL_GetPixelFormatName(format->format));
		return 1;
	}

	int inline PixelFormat::getFormat(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->format);
		return 1;
	}

	int inline PixelFormat::setFormat(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->format = stack->to<int>(1);
		return 0;
	}
	int inline PixelFormat::getBitsPerPixel(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->BitsPerPixel);
		return 1;
	}

	int inline PixelFormat::setBitsPerPixel(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->BitsPerPixel = (Uint8)stack->to<int>(1);
		return 0;
	}
	int inline PixelFormat::getBytesPerPixel(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->BytesPerPixel);
		return 1;
	}

	int inline PixelFormat::setBytesPerPixel(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->BytesPerPixel = (Uint8)stack->to<int>(1);
		return 0;
	}
	int inline PixelFormat::getRmask(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->Rmask);
		return 1;
	}

	int inline PixelFormat::setRmask(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->Rmask = (Uint32)stack->to<int>(1);
		return 0;
	}
	int inline PixelFormat::getGmask(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->Gmask);
		return 1;
	}

	int inline PixelFormat::setGmask(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->Gmask = (Uint32)stack->to<int>(1);
		return 0;
	}
	int inline PixelFormat::getBmask(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->Bmask);
		return 1;
	}

	int inline PixelFormat::setBmask(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->Bmask = (Uint32)stack->to<int>(1);
		return 0;
	}

	int inline PixelFormat::getAmask(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->Amask);
		return 1;
	}
	int inline PixelFormat::setAmask(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->Amask = (Uint32)stack->to<int>(1);
		return 0;
	}

	int inline PixelFormat::getRloss(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->Rloss);
		return 1;
	}
	int inline PixelFormat::setRloss(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->Rloss = (Uint8)stack->to<int>(1);
		return 0;
	}
	int inline PixelFormat::getGloss(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->Gloss);
		return 1;
	}
	int inline PixelFormat::setGloss(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->Gloss = (Uint8)stack->to<int>(1);
		return 0;
	}
	int inline PixelFormat::getBloss(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->Bloss);
		return 1;
	}
	int inline PixelFormat::setBloss(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->Bloss = (Uint8)stack->to<int>(1);
		return 0;
	}
	int inline PixelFormat::getAloss(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->Aloss);
		return 1;
	}
	int inline PixelFormat::setAloss(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->Aloss = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline PixelFormat::getRshift(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->Rshift);
		return 1;
	}
	int inline PixelFormat::setRshift(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->Rshift = (Uint8)stack->to<int>(1);
		return 0;
	}
	int inline PixelFormat::getGshift(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->Gshift);
		return 1;
	}
	int inline PixelFormat::setGshift(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->Gshift = (Uint8)stack->to<int>(1);
		return 0;
	}
	int inline PixelFormat::getBshift(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->Bshift);
		return 1;
	}
	int inline PixelFormat::setBshift(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->Bshift = (Uint8)stack->to<int>(1);
		return 0;
	}
	int inline PixelFormat::getAshift(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		stack->push<int>(format->Ashift);
		return 1;
	}
	int inline PixelFormat::setAshift(State & state, SDL_PixelFormat * format) {
		Stack * stack = state.stack;
		format->Ashift = (Uint8)stack->to<int>(1);
		return 0;
	}

	SDL_PixelFormat * PixelFormat::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		PixelFormat * interfacePixelFormat = state.getInterface<PixelFormat>("LuaSDL_PixelFormat");
		Uint32 pname;
		if (stack->is<LUA_TNUMBER>(1)){
			pname = (Uint32)stack->to<int>(1);
		}
		else{
			pname = SDL_PIXELFORMAT_UNKNOWN;
		}
		SDL_PixelFormat * pixelformat = SDL_AllocFormat(pname);
		return pixelformat;
	}

	static int lua_SDL_MasksToPixelFormatEnum(State & state){
		Stack * stack = state.stack;
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
		Stack * stack = state.stack;
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
			}
			else{
				stack->push<bool>(false);
				return 1;
			}
		}
		return 0;
	}


	void initPixelFormat(State * state, Module & module){
		INIT_OBJECT(PixelFormat);
		module["masksToPixelFormatEnum"] = lua_SDL_MasksToPixelFormatEnum;
		module["pixelFormatEnumToMasks"] = lua_SDL_PixelFormatEnumToMasks;
	}


};
