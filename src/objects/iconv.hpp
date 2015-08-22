#ifndef LUA_SDL_OBJECTS_ICONV_H
#define LUA_SDL_OBJECTS_ICONV_H

#include "common.hpp"

namespace LuaSDL {

	class Iconv : public Object<SDL_iconv_t> {
	public:
		explicit Iconv(State * state) : Object<SDL_iconv_t>(state){
			LUTOK_METHOD("convert", &Iconv::convert);
		}

		SDL_iconv_t * constructor(State & state, bool & managed);
		void destructor(State & state, SDL_iconv_t * iconv){
			SDL_iconv_close(*iconv);
			delete iconv;
		}

		int convert(State & state, SDL_iconv_t * iconv);
	};
}

#endif