#include "common.hpp"
#include "objects/mix_chunk.hpp"
#include "objects/audiospec.hpp"

namespace LuaSDL {

	/* Magic numbers for various audio file formats */
#define RIFF        0x46464952      /* "RIFF" */
#define WAVE        0x45564157      /* "WAVE" */
#define FORM        0x4d524f46      /* "FORM" */
#define OGGS        0x5367674f      /* "OggS" */
#define CREA        0x61657243      /* "Crea" */
#define FLAC        0x43614C66      /* "fLaC" */

	extern "C" SDL_AudioSpec *Mix_LoadAIFF_RW(SDL_RWops *src, int freesrc, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len);
	extern "C" SDL_AudioSpec *Mix_LoadOGG_RW(SDL_RWops *src, int freesrc, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len);
	extern "C" SDL_AudioSpec *Mix_LoadFLAC_RW(SDL_RWops *src, int freesrc, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len);
	extern "C" SDL_AudioSpec *Mix_LoadVOC_RW(SDL_RWops *src, int freesrc, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len);
	extern "C" SDL_AudioSpec *Mix_LoadMP3_RW(SDL_RWops *src, int freesrc, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len);
	extern "C" SDL_AudioSpec *Mix_LoadAIFF_RW(SDL_RWops *src, int freesrc, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len);
	extern "C" SDL_AudioSpec *Mix_LoadAIFF_RW(SDL_RWops *src, int freesrc, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len);
	extern "C" SDL_AudioSpec *Mix_LoadAIFF_RW(SDL_RWops *src, int freesrc, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len);

	static int detect_mp3(Uint8 *magic)
	{
		if (strncmp((char *)magic, "ID3", 3) == 0) {
			return 1;
		}

		/* Detection code lifted from SMPEG */
		if (((magic[0] & 0xff) != 0xff) || // No sync bits
			((magic[1] & 0xf0) != 0xf0) || //
			((magic[2] & 0xf0) == 0x00) || // Bitrate is 0
			((magic[2] & 0xf0) == 0xf0) || // Bitrate is 15
			((magic[2] & 0x0c) == 0x0c) || // Frequency is 3
			((magic[1] & 0x06) == 0x00)) { // Layer is 4
			return(0);
		}
		return 1;
	}

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
		stack->push<const std::string &>(Mix_GetError());
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

	static void lua_Mix_EffectCallback(int chan, void *stream, int len, void *udata){
		lua_EffectWrapper * wrapper = reinterpret_cast<lua_EffectWrapper*>(udata);
		State * state = wrapper->state;
		Stack * stack = state->stack;

		stack->regValue(wrapper->fnRef);
		if (stack->is<LUA_TFUNCTION>(-1)){
			stack->pushLString(std::string(reinterpret_cast<const char *>(stream), len));

			try{
				stack->pcall(1, 1, 0);

				if (stack->is<LUA_TSTRING>(-1)){
					const std::string resultData = stack->toLString(-1);
					memcpy(stream, resultData.c_str(), len);
				}
			}
			catch (std::runtime_error & e){
				if (wrapper->errFnRef != LUA_REFNIL){
					stack->regValue(wrapper->errFnRef);
					stack->pushValue(-2);
					if (stack->is<LUA_TFUNCTION>(-1)){
						try{
							stack->pcall(1, 0, 0);
						}
						catch (std::runtime_error & e){
							stack->pop(1);
						}
					}
				}
			}

			stack->pop(1);
		}
	}

	static void lua_Mix_EffectDoneCallback(int chan, void *udata){
		lua_EffectWrapper * wrapper = reinterpret_cast<lua_EffectWrapper*>(udata);
		State * state = wrapper->state;
		Stack * stack = state->stack;
		stack->unref(wrapper->fnRef);
		if (wrapper->errFnRef != LUA_REFNIL){
			stack->unref(wrapper->errFnRef);
		}
		delete wrapper;
	}

	static int lua_Mix_RegisterEffect(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TFUNCTION>(2)){
			lua_EffectWrapper * wrapper = new lua_EffectWrapper;
			
			wrapper->state = &state;
			
			stack->pushValue(2);
			wrapper->fnRef = stack->ref();

			if (stack->is<LUA_TFUNCTION>(3)){
				stack->pushValue(3);
				wrapper->fnRef = stack->ref();
			}
			else{
				wrapper->errFnRef = LUA_REFNIL;
			}

			int channel = stack->to<int>(1);

			Mix_RegisterEffect(channel, lua_Mix_EffectCallback, lua_Mix_EffectDoneCallback, wrapper);
			return 1;
		}
		else{
			return 0;
		}
	}

	static int lua_Mix_Load(State & state){
		Stack * stack = state.stack;

		if (stack->is<LUA_TSTRING>(1)){
			AudioSpec * interfaceAS = state.getInterface<AudioSpec>("LuaSDL_AudioSpec");
			SDL_AudioSpec * inputSpec = interfaceAS->get(2);
			if (inputSpec){

				const std::string filename = stack->toLString(1);
				SDL_RWops * src = SDL_RWFromFile(filename.c_str(), "rb");
				if (!src){
					state.error("Couldn't open audio file: %s\n", filename.c_str());
				}
				Uint32 magic;
				SDL_AudioSpec wavespec, *audiospec = nullptr;
				Uint8 *abuf = nullptr;
				Uint32 alen;

				/* note: send a copy of the mixer spec */
				wavespec = *inputSpec;

				/* Find out what kind of audio file this is */
				magic = SDL_ReadLE32(src);
				/* Seek backwards for compatibility with older loaders */
				SDL_RWseek(src, -(int)sizeof(Uint32), RW_SEEK_CUR);

				switch (magic) {
				case WAVE:
				case RIFF:
					audiospec = SDL_LoadWAV_RW(src, 0, &wavespec,
						(Uint8 **)&abuf, &alen);
					break;
				case FORM:
					audiospec = Mix_LoadAIFF_RW(src, 0, &wavespec,
						(Uint8 **)&abuf, &alen);
					break;
				case OGGS:
					audiospec = Mix_LoadOGG_RW(src, 0, &wavespec,
						(Uint8 **)&abuf, &alen);
					break;
				case FLAC:
					audiospec = Mix_LoadFLAC_RW(src, 0, &wavespec,
						(Uint8 **)&abuf, &alen);
					break;
				case CREA:
					audiospec = Mix_LoadVOC_RW(src, 0, &wavespec,
						(Uint8 **)&abuf, &alen);
					break;
				default:
					if (detect_mp3((Uint8*)&magic))	{
						audiospec = Mix_LoadMP3_RW(src, 0, &wavespec,
							(Uint8 **)&abuf, &alen);
						break;
					}
					break;
				}
				SDL_RWclose(src);

				if (audiospec) {
					stack->pushLString(std::string(reinterpret_cast<char*>(abuf), alen));
					interfaceAS->push(audiospec, true);
					return 2;
				}
				else{
					state.error("Unreckonized audio file\n");
				}
			}
		}
		return 0;
	}

	

	void initSDLmixer(Module & module){
		module["mixerInit"] = lua_Mixer_Init;
		module["mixerQuit"] = lua_Mixer_Quit;
		module["mixerOpenAudio"] = lua_Mixer_OpenAudio;
		module["mixerCloseAudio"] = lua_Mixer_CloseAudio;
		module["mixerGetError"] = lua_Mix_GetError;
		module["mixerQuerySpec"] = lua_Mix_QuerySpec;

		module["mixerLoad"] = lua_Mix_Load;

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
		module["mixerRegisterEffect"] = lua_Mix_RegisterEffect;

		

	}
}