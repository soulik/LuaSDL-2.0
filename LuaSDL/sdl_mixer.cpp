#include "common.hpp"
#include "objects/mix_chunk.hpp"

namespace LuaSDL {

	static int lua_Mixer_Init(lutok::state& state){
		int result = 0;
		if (state.is_number(1)){
			result = Mix_Init(state.to_integer(1));
		}else{
			result = Mix_Init(0);
		}
		state.push_integer(result);
		return 1;
	}
	static int lua_Mixer_Quit(lutok::state& state){
		Mix_Quit();
		return 0;
	}
	static int lua_Mixer_OpenAudio(lutok::state& state){
		int frequency = MIX_DEFAULT_FREQUENCY;
		Uint16 format = MIX_DEFAULT_FORMAT;
		int channels  = MIX_DEFAULT_CHANNELS;
		int chunk_size = 1024;

		if (state.is_number(1)){
			frequency = state.to_integer(1);
		}
		if (state.is_number(2)){
			format = static_cast<Uint16>(state.to_integer(2));
		}
		if (state.is_number(3)){
			channels  = state.to_integer(3);
		}
		if (state.is_number(4)){
			chunk_size = state.to_integer(4);
		}
		int result = Mix_OpenAudio(frequency, format, channels, chunk_size);
		state.push_boolean(result == 0);
		return 1;
	}
	static int lua_Mixer_CloseAudio(lutok::state& state){
		Mix_CloseAudio();
		return 0;
	}
	static int lua_Mix_GetError(lutok::state& state){
		state.push_string(Mix_GetError());
		return 1;
	}
	static int lua_Mix_QuerySpec(lutok::state& state){
		int frequency;
		Uint16 format;
		int channels;

		int result = Mix_QuerySpec(&frequency, &format, &channels);
		if (result>0){
			state.push_integer(result);
			state.push_integer(frequency);
			state.push_integer(format);
			state.push_integer(channels);
			return 4;
		}else{
			state.push_boolean(false);
			return 1;
		}
	}
	static int lua_Mix_AllocateChannels(lutok::state& state){
		int channels = -1;
		if (state.is_number(1)){
			channels = state.to_integer(1);
		}
		state.push_integer(Mix_AllocateChannels(channels));
		return 1;
	}
	static int lua_Mix_Volume(lutok::state& state){
		int channel = -1;
		int volume = -1;
		if (state.is_number(1)){
			channel = state.to_integer(1);
		}
		if (state.is_number(2)){
			volume = state.to_integer(2);
		}

		state.push_integer(Mix_Volume(channel, volume));
		return 1;
	}
	static int lua_Mix_Pause(lutok::state& state){
		int channel = -1;
		if (state.is_number(1)){
			channel = state.to_integer(1);
		}
		Mix_Pause(channel);
		return 0;
	}
	static int lua_Mix_Resume(lutok::state& state){
		int channel = -1;
		if (state.is_number(1)){
			channel = state.to_integer(1);
		}
		Mix_Resume(channel);
		return 0;
	}
	static int lua_Mix_Halt(lutok::state& state){
		int channel = -1;
		if (state.is_number(1)){
			channel = state.to_integer(1);
		}
		Mix_HaltChannel(channel);
		return 0;
	}
	static int lua_Mix_ExpireChannel(lutok::state& state){
		int channel = -1;
		int ms = 0;
		if (state.is_number(1)){
			channel = state.to_integer(1);
		}
		if (state.is_number(2)){
			ms = state.to_integer(2);
		}
		state.push_integer(Mix_ExpireChannel(channel, ms));
		return 1;
	}
	static int lua_Mix_FadeOutChannel(lutok::state& state){
		int channel = -1;
		int ms = 0;
		if (state.is_number(1)){
			channel = state.to_integer(1);
		}
		if (state.is_number(2)){
			ms = state.to_integer(2);
		}
		state.push_integer(Mix_FadeOutChannel(channel, ms));
		return 1;
	}
	static int lua_Mix_ChannelPlaying(lutok::state& state){
		int channel = -1;
		if (state.is_number(1)){
			channel = state.to_integer(1);
		}
		int result = Mix_Playing(channel);
		if (channel != -1){
			state.push_boolean(result == 1);
		}else{
			state.push_integer(result);
		}

		return 1;
	}
	static int lua_Mix_ChannelPaused(lutok::state& state){
		int channel = -1;
		if (state.is_number(1)){
			channel = state.to_integer(1);
		}
		int result = Mix_Playing(channel);
		if (channel != -1){
			state.push_boolean(result == 1);
		}else{
			state.push_integer(result);
		}

		return 1;
	}
	static int lua_Mix_FadingChannel(lutok::state& state){
		if (state.is_number(1)){
			int channel = state.to_integer(1);
			Mix_Fading fading = Mix_FadingChannel(channel);
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
		return 0;
	}
	static int lua_Mix_ReserveChannels(lutok::state& state){
		int channels = 0;
		if (state.is_number(1)){
			channels = state.to_integer(1);
		}
		state.push_integer(Mix_ReserveChannels(channels));
		return 1;
	}
	static int lua_Mix_GroupChannel(lutok::state& state){
		int channel = 0;
		int tag = -1;
		if (state.is_number(1)){
			channel = state.to_integer(1);
			if (state.is_number(2)){
				tag = state.to_integer(2);
			}
			int result = Mix_GroupChannel(channel, tag);
			state.push_integer(result == 1);
			return 1;
		}
		return 0;
	}
	static int lua_Mix_GroupChannels(lutok::state& state){
		int from = 0;
		int to = 0;
		int tag = -1;
		if (state.is_number(1) && state.is_number(2)){
			from = state.to_integer(1);
			to = state.to_integer(2);
			if (from <= to){
				if (state.is_number(3)){
					tag = state.to_integer(3);
				}
				int result = Mix_GroupChannels(from, to, tag);
				state.push_integer(result);
				return 1;
			}
		}
		return 0;
	}
	static int lua_Mix_GroupCount(lutok::state& state){
		int tag = -1;
		if (state.is_number(1)){
			tag = state.to_integer(1);
		}
		int result = Mix_GroupCount(tag);
		if (result >= 0){
			state.push_integer(result);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	static int lua_Mix_GroupAvailable(lutok::state& state){
		int tag = -1;
		if (state.is_number(1)){
			tag = state.to_integer(1);
		}
		int result = Mix_GroupAvailable(tag);
		if (result >= 0){
			state.push_integer(result);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	static int lua_Mix_GroupOldest(lutok::state& state){
		int tag = -1;
		if (state.is_number(1)){
			tag = state.to_integer(1);
		}
		int result = Mix_GroupOldest(tag);
		if (result >= 0){
			state.push_integer(result);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	static int lua_Mix_GroupNewer(lutok::state& state){
		int tag = -1;
		if (state.is_number(1)){
			tag = state.to_integer(1);
		}
		int result = Mix_GroupNewer(tag);
		if (result >= 0){
			state.push_integer(result);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	static int lua_Mix_FadeOutGroup(lutok::state& state){
		int tag = -1;
		int ms = 0;
		if (state.is_number(1)){
			tag = state.to_integer(1);
		}
		if (state.is_number(2)){
			ms = state.to_integer(2);
		}
		state.push_integer(Mix_FadeOutGroup(tag, ms));
		return 1;
	}
	static int lua_Mix_HaltGroup(lutok::state& state){
		int tag = -1;
		if (state.is_number(1)){
			tag = state.to_integer(1);
		}
		Mix_HaltGroup(tag);
		return 0;
	}
	static int lua_Mix_SetPanning(lutok::state& state){
		int channel = MIX_CHANNEL_POST;
		Uint8 left = 255;
		Uint8 right = 255;

		if (state.is_number(1)){
			channel = state.to_integer(1);
		}
		if (state.is_number(2)){
			left = static_cast<Uint8>(state.to_integer(2));
		}
		if (state.is_number(3)){
			right = static_cast<Uint8>(state.to_integer(3));
		}
		int result = Mix_SetPanning(channel, left, right);
		state.push_boolean(result != 0);
		return 1;
	}
	static int lua_Mix_SetDistance(lutok::state& state){
		int channel = MIX_CHANNEL_POST;
		Uint8 distance = 0;

		if (state.is_number(1)){
			channel = state.to_integer(1);
		}
		if (state.is_number(2)){
			distance = static_cast<Uint8>(state.to_integer(2));
		}
		int result = Mix_SetDistance(channel, distance);
		state.push_boolean(result != 0);
		return 1;
	}
	static int lua_Mix_SetPosition(lutok::state& state){
		int channel = MIX_CHANNEL_POST;
		Sint16 angle = 0;
		Uint8 distance = 0;

		if (state.is_number(1)){
			channel = state.to_integer(1);
		}
		if (state.is_number(2)){
			angle = static_cast<Uint16>(state.to_integer(2));
		}
		if (state.is_number(3)){
			distance = static_cast<Uint8>(state.to_integer(3));
		}
		int result = Mix_SetPosition(channel, angle, distance);
		state.push_boolean(result != 0);
		return 1;
	}
	static int lua_Mix_SetReverseStereo(lutok::state& state){
		int channel = MIX_CHANNEL_POST;
		int flip = 0;

		if (state.is_number(1)){
			channel = state.to_integer(1);
		}
		if (state.is_number(2) || state.is_boolean(2)){
			flip = state.to_integer(2);
		}
		int result = Mix_SetReverseStereo(channel, flip);
		state.push_boolean(result != 0);
		return 1;
	}
	static int lua_Mix_UnregisterAllEffects(lutok::state& state){
		int channel = MIX_CHANNEL_POST;	
		if (state.is_number(1)){
			channel = state.to_integer(1);
		}
		int result = Mix_UnregisterAllEffects(channel);
		state.push_boolean(result != 0);
		return 1;
	}

	void init_sdl_mixer(moduleDef & module){
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