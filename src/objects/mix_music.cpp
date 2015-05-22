#include "objects/mix_music.hpp"
#include <lua.hpp>

static int lua_Mix_LoadMUS(State & state){
	LuaSDL::Lua_SDL_MixMusic & m = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_MixMusic);

	Mix_Music * music = Mix_LoadMUS(stack->to<const std::string>(1).c_str());
	if (music){
		m.push(music);
		return 1;
	}else{
		return 0;
	}
}
static int lua_Mix_GetNumMusicDecoders(State & state){
	int count = Mix_GetNumMusicDecoders();
	stack->newTable();
	for (int index=0; index<count; index++){
		stack->setField(index+1, Mix_GetMusicDecoder(index));
	}
	return 1;
}
static int lua_Mix_VolumeMusic(State & state){
	int volume = -1;
	if (stack->is<LUA_TNUMBER>(1)){
		volume = stack->to<int>(1);
	}

	stack->push<int>(Mix_VolumeMusic(volume));
	return 1;
}
static int lua_Mix_PauseMusic(State & state){
	Mix_PauseMusic();
	return 0;
}
static int lua_Mix_ResumeMusic(State & state){
	Mix_ResumeMusic();
	return 0;
}
static int lua_Mix_RewindMusic(State & state){
	Mix_RewindMusic();
	return 0;
}
static int lua_Mix_SetMusicPosition(State & state){
	double position = -1;
	if (stack->is<LUA_TNUMBER>(1)){
		position = state.to_number(1);
		int result = Mix_SetMusicPosition(position);
		stack->push<bool>(result == 0);
		return 1;
	}
	return 0;
}
static int lua_Mix_HaltMusic(State & state){
	Mix_HaltMusic();
	return 0;
}
static int lua_Mix_FadeOutMusic(State & state){
	int ms = 0;
	if (stack->is<LUA_TNUMBER>(1)){
		ms = stack->to<int>(1);
	}
	int result = Mix_FadeOutMusic(ms);
	stack->push<bool>(result == 1);
	return 1;
}
static int lua_Mix_PlayingMusic(State & state){
	int result = Mix_PlayingMusic();
	stack->push<bool>(result == 1);
	return 1;
}
static int lua_Mix_PausedMusic(State & state){
	int result = Mix_PausedMusic();
	stack->push<bool>(result == 1);
	return 1;
}
static int lua_Mix_FadingMusic(State & state){
	Mix_Fading fading = Mix_FadingMusic();
	switch (fading){
	case MIX_NO_FADING:
		stack->push<const std::string>("none");
		break;
	case MIX_FADING_OUT:
		stack->push<const std::string>("out");
		break;
	case MIX_FADING_IN:
		stack->push<const std::string>("in");
		break;
	}
	return 1;
}

void LuaSDL::init_mix_music(State & state, Module & module){
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
