#include "objects/mix_chunk.hpp"
#include <lua.hpp>

static int lua_Mix_LoadWAV(lutok::state& state){
	LuaSDL::Lua_SDL_MixChunk * c = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_MixChunk);

	if (state.is_string(1)){
		Mix_Chunk * chunk = Mix_LoadWAV(state.to_string(1).c_str());
		if (chunk){
			c->push(chunk);
			return 1;
		}
	}
	return 0;
}
static int lua_Mix_GetChunkDecoders(lutok::state& state){
	int count = Mix_GetNumChunkDecoders();
	state.new_table();
	for (int index=0; index<count; index++){
		state.set_field(index+1, Mix_GetChunkDecoder(index));
	}
	return 1;
}

void LuaSDL::init_mix_chunk(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_MixChunk);
	module["mixerLoadWAV"] = lua_Mix_LoadWAV;
	module["mixerGetChunkDecoders"] = lua_Mix_GetChunkDecoders;
}
