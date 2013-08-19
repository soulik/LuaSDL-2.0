#ifndef LUA_SDL_OBJECTS_CHUNK_H
#define LUA_SDL_OBJECTS_CHUNK_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_MixChunk : public LObject<Lua_SDL_MixChunk, Mix_Chunk  *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_MixChunk, Mix_Chunk *, "Chunk") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_MixChunk, "play", play);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_MixChunk, "fadeIn", fadeIn);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_MixChunk, Mix_Chunk *, "volume", getVolume, setVolume);	
		}

		void destructor(lutok::state & s, Mix_Chunk * chunk){
			Mix_FreeChunk(chunk);
		}

		int LOBJECT_METHOD(getVolume, Mix_Chunk * chunk){
			state.push_integer(Mix_VolumeChunk(chunk, -1));
			return 1;
		}
		int LOBJECT_METHOD(setVolume, Mix_Chunk * chunk){
			int _volume = state.to_integer(1);
			int volume = ((_volume >= 0) && (_volume <= MIX_MAX_VOLUME)) ? _volume : MIX_MAX_VOLUME;
			Mix_VolumeChunk(chunk, volume);
			return 0;
		}
		int LOBJECT_METHOD(play, Mix_Chunk * chunk){
			int channel = -1;
			int loops = 0;
			int ticks = -1;
			int result = 0;

			if (state.is_number(1)){
				channel = state.to_integer(1);
			}
			if (state.is_number(2)){
				loops = state.to_integer(2);
			}
			if (state.is_number(3)){
				ticks = state.to_integer(3);
				result = Mix_PlayChannelTimed(channel, chunk, loops, ticks);
			}else{
				result = Mix_PlayChannel(channel, chunk, loops);
			}
			
			if (result != -1){
				return 1;
			}else{
				return 0;
			}

		}
		int LOBJECT_METHOD(fadeIn, Mix_Chunk * chunk){
			int channel = -1;
			int loops = 0;
			int ticks = -1;
			int ms = 0;
			int result = 0;

			if (state.is_number(1)){
				channel = state.to_integer(1);
			}
			if (state.is_number(2)){
				loops = state.to_integer(2);
			}
			if (state.is_number(3)){
				ms = state.to_integer(3);
			}
			if (state.is_number(4)){
				ticks = state.to_integer(4);
				result = Mix_FadeInChannelTimed(channel, chunk, loops, ms, ticks);
			}else{
				result = Mix_FadeInChannel(channel, chunk, loops, ms);
			}

			if (result != -1){
				return 1;
			}else{
				return 0;
			}

		}
	};
}

#endif
