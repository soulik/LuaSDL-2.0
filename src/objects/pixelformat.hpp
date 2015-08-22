#ifndef LUA_SDL_OBJECTS_PIXELFORMAT_H
#define LUA_SDL_OBJECTS_PIXELFORMAT_H

#include "common.hpp"

namespace LuaSDL {

	class PixelFormat : public Object<SDL_PixelFormat> {
	public:
		explicit PixelFormat(State * state) : Object<SDL_PixelFormat>(state) {

			LUTOK_METHOD("getRGB", &PixelFormat::getRGB);
			LUTOK_METHOD("getRGBA", &PixelFormat::getRGBA);
			LUTOK_METHOD("mapRGB", &PixelFormat::mapRGB);
			LUTOK_METHOD("mapRGBA", &PixelFormat::mapRGBA);

			LUTOK_PROPERTY("name", &PixelFormat::getName, &PixelFormat::nullMethod);	
			LUTOK_PROPERTY("format", &PixelFormat::getFormat, &PixelFormat::setFormat);	
			LUTOK_PROPERTY("BitsPerPixel", &PixelFormat::getBitsPerPixel, &PixelFormat::setBitsPerPixel);	
			LUTOK_PROPERTY("BytesPerPixel", &PixelFormat::getBytesPerPixel, &PixelFormat::setBytesPerPixel);	
			LUTOK_PROPERTY("Rmask", &PixelFormat::getRmask, &PixelFormat::setRmask);	
			LUTOK_PROPERTY("Gmask", &PixelFormat::getGmask, &PixelFormat::setGmask);	
			LUTOK_PROPERTY("Bmask", &PixelFormat::getBmask, &PixelFormat::setBmask);	
			LUTOK_PROPERTY("Amask", &PixelFormat::getAmask, &PixelFormat::setAmask);	

			LUTOK_PROPERTY("Rloss", &PixelFormat::getRloss, &PixelFormat::setRloss);	
			LUTOK_PROPERTY("Gloss", &PixelFormat::getGloss, &PixelFormat::setGloss);	
			LUTOK_PROPERTY("Bloss", &PixelFormat::getBloss, &PixelFormat::setBloss);	
			LUTOK_PROPERTY("Aloss", &PixelFormat::getAloss, &PixelFormat::setAloss);	

			LUTOK_PROPERTY("Rshift", &PixelFormat::getRshift, &PixelFormat::setRshift);
			LUTOK_PROPERTY("Gshift", &PixelFormat::getGshift, &PixelFormat::setGshift);
			LUTOK_PROPERTY("Bshift", &PixelFormat::getBshift, &PixelFormat::setBshift);
			LUTOK_PROPERTY("Ashift", &PixelFormat::getAshift, &PixelFormat::setAshift);
		}

		SDL_PixelFormat * constructor(State & state, bool & managed);

		void destructor(State & state, SDL_PixelFormat * pixelformat){
			SDL_FreeFormat(pixelformat);
		}

		int inline mapRGB(State & state, SDL_PixelFormat * format);
		int inline mapRGBA(State & state, SDL_PixelFormat * format);
		int inline getRGB(State & state, SDL_PixelFormat * format);
		int inline getRGBA(State & state, SDL_PixelFormat * format);
		int inline getName(State & state, SDL_PixelFormat * format);
		int inline getFormat(State & state, SDL_PixelFormat * format);
		int inline setFormat(State & state, SDL_PixelFormat * format);
		int inline getBitsPerPixel(State & state, SDL_PixelFormat * format);
		int inline setBitsPerPixel(State & state, SDL_PixelFormat * format);
		int inline getBytesPerPixel(State & state, SDL_PixelFormat * format);
		int inline setBytesPerPixel(State & state, SDL_PixelFormat * format);
		
		int inline getRmask(State & state, SDL_PixelFormat * format);
		int inline setRmask(State & state, SDL_PixelFormat * format);
		int inline getGmask(State & state, SDL_PixelFormat * format);
		int inline setGmask(State & state, SDL_PixelFormat * format);
		int inline getBmask(State & state, SDL_PixelFormat * format);
		int inline setBmask(State & state, SDL_PixelFormat * format);
		int inline getAmask(State & state, SDL_PixelFormat * format);
		int inline setAmask(State & state, SDL_PixelFormat * format);
		int inline getRloss(State & state, SDL_PixelFormat * format);
		int inline setRloss(State & state, SDL_PixelFormat * format);
		int inline getGloss(State & state, SDL_PixelFormat * format);
		int inline setGloss(State & state, SDL_PixelFormat * format);
		int inline getBloss(State & state, SDL_PixelFormat * format);
		int inline setBloss(State & state, SDL_PixelFormat * format);
		int inline getAloss(State & state, SDL_PixelFormat * format);
		int inline setAloss(State & state, SDL_PixelFormat * format);
		int inline getRshift(State & state, SDL_PixelFormat * format);
		int inline setRshift(State & state, SDL_PixelFormat * format);
		int inline getGshift(State & state, SDL_PixelFormat * format);
		int inline setGshift(State & state, SDL_PixelFormat * format);
		int inline getBshift(State & state, SDL_PixelFormat * format);
		int inline setBshift(State & state, SDL_PixelFormat * format);
		int inline getAshift(State & state, SDL_PixelFormat * format);
		int inline setAshift(State & state, SDL_PixelFormat * format);
	};
}

#endif