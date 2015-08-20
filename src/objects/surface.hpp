#ifndef LUA_SDL_OBJECTS_SURFACE_H
#define LUA_SDL_OBJECTS_SURFACE_H

#include "common.hpp"

namespace LuaSDL {

	class Surface : public Object<SDL_Surface> {
	public:
		explicit Surface(State * state) : Object<SDL_Surface>(state){
			LUTOK_METHOD("createSoftwareRenderer", &Surface::createSoftwareRenderer);

			LUTOK_METHOD("blit", &Surface::createSoftwareRenderer);
			LUTOK_METHOD("lowerBlit", &Surface::lowerBlit);
			LUTOK_METHOD("upperBlit", &Surface::upperBlit);
			LUTOK_METHOD("softStretch", &Surface::softStretch);
			LUTOK_METHOD("convert", &Surface::convert);
			LUTOK_METHOD("convertFormat", &Surface::convertFormat);
			LUTOK_METHOD("fillRect", &Surface::fillRect);
			LUTOK_METHOD("lock", &Surface::lock);
			LUTOK_METHOD("unlock", &Surface::unlock);
			LUTOK_METHOD("createColorCursor", &Surface::createColorCursor);
			LUTOK_METHOD("rawPixels", &Surface::getRawPixels);
			LUTOK_METHOD("setRawPixels8", &Surface::setRawPixels8);
			LUTOK_METHOD("setRawPixels32", &Surface::setRawPixels32);

			LUTOK_PROPERTY("format", &Surface::getFormat, &Surface::nullMethod);
			LUTOK_PROPERTY("w", &Surface::getW, &Surface::nullMethod);
			LUTOK_PROPERTY("h", &Surface::getH, &Surface::nullMethod);
			LUTOK_PROPERTY("pitch", &Surface::getPitch, &Surface::nullMethod);
			LUTOK_PROPERTY("clipRect", &Surface::getClipRect, &Surface::setClipRect);
			LUTOK_PROPERTY("refcount", &Surface::getRefCount, &Surface::setRefCount);
			LUTOK_PROPERTY("pixels", &Surface::getPixels, &Surface::setPixels);

			LUTOK_PROPERTY("colorKey", &Surface::getColorKey, &Surface::setColorKey);
			LUTOK_PROPERTY("alphaMod", &Surface::getAlphaMod, &Surface::setAlphaMod);
			LUTOK_PROPERTY("blendMode", &Surface::getBlendMode, &Surface::setBlendMode);
			LUTOK_PROPERTY("colorMod", &Surface::getColorMod, &Surface::setColorMod);

			LUTOK_PROPERTY("RLE", &Surface::nullMethod, &Surface::setRLE);
		}

		SDL_Surface * constructor(State & state, bool & managed);
		void destructor(State & state, SDL_Surface * surface);

		int createSoftwareRenderer(State & state, SDL_Surface  * surface);

		int blit(State & state, SDL_Surface  * surface);
		int lowerBlit(State & state, SDL_Surface  * surface);
		int upperBlit(State & state, SDL_Surface  * surface);
		int softStretch(State & state, SDL_Surface  * surface);
		int convert(State & state, SDL_Surface  * surface);

		int convertFormat(State & state, SDL_Surface  * surface);

		int getRawPixels(State & state, SDL_Surface  * surface);
		int setRawPixels8(State & state, SDL_Surface  * surface);
		int setRawPixels32(State & state, SDL_Surface  * surface);
		int fillRect(State & state, SDL_Surface  * surface);
		int getClipRect(State & state, SDL_Surface  * surface);
		int setClipRect(State & state, SDL_Surface  * surface);
		int getFormat(State & state, SDL_Surface  * surface);
		int setFormat(State & state, SDL_Surface  * surface);

		int inline lock(State & state, SDL_Surface  * surface);
		int inline unlock(State & state, SDL_Surface  * surface);

		int createColorCursor(State & state, SDL_Surface  * surface);

		int inline getW(State & state, SDL_Surface  * surface);
		int inline getH(State & state, SDL_Surface  * surface);
		int inline getPitch(State & state, SDL_Surface  * surface);
		int inline getPixels(State & state, SDL_Surface  * surface);
		int inline setPixels(State & state, SDL_Surface  * surface);
		int inline getRefCount(State & state, SDL_Surface  * surface);
		int inline setRefCount(State & state, SDL_Surface  * surface);
		int inline getColorKey(State & state, SDL_Surface  * surface);
		int inline setColorKey(State & state, SDL_Surface  * surface);
		int inline getAlphaMod(State & state, SDL_Surface  * surface);
		int inline setAlphaMod(State & state, SDL_Surface  * surface);
		int inline getBlendMode(State & state, SDL_Surface  * surface);
		int inline setBlendMode(State & state, SDL_Surface  * surface);
		int inline getColorMod(State & state, SDL_Surface  * surface);
		int inline setColorMod(State & state, SDL_Surface  * surface);

		int inline setRLE(State & state, SDL_Surface  * surface);
	};
}

#endif