#include "objects/audiospec.hpp"
#include "objects/audiodevice.hpp"
#include <lua.hpp>

static int lua_SDL_OpenAudioDevice(lutok::state& state){
	LuaSDL::Lua_SDL_AudioSpec * as = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_AudioSpec);
	SDL_AudioSpec * inSpec = as->check(3);
	SDL_AudioSpec * outSpec = new SDL_AudioSpec;
	int allowedChanges = SDL_AUDIO_ALLOW_ANY_CHANGE;
	if (state.is_number(4)){
		allowedChanges = state.to_integer(4);
	}
	
	SDL_AudioDeviceID id = SDL_OpenAudioDevice(
			state.to_string(1).c_str(),
			(state.to_boolean(2)) ? 1 : 0,
			inSpec,
			outSpec,
			allowedChanges
		);
	if (id >= 2){
		LuaSDL::Lua_SDL_AudioDevice * ad = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_AudioDevice);
		LuaSDL::AudioDevice_Data * adata = new LuaSDL::AudioDevice_Data;
		adata->id = id;
		adata->audioSpec = outSpec;

		ad->push(adata);
		return 1;
	}else{
		delete outSpec;
		return 0;
	}
}

void LuaSDL::init_audiodevice(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_AudioDevice);
	module["openAudioDevice"] = lua_SDL_OpenAudioDevice;
}
