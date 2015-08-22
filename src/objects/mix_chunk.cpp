#include "objects/mix_chunk.hpp"
#include <lua.hpp>

namespace LuaSDL {
	int MixChunk::getVolume(State & state, Mix_Chunk * chunk) {
		Stack * stack = state.stack;
		stack->push<int>(Mix_VolumeChunk(chunk, -1));
		return 1;
	}
	int MixChunk::setVolume(State & state, Mix_Chunk * chunk) {
		Stack * stack = state.stack;
		int _volume = stack->to<int>(1);
		int volume = ((_volume >= 0) && (_volume <= MIX_MAX_VOLUME)) ? _volume : MIX_MAX_VOLUME;
		Mix_VolumeChunk(chunk, volume);
		return 0;
	}
	int MixChunk::play(State & state, Mix_Chunk * chunk) {
		Stack * stack = state.stack;
		int channel = -1;
		int loops = 0;
		int ticks = -1;
		int result = 0;

		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		if (stack->is<LUA_TNUMBER>(2)){
			loops = stack->to<int>(2);
		}
		if (stack->is<LUA_TNUMBER>(3)){
			ticks = stack->to<int>(3);
			result = Mix_PlayChannelTimed(channel, chunk, loops, ticks);
		}
		else{
			result = Mix_PlayChannel(channel, chunk, loops);
		}

		if (result != -1){
			return 1;
		}
		else{
			return 0;
		}

	}
	int MixChunk::fadeIn(State & state, Mix_Chunk * chunk) {
		Stack * stack = state.stack;
		int channel = -1;
		int loops = 0;
		int ticks = -1;
		int ms = 0;
		int result = 0;

		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		if (stack->is<LUA_TNUMBER>(2)){
			loops = stack->to<int>(2);
		}
		if (stack->is<LUA_TNUMBER>(3)){
			ms = stack->to<int>(3);
		}
		if (stack->is<LUA_TNUMBER>(4)){
			ticks = stack->to<int>(4);
			result = Mix_FadeInChannelTimed(channel, chunk, loops, ms, ticks);
		}
		else{
			result = Mix_FadeInChannel(channel, chunk, loops, ms);
		}

		if (result != -1){
			return 1;
		}
		else{
			return 0;
		}

	}

	static int lua_Mix_LoadWAV(State & state){
		Stack * stack = state.stack;
		MixChunk * interfaceMixChunk = state.getInterface<MixChunk>("LuaSDL_MixChunk");

		if (stack->is<LUA_TSTRING>(1)){
			const std::string fileName = stack->to<const std::string>(1);
			Mix_Chunk * chunk = Mix_LoadWAV(fileName.c_str());
			if (chunk){
				interfaceMixChunk->push(chunk, true);
				return 1;
			}
		}
		return 0;
	}
	static int lua_Mix_GetChunkDecoders(State & state){
		Stack * stack = state.stack;
		int count = Mix_GetNumChunkDecoders();
		stack->newTable();
		for (int index = 0; index < count; index++){
			stack->push<int>(index+1);
			stack->push<const std::string &>(Mix_GetChunkDecoder(index));
			stack->setTable();
		}
		return 1;
	}

	void initMixChunk(State * state, Module & module){
		INIT_OBJECT(MixChunk);
		module["mixerLoadWAV"] = lua_Mix_LoadWAV;
		module["mixerGetChunkDecoders"] = lua_Mix_GetChunkDecoders;
	}

};
