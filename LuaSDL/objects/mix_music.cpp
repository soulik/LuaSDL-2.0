#include "objects/mix_music.hpp"
#include <lua.hpp>

static int lua_Mix_LoadMUS(lutok::state& state){
	LuaSDL::Lua_SDL_MixMusic * m = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_MixMusic);

	Mix_Music * music = Mix_LoadMUS(state.to_string(1).c_str());
	if (music){
		m->push(music);
		return 1;
	}else{
		return 0;
	}
}
static int lua_Mix_GetNumMusicDecoders(lutok::state& state){
	int count = Mix_GetNumMusicDecoders();
	state.new_table();
	for (int index=0; index<count; index++){
		state.set_field(index+1, Mix_GetMusicDecoder(index));
	}
	return 1;
}
static int lua_Mix_VolumeMusic(lutok::state& state){
	int volume = -1;
	if (state.is_number(1)){
		volume = state.to_integer(1);
	}

	state.push_integer(Mix_VolumeMusic(volume));
	return 1;
}
static int lua_Mix_PauseMusic(lutok::state& state){
	Mix_PauseMusic();
	return 0;
}
static int lua_Mix_ResumeMusic(lutok::state& state){
	Mix_ResumeMusic();
	return 0;
}
static int lua_Mix_RewindMusic(lutok::state& state){
	Mix_RewindMusic();
	return 0;
}
static int lua_Mix_SetMusicPosition(lutok::state& state){
	double position = -1;
	if (state.is_number(1)){
		position = state.to_number(1);
		int result = Mix_SetMusicPosition(position);
		state.push_boolean(result == 0);
		return 1;
	}
	return 0;
}
static int lua_Mix_HaltMusic(lutok::state& state){
	Mix_HaltMusic();
	return 0;
}
static int lua_Mix_FadeOutMusic(lutok::state& state){
	int ms = 0;
	if (state.is_number(1)){
		ms = state.to_integer(1);
	}
	int result = Mix_FadeOutMusic(ms);
	state.push_boolean(result == 1);
	return 1;
}
static int lua_Mix_PlayingMusic(lutok::state& state){
	int result = Mix_PlayingMusic();
	state.push_boolean(result == 1);
	return 1;
}
static int lua_Mix_PausedMusic(lutok::state& state){
	int result = Mix_PausedMusic();
	state.push_boolean(result == 1);
	return 1;
}
static int lua_Mix_FadingMusic(lutok::state& state){
	Mix_Fading fading = Mix_FadingMusic();
	switch (fading){
	case MIX_NO_FADING:
		state.push_string("none");
		break;
	case MIX_FADING_OUT:
		state.push_string("out");
		break;
	case MIX_FADING_IN:
		state.push_string("in");
		break;
	}
	return 1;
}

void LuaSDL::init_mix_music(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_MixMusic);
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
