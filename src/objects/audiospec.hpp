#ifndef LUA_SDL_OBJECTS_AUDIOSPEC_H
#define LUA_SDL_OBJECTS_AUDIOSPEC_H

#include "common.hpp"

namespace LuaSDL {

	class AudioSpec : public Object<SDL_AudioSpec> {
	public:
		explicit AudioSpec(State * state) : Object<SDL_AudioSpec>(state) {
			LUTOK_PROPERTY("freq", &AudioSpec::getFreq, &AudioSpec::setFreq);	
			LUTOK_PROPERTY("format", &AudioSpec::getFormat, &AudioSpec::setFormat);	
			LUTOK_PROPERTY("channels", &AudioSpec::getChannels, &AudioSpec::setChannels);	
			LUTOK_PROPERTY("silence", &AudioSpec::getSilence, &AudioSpec::nullMethod);	
			LUTOK_PROPERTY("samples", &AudioSpec::getSamples, &AudioSpec::setSamples);	
			LUTOK_PROPERTY("padding", &AudioSpec::getPadding, &AudioSpec::setPadding);	
			LUTOK_PROPERTY("size", &AudioSpec::getSize, &AudioSpec::nullMethod);	
			LUTOK_PROPERTY("callback", &AudioSpec::getCallback, &AudioSpec::setCallback);	
			LUTOK_PROPERTY("userdata", &AudioSpec::getUserdata, &AudioSpec::setUserdata);	
		}

		SDL_AudioSpec * constructor(State & state, bool & managed);

		void destructor(State & state, SDL_AudioSpec * audiospec);

		int getFreq(State & state, SDL_AudioSpec * audiospec);
		int setFreq(State & state, SDL_AudioSpec * audiospec);
		int getFormat(State & state, SDL_AudioSpec * audiospec);
		int setFormat(State & state, SDL_AudioSpec * audiospec);
		int getChannels(State & state, SDL_AudioSpec * audiospec);
		int setChannels(State & state, SDL_AudioSpec * audiospec);
		int getSilence(State & state, SDL_AudioSpec * audiospec);
		int getSamples(State & state, SDL_AudioSpec * audiospec);
		int setSamples(State & state, SDL_AudioSpec * audiospec);
		int getPadding(State & state, SDL_AudioSpec * audiospec);
		int setPadding(State & state, SDL_AudioSpec * audiospec);
		int getSize(State & state, SDL_AudioSpec * audiospec);
		int getCallback(State & state, SDL_AudioSpec * audiospec);
		int setCallback(State & state, SDL_AudioSpec * audiospec);
		int getUserdata(State & state, SDL_AudioSpec * audiospec);
		int setUserdata(State & state, SDL_AudioSpec * audiospec);

		static void audioCallback(void *userdata, Uint8 * stream, int len);
		void freeCallbackData(State & state, SDL_AudioSpec * audiospec);
	};
}

#endif
