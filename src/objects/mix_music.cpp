#include "objects/mix_music.hpp"
#include <lua.hpp>

namespace LuaSDL {
	int MixMusic::play(State & state, Mix_Music * music) {
		Stack * stack = state.stack;
		int loops = 0;
		int result = 0;

		if (stack->is<LUA_TNUMBER>(1)){
			loops = stack->to<int>(1);
		}
		result = Mix_PlayMusic(music, loops);
		stack->push<bool>(result != -1);
		return 1;
	}
	int MixMusic::fadeIn(State & state, Mix_Music * music) {
		Stack * stack = state.stack;
		int loops = 0;
		int ms = 0;
		int result = 0;
		double position = 0;

		if (stack->is<LUA_TNUMBER>(1)){
			loops = stack->to<int>(1);
		}
		if (stack->is<LUA_TNUMBER>(2)){
			ms = stack->to<int>(2);
		}
		if (stack->is<LUA_TNUMBER>(3)){
			position = stack->to<LUA_NUMBER>(3);
			result = Mix_FadeInMusicPos(music, loops, ms, position);
		}
		else{
			result = Mix_FadeInMusic(music, loops, ms);
		}

		stack->push<bool>(result != -1);
		return 1;
	}
	int MixMusic::getMusicType(State & state, Mix_Music * music) {
		Stack * stack = state.stack;
		Mix_MusicType type = Mix_GetMusicType(music);
		switch (type){
		case MUS_NONE:
		case MUS_CMD:
			stack->push<const std::string &>("cmd");
			break;
		case MUS_WAV:
			stack->push<const std::string &>("wav");
			break;
		case MUS_MOD:
			stack->push<const std::string &>("mod");
			break;
		case MUS_MID:
			stack->push<const std::string &>("mid");
			break;
		case MUS_OGG:
			stack->push<const std::string &>("ogg");
			break;
		case MUS_MP3:
			stack->push<const std::string &>("mp3");
			break;
		default:
			stack->push<const std::string &>("unknown");
			break;
		}
		return 1;
	}


	static int lua_Mix_LoadMUS(State & state){
		Stack * stack = state.stack;
		MixMusic * interfaceMixMusic = state.getInterface<MixMusic>("LuaSDL_MixMusic");
		if (stack->is<LUA_TSTRING>(1)){
			const std::string fileName = stack->to<const std::string>(1);
			Mix_Music * music = Mix_LoadMUS(fileName.c_str());
			if (music){
				interfaceMixMusic->push(music, true);
				return 1;
			}
		}
		return 0;
	}
	static int lua_Mix_GetNumMusicDecoders(State & state){
		Stack * stack = state.stack;
		int count = Mix_GetNumMusicDecoders();
		stack->newTable();
		for (int index = 0; index < count; index++){
			stack->push<int>(index + 1);
			stack->push<const std::string &>(Mix_GetMusicDecoder(index));
			stack->setTable();
		}
		return 1;
	}
	static int lua_Mix_VolumeMusic(State & state){
		Stack * stack = state.stack;
		int volume = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			volume = stack->to<int>(1);
		}

		stack->push<int>(Mix_VolumeMusic(volume));
		return 1;
	}
	static int lua_Mix_PauseMusic(State & state){
		Stack * stack = state.stack;
		Mix_PauseMusic();
		return 0;
	}
	static int lua_Mix_ResumeMusic(State & state){
		Stack * stack = state.stack;
		Mix_ResumeMusic();
		return 0;
	}
	static int lua_Mix_RewindMusic(State & state){
		Stack * stack = state.stack;
		Mix_RewindMusic();
		return 0;
	}
	static int lua_Mix_SetMusicPosition(State & state){
		Stack * stack = state.stack;
		double position = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			position = stack->to<LUA_NUMBER>(1);
			int result = Mix_SetMusicPosition(position);
			stack->push<bool>(result == 0);
			return 1;
		}
		return 0;
	}
	static int lua_Mix_HaltMusic(State & state){
		Stack * stack = state.stack;
		Mix_HaltMusic();
		return 0;
	}
	static int lua_Mix_FadeOutMusic(State & state){
		Stack * stack = state.stack;
		int ms = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			ms = stack->to<int>(1);
		}
		int result = Mix_FadeOutMusic(ms);
		stack->push<bool>(result == 1);
		return 1;
	}
	static int lua_Mix_PlayingMusic(State & state){
		Stack * stack = state.stack;
		int result = Mix_PlayingMusic();
		stack->push<bool>(result == 1);
		return 1;
	}
	static int lua_Mix_PausedMusic(State & state){
		Stack * stack = state.stack;
		int result = Mix_PausedMusic();
		stack->push<bool>(result == 1);
		return 1;
	}
	static int lua_Mix_FadingMusic(State & state){
		Stack * stack = state.stack;
		Mix_Fading fading = Mix_FadingMusic();
		switch (fading){
		case MIX_NO_FADING:
			stack->push<const std::string &>("none");
			break;
		case MIX_FADING_OUT:
			stack->push<const std::string &>("out");
			break;
		case MIX_FADING_IN:
			stack->push<const std::string &>("in");
			break;
		}
		return 1;
	}

	void initMixMusic(State * state, Module & module){
		INIT_OBJECT(MixMusic);
		
		module["mixerLoadMUS"] = lua_Mix_LoadMUS;
		module["mixerGetMusicDecoders"] = lua_Mix_GetNumMusicDecoders;
		module["mixerVolumeMusic"] = lua_Mix_VolumeMusic;
		module["mixerPauseMusic"] = lua_Mix_PauseMusic;
		module["mixerResumeMusic"] = lua_Mix_ResumeMusic;
		module["mixerRewindMusic"] = lua_Mix_RewindMusic;
		module["mixerSetMusicPosition"] = lua_Mix_SetMusicPosition;
		module["mixerHaltMusic"] = lua_Mix_HaltMusic;
		module["mixerFadeOutMusic"] = lua_Mix_FadeOutMusic;
		module["mixerPlayingMusic"] = lua_Mix_PlayingMusic;
		module["mixerPausedMusic"] = lua_Mix_PausedMusic;
		module["mixerFadingMusic"] = lua_Mix_FadingMusic;
	}

};
