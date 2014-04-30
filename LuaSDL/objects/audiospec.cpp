#include "objects/audiospec.hpp"
#include <lua.hpp>

static int lua_AudioSpec(lutok::state& state){
	LuaSDL::Lua_SDL_AudioSpec & as = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_AudioSpec);
	
	SDL_AudioSpec * audiospec = new SDL_AudioSpec;

	audiospec->freq = 0;
	audiospec->format = 0;
	audiospec->channels = 0;
	audiospec->silence = 0;
	audiospec->samples = 0;
	audiospec->padding = 0;
	audiospec->size = 0;
	audiospec->callback = nullptr;
	audiospec->userdata = nullptr;

	as.push(audiospec);
	return 1;
}

void LuaSDL::init_audiospec(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_AudioSpec);
	module["AudioSpec"] = lua_AudioSpec;
}
