#include "common.hpp"
#include "objects/mix_chunk.hpp"

namespace LuaSDL {

	static int lua_Mixer_Init(State & state){
		Stack * stack = state.stack;
		int result = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			result = Mix_Init(stack->to<int>(1));
		}else{
			result = Mix_Init(0);
		}
		stack->push<int>(result);
		return 1;
	}
	static int lua_Mixer_Quit(State & state){
		Mix_Quit();
		return 0;
	}
	static int lua_Mixer_OpenAudio(State & state){
		Stack * stack = state.stack;
		int frequency = MIX_DEFAULT_FREQUENCY;
		Uint16 format = MIX_DEFAULT_FORMAT;
		int channels  = MIX_DEFAULT_CHANNELS;
		int chunk_size = 1024;

		if (stack->is<LUA_TNUMBER>(1)){
			frequency = stack->to<int>(1);
		}
		if (stack->is<LUA_TNUMBER>(2)){
			format = static_cast<Uint16>(stack->to<int>(2));
		}
		if (stack->is<LUA_TNUMBER>(3)){
			channels  = stack->to<int>(3);
		}
		if (stack->is<LUA_TNUMBER>(4)){
			chunk_size = stack->to<int>(4);
		}
		int result = Mix_OpenAudio(frequency, format, channels, chunk_size);
		stack->push<bool>(result == 0);
		return 1;
	}
	static int lua_Mixer_CloseAudio(State & state){
		Mix_CloseAudio();
		return 0;
	}
	static int lua_Mix_GetError(State & state){
		Stack * stack = state.stack;
		stack->push<const std::string>(Mix_GetError());
		return 1;
	}
	static int lua_Mix_QuerySpec(State & state){
		Stack * stack = state.stack;
		int frequency;
		Uint16 format;
		int channels;

		int result = Mix_QuerySpec(&frequency, &format, &channels);
		if (result>0){
			stack->push<int>(result);
			stack->push<int>(frequency);
			stack->push<int>(format);
			stack->push<int>(channels);
			return 4;
		}else{
			stack->push<bool>(false);
			return 1;
		}
	}
	static int lua_Mix_AllocateChannels(State & state){
		Stack * stack = state.stack;
		int channels = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			channels = stack->to<int>(1);
		}
		stack->push<int>(Mix_AllocateChannels(channels));
		return 1;
	}
	static int lua_Mix_Volume(State & state){
		Stack * stack = state.stack;
		int channel = -1;
		int volume = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		if (stack->is<LUA_TNUMBER>(2)){
			volume = stack->to<int>(2);
		}

		stack->push<int>(Mix_Volume(channel, volume));
		return 1;
	}
	static int lua_Mix_Pause(State & state){
		Stack * stack = state.stack;
		int channel = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		Mix_Pause(channel);
		return 0;
	}
	static int lua_Mix_Resume(State & state){
		Stack * stack = state.stack;
		int channel = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		Mix_Resume(channel);
		return 0;
	}
	static int lua_Mix_Halt(State & state){
		Stack * stack = state.stack;
		int channel = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		Mix_HaltChannel(channel);
		return 0;
	}
	static int lua_Mix_ExpireChannel(State & state){
		Stack * stack = state.stack;
		int channel = -1;
		int ms = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		if (stack->is<LUA_TNUMBER>(2)){
			ms = stack->to<int>(2);
		}
		stack->push<int>(Mix_ExpireChannel(channel, ms));
		return 1;
	}
	static int lua_Mix_FadeOutChannel(State & state){
		Stack * stack = state.stack;
		int channel = -1;
		int ms = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		if (stack->is<LUA_TNUMBER>(2)){
			ms = stack->to<int>(2);
		}
		stack->push<int>(Mix_FadeOutChannel(channel, ms));
		return 1;
	}
	static int lua_Mix_ChannelPlaying(State & state){
		Stack * stack = state.stack;
		int channel = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		int result = Mix_Playing(channel);
		if (channel != -1){
			stack->push<bool>(result == 1);
		}else{
			stack->push<int>(result);
		}

		return 1;
	}
	static int lua_Mix_ChannelPaused(State & state){
		Stack * stack = state.stack;
		int channel = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		int result = Mix_Playing(channel);
		if (channel != -1){
			stack->push<bool>(result == 1);
		}else{
			stack->push<int>(result);
		}

		return 1;
	}
	static int lua_Mix_FadingChannel(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			int channel = stack->to<int>(1);
			Mix_Fading fading = Mix_FadingChannel(channel);
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
		return 0;
	}
	static int lua_Mix_ReserveChannels(State & state){
		Stack * stack = state.stack;
		int channels = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			channels = stack->to<int>(1);
		}
		stack->push<int>(Mix_ReserveChannels(channels));
		return 1;
	}
	static int lua_Mix_GroupChannel(State & state){
		Stack * stack = state.stack;
		int channel = 0;
		int tag = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
			if (stack->is<LUA_TNUMBER>(2)){
				tag = stack->to<int>(2);
			}
			int result = Mix_GroupChannel(channel, tag);
			stack->push<int>(result == 1);
			return 1;
		}
		return 0;
	}
	static int lua_Mix_GroupChannels(State & state){
		Stack * stack = state.stack;
		int from = 0;
		int to = 0;
		int tag = -1;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2)){
			from = stack->to<int>(1);
			to = stack->to<int>(2);
			if (from <= to){
				if (stack->is<LUA_TNUMBER>(3)){
					tag = stack->to<int>(3);
				}
				int result = Mix_GroupChannels(from, to, tag);
				stack->push<int>(result);
				return 1;
			}
		}
		return 0;
	}
	static int lua_Mix_GroupCount(State & state){
		Stack * stack = state.stack;
		int tag = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			tag = stack->to<int>(1);
		}
		int result = Mix_GroupCount(tag);
		if (result >= 0){
			stack->push<int>(result);
		}else{
			stack->push<bool>(false);
		}
		return 1;
	}
	static int lua_Mix_GroupAvailable(State & state){
		Stack * stack = state.stack;
		int tag = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			tag = stack->to<int>(1);
		}
		int result = Mix_GroupAvailable(tag);
		if (result >= 0){
			stack->push<int>(result);
		}else{
			stack->push<bool>(false);
		}
		return 1;
	}
	static int lua_Mix_GroupOldest(State & state){
		Stack * stack = state.stack;
		int tag = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			tag = stack->to<int>(1);
		}
		int result = Mix_GroupOldest(tag);
		if (result >= 0){
			stack->push<int>(result);
		}else{
			stack->push<bool>(false);
		}
		return 1;
	}
	static int lua_Mix_GroupNewer(State & state){
		Stack * stack = state.stack;
		int tag = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			tag = stack->to<int>(1);
		}
		int result = Mix_GroupNewer(tag);
		if (result >= 0){
			stack->push<int>(result);
		}else{
			stack->push<bool>(false);
		}
		return 1;
	}
	static int lua_Mix_FadeOutGroup(State & state){
		Stack * stack = state.stack;
		int tag = -1;
		int ms = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			tag = stack->to<int>(1);
		}
		if (stack->is<LUA_TNUMBER>(2)){
			ms = stack->to<int>(2);
		}
		stack->push<int>(Mix_FadeOutGroup(tag, ms));
		return 1;
	}
	static int lua_Mix_HaltGroup(State & state){
		Stack * stack = state.stack;
		int tag = -1;
		if (stack->is<LUA_TNUMBER>(1)){
			tag = stack->to<int>(1);
		}
		Mix_HaltGroup(tag);
		return 0;
	}
	static int lua_Mix_SetPanning(State & state){
		Stack * stack = state.stack;
		int channel = MIX_CHANNEL_POST;
		Uint8 left = 255;
		Uint8 right = 255;

		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		if (stack->is<LUA_TNUMBER>(2)){
			left = static_cast<Uint8>(stack->to<int>(2));
		}
		if (stack->is<LUA_TNUMBER>(3)){
			right = static_cast<Uint8>(stack->to<int>(3));
		}
		int result = Mix_SetPanning(channel, left, right);
		stack->push<bool>(result != 0);
		return 1;
	}
	static int lua_Mix_SetDistance(State & state){
		Stack * stack = state.stack;
		int channel = MIX_CHANNEL_POST;
		Uint8 distance = 0;

		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		if (stack->is<LUA_TNUMBER>(2)){
			distance = static_cast<Uint8>(stack->to<int>(2));
		}
		int result = Mix_SetDistance(channel, distance);
		stack->push<bool>(result != 0);
		return 1;
	}
	static int lua_Mix_SetPosition(State & state){
		Stack * stack = state.stack;
		int channel = MIX_CHANNEL_POST;
		Sint16 angle = 0;
		Uint8 distance = 0;

		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		if (stack->is<LUA_TNUMBER>(2)){
			angle = static_cast<Uint16>(stack->to<int>(2));
		}
		if (stack->is<LUA_TNUMBER>(3)){
			distance = static_cast<Uint8>(stack->to<int>(3));
		}
		int result = Mix_SetPosition(channel, angle, distance);
		stack->push<bool>(result != 0);
		return 1;
	}
	static int lua_Mix_SetReverseStereo(State & state){
		Stack * stack = state.stack;
		int channel = MIX_CHANNEL_POST;
		int flip = 0;

		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		if (stack->is<LUA_TNUMBER>(2) || stack->is<LUA_TBOOLEAN>(2)){
			flip = stack->to<int>(2);
		}
		int result = Mix_SetReverseStereo(channel, flip);
		stack->push<bool>(result != 0);
		return 1;
	}
	static int lua_Mix_UnregisterAllEffects(State & state){
		Stack * stack = state.stack;
		int channel = MIX_CHANNEL_POST;	
		if (stack->is<LUA_TNUMBER>(1)){
			channel = stack->to<int>(1);
		}
		int result = Mix_UnregisterAllEffects(channel);
		stack->push<bool>(result != 0);
		return 1;
	}

	void init_sdl_mixer(Module & module){
		module["mixerInit"] = lua_Mixer_Init;
		module["mixerQuit"] = lua_Mixer_Quit;
		module["mixerOpenAudio"] = lua_Mixer_OpenAudio;
		module["mixerCloseAudio"] = lua_Mixer_CloseAudio;
		module["mixerGetError"] = lua_Mix_GetError;
		module["mixerQuerySpec"] = lua_Mix_QuerySpec;

		//channels
		module["mixerAllocateChannels"] = lua_Mix_AllocateChannels;
		module["mixerVolume"] = lua_Mix_Volume;
		module["mixerPause"] = lua_Mix_Pause;
		module["mixerResume"] = lua_Mix_Resume;
		module["mixerHaltChannel"] = lua_Mix_Halt;
		module["mixerExpireChannel"] = lua_Mix_ExpireChannel;
		module["mixerFadeOutChannel"] = lua_Mix_FadeOutChannel;
		module["mixerChannelPlaying"] = lua_Mix_ChannelPlaying;
		module["mixerChannelPaused"] = lua_Mix_ChannelPaused;
		module["mixerFadingChannel"] = lua_Mix_FadingChannel;

		//groups
		module["mixerReserveChannels"] = lua_Mix_ReserveChannels;
		module["mixerGroupChannel"] = lua_Mix_GroupChannel;
		module["mixerGroupChannels"] = lua_Mix_GroupChannels;
		module["mixerGroupCount"] = lua_Mix_GroupCount;
		module["mixerGroupAvailable"] = lua_Mix_GroupAvailable;
		module["mixerGroupOldest"] = lua_Mix_GroupOldest;
		module["mixerGroupNewer"] = lua_Mix_GroupNewer;
		module["mixerFadeOutGroup"] = lua_Mix_FadeOutGroup;
		module["mixerHaltGroup"] = lua_Mix_HaltGroup;

		//effects
		module["mixerSetPanning"] = lua_Mix_SetPanning;
		module["mixerSetDistance"] = lua_Mix_SetDistance;
		module["mixerSetPosition"] = lua_Mix_SetPosition;
		module["mixerSetReverseStereo"] = lua_Mix_SetReverseStereo;
		module["mixerUnregisterAllEffects"] = lua_Mix_UnregisterAllEffects;

		

	}
}