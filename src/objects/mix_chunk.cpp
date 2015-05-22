#include "objects/mix_chunk.hpp"
#include <lua.hpp>

static int lua_Mix_LoadWAV(State & state){
	LuaSDL::Lua_SDL_MixChunk & c = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_MixChunk);

	if (stack->is<LUA_TSTRING>(1)){
		Mix_Chunk * chunk = Mix_LoadWAV(stack->to<const std::string>(1).c_str());
		if (chunk){
			c.push(chunk);
			return 1;
		}
	}
	return 0;
}
static int lua_Mix_GetChunkDecoders(State & state){
	int count = Mix_GetNumChunkDecoders();
	stack->newTable();
	for (int index=0; index<count; index++){
		stack->setField(index+1, Mix_GetChunkDecoder(index));
	}
	return 1;
}

void LuaSDL::init_mix_chunk(State & state, Module & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_MixChunk);
	module["mixerLoadWAV"] = lua_Mix_LoadWAV;
	module["mixerGetChunkDecoders"] = lua_Mix_GetChunkDecoders;
}
