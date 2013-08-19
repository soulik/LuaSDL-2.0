#ifndef LUA_SDL_OBJECTS_MUSIC_H
#define LUA_SDL_OBJECTS_MUSIC_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_MixMusic : public LObject<Lua_SDL_MixMusic, Mix_Music  *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_MixMusic, Mix_Music *, "Music") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_MixMusic, "play", play);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_MixMusic, "fadeIn", fadeIn);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_MixMusic, Mix_Music *, "type", getMusicType, null_method);	
		}

		void destructor(lutok::state & s, Mix_Music * music){
			Mix_FreeMusic(music);
		}

		int LOBJECT_METHOD(play, Mix_Music * music){
			int loops = 0;
			int result = 0;

			if (state.is_number(1)){
				loops = state.to_integer(1);
			}
			result = Mix_PlayMusic(music, loops);
			state.push_boolean(result != -1);
			return 1;
		}
		int LOBJECT_METHOD(fadeIn, Mix_Music * music){
			int loops = 0;
			int ms = 0;
			int result = 0;
			double position = 0;

			if (state.is_number(1)){
				loops = state.to_integer(1);
			}
			if (state.is_number(2)){
				ms = state.to_integer(2);
			}
			if (state.is_number(3)){
				position = state.to_number(3);
				result = Mix_FadeInMusicPos(music, loops, ms, position);
			}else{
				result = Mix_FadeInMusic(music, loops, ms);
			}

			state.push_boolean(result != -1);
			return 1;
		}
		int LOBJECT_METHOD(getMusicType, Mix_Music * music){
			Mix_MusicType type = Mix_GetMusicType(music);
			switch (type){
			case MUS_NONE:
			case MUS_CMD:
				state.push_literal("cmd");
				break;
			case MUS_WAV:
				state.push_literal("wav");
				break;
			case MUS_MOD:
				state.push_literal("mod");
				break;
			case MUS_MID:
				state.push_literal("mid");
				break;
			case MUS_OGG:
				state.push_literal("ogg");
				break;
			case MUS_MP3:
				state.push_literal("mp3");
				break;
			default:
				state.push_literal("unknown");
				break;
			}
			return 1;
		}
	};
}

#endif
