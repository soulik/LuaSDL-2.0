#ifndef LUA_SDL_OBJECTS_AUDIOSPEC_H
#define LUA_SDL_OBJECTS_AUDIOSPEC_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_AudioSpec : public LObject<Lua_SDL_AudioSpec, SDL_AudioSpec *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_AudioSpec, SDL_AudioSpec *, "AudioSpec") {
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioSpec, SDL_AudioSpec *, "freq", getFreq, setFreq);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioSpec, SDL_AudioSpec *, "format", getFormat, setFormat);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioSpec, SDL_AudioSpec *, "channels", getChannels, setChannels);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioSpec, SDL_AudioSpec *, "silence", getSilence, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioSpec, SDL_AudioSpec *, "samples", getSamples, setSamples);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioSpec, SDL_AudioSpec *, "padding", getPadding, setPadding);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioSpec, SDL_AudioSpec *, "size", getSize, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioSpec, SDL_AudioSpec *, "callback", getCallback, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioSpec, SDL_AudioSpec *, "userdata", getUserdata, null_method);	
		}

		void destructor(lutok::state & state, SDL_AudioSpec * audiospec){
			delete audiospec;
		}

		int LOBJECT_METHOD(getFreq, SDL_AudioSpec * audiospec){
			state.push_integer(audiospec->freq);
			return 1;
		}
		int LOBJECT_METHOD(setFreq, SDL_AudioSpec * audiospec){
			audiospec->freq = state.to_integer(1);
			return 0;
		}
		int LOBJECT_METHOD(getFormat, SDL_AudioSpec * audiospec){
			state.push_integer(audiospec->format);
			return 1;
		}
		int LOBJECT_METHOD(setFormat, SDL_AudioSpec * audiospec){
			audiospec->format = static_cast<SDL_AudioFormat>(state.to_integer(1));
			return 0;
		}
		int LOBJECT_METHOD(getChannels, SDL_AudioSpec * audiospec){
			state.push_integer(audiospec->channels);
			return 1;
		}
		int LOBJECT_METHOD(setChannels, SDL_AudioSpec * audiospec){
			audiospec->channels = static_cast<Uint8>(state.to_integer(1));
			return 0;
		}
		int LOBJECT_METHOD(getSilence, SDL_AudioSpec * audiospec){
			state.push_integer(audiospec->silence);
			return 1;
		}
		int LOBJECT_METHOD(getSamples, SDL_AudioSpec * audiospec){
			state.push_integer(audiospec->samples);
			return 1;
		}
		int LOBJECT_METHOD(setSamples, SDL_AudioSpec * audiospec){
			audiospec->samples = static_cast<Uint16>(state.to_integer(1));
			return 0;
		}
		int LOBJECT_METHOD(getPadding, SDL_AudioSpec * audiospec){
			state.push_integer(audiospec->padding);
			return 1;
		}
		int LOBJECT_METHOD(setPadding, SDL_AudioSpec * audiospec){
			audiospec->padding = static_cast<Uint16>(state.to_integer(1));
			return 0;
		}
		int LOBJECT_METHOD(getSize, SDL_AudioSpec * audiospec){
			state.push_integer(audiospec->size);
			return 1;
		}
		int LOBJECT_METHOD(getCallback, SDL_AudioSpec * audiospec){
			return 0;
		}
		int LOBJECT_METHOD(getUserdata, SDL_AudioSpec * audiospec){
			return 0;
		}
	};
}

#endif
