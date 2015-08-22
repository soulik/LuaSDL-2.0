#ifndef LUA_SDL_OBJECTS_MUSIC_H
#define LUA_SDL_OBJECTS_MUSIC_H

#include "common.hpp"

namespace LuaSDL {

	class MixMusic : public Object<Mix_Music> {
	public:
		explicit MixMusic(State * state) : Object<Mix_Music>(state) {
			LUTOK_METHOD("play", &MixMusic::play);
			LUTOK_METHOD("fadeIn", &MixMusic::fadeIn);
			LUTOK_PROPERTY("type", &MixMusic::getMusicType, &MixMusic::nullMethod);	
		}

		void destructor(State & state, Mix_Music * music){
			Mix_FreeMusic(music);
		}

		int play(State & state, Mix_Music * music);
		int fadeIn(State & state, Mix_Music * music);
		int getMusicType(State & state, Mix_Music * music);
	};
}

#endif
