#include "objects/audiospec.hpp"
#include "objects/audiodevice.hpp"
#include "objects/audiobuffer.hpp"
#include <lua.hpp>

namespace LuaSDL {
	int AudioDevice::playAudio(State & state, AudioDevice_Data * audiodevice) {
		Stack * stack = state.stack;
		SDL_PauseAudioDevice(audiodevice->id, 0);
		return 0;
	}
	int AudioDevice::pauseAudio(State & state, AudioDevice_Data * audiodevice) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TBOOLEAN>(1)){
			SDL_PauseAudioDevice(audiodevice->id, (stack->to<bool>(1)) ? 1 : 0);
		}
		return 0;
	}
	int AudioDevice::lockAudio(State & state, AudioDevice_Data * audiodevice) {
		Stack * stack = state.stack;
		SDL_LockAudioDevice(audiodevice->id);
		return 0;
	}
	int AudioDevice::unlockAudio(State & state, AudioDevice_Data * audiodevice) {
		Stack * stack = state.stack;
		SDL_UnlockAudioDevice(audiodevice->id);
		return 0;
	}
	int AudioDevice::getAudioID(State & state, AudioDevice_Data * audiodevice) {
		Stack * stack = state.stack;
		stack->push<int>(audiodevice->id);
		return 1;
	}
	int AudioDevice::getAudioStatus(State & state, AudioDevice_Data * audiodevice) {
		Stack * stack = state.stack;
		stack->push<int>(SDL_GetAudioDeviceStatus(audiodevice->id));
		return 1;
	}
	int AudioDevice::getBufferPos(State & state, AudioDevice_Data * audiodevice) {
		Stack * stack = state.stack;
		stack->push<int>(audiodevice->pos);
		return 1;
	}
	int AudioDevice::setBufferPos(State & state, AudioDevice_Data * audiodevice) {
		Stack * stack = state.stack;
		audiodevice->pos = stack->to<int>(1);
		return 0;
	}
	int AudioDevice::isAudioConnected(State & state, AudioDevice_Data * audiodevice) {
		Stack * stack = state.stack;
#ifdef AUDIODEVICECONNECTED_DEFINED
		int status = SDL_AudioDeviceConnected(audiodevice->id);
		if (status >= 0){
			stack->push<bool>(status == 1);
			return 1;
		}
		else{
			return 0;
		}
#else
		return 0;
#endif
	}
	void AudioDevice::audioCallback(void * data, Uint8 * stream, int len){
		AudioDevice_Data * adata = reinterpret_cast<LuaSDL::AudioDevice_Data *>(data);
		Uint8 * buffer = adata->buffer->buffer;
		size_t bytes_to_copy = len;
		if (adata->buffer->size > 0){
			if ((adata->buffer->pos + bytes_to_copy) > adata->buffer->physicalSize){
				bytes_to_copy = (adata->buffer->physicalSize - adata->buffer->pos);
			}
			if ((adata->pos + bytes_to_copy) > (Uint32)len){
				bytes_to_copy = (len - adata->pos);
			}

			SDL_memcpy(stream + adata->pos, buffer + adata->buffer->pos, bytes_to_copy);
			adata->buffer->pos = (adata->buffer->pos + bytes_to_copy) % adata->buffer->physicalSize;
			adata->pos = (adata->pos + bytes_to_copy) % len;
		}
	}

	AudioDevice_Data * AudioDevice::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		AudioSpec * interfaceAudioSpec = state.getInterface<AudioSpec>("LuaSDL_AudioSpec");
		SDL_AudioSpec * inSpec = interfaceAudioSpec->get(3);
		SDL_AudioSpec * outSpec = new SDL_AudioSpec;
		AudioDevice_Data * adata = new LuaSDL::AudioDevice_Data;

		SDL_AudioSpec * tmpSpec = new SDL_AudioSpec;
		tmpSpec->callback = inSpec->callback;
		tmpSpec->channels = inSpec->channels;
		tmpSpec->format = inSpec->format;
		tmpSpec->freq = inSpec->freq;
		tmpSpec->padding = inSpec->padding;
		tmpSpec->samples = inSpec->samples;
		tmpSpec->silence = inSpec->silence;
		tmpSpec->size = inSpec->size;
		tmpSpec->userdata = inSpec->userdata;

		int allowedChanges = SDL_AUDIO_ALLOW_ANY_CHANGE;
		if (stack->is<LUA_TNUMBER>(4)){
			allowedChanges = stack->to<int>(4);
		}

		if (!inSpec->callback){
			tmpSpec->callback = AudioDevice::audioCallback;
			tmpSpec->userdata = reinterpret_cast<void*>(adata);
		}

		const std::string device = stack->to<const std::string>(1);

		SDL_AudioDeviceID id = SDL_OpenAudioDevice(
			device.c_str(),
			(stack->to<bool>(2)) ? 1 : 0,
			tmpSpec,
			outSpec,
			allowedChanges
			);

		if (id >= 2){
			AudioDevice * interfaceAudioDevice = state.getInterface<AudioDevice>("LuaSDL_AudioDevice");

			adata->id = id;
			adata->audioSpec = outSpec;
			if (!inSpec->callback){
				createBuffer(adata);
			}
			return adata;
		}
		else{
			delete adata->buffer;
			delete adata;
			delete outSpec;
			return nullptr;
		}
	}

	void AudioDevice::createBuffer(AudioDevice_Data * audiodevice){
		freeBuffer(audiodevice);
		SDL_LockAudioDevice(audiodevice->id);
		audiodevice->buffer = new AudioBuffer_internal();
		AudioBuffer::setAudioBufferFormat(audiodevice->buffer, AUDIO_U8);
		audiodevice->buffer->clear();
		audiodevice->pos = 0;
		audiodevice->ownBuffer = true;
		SDL_UnlockAudioDevice(audiodevice->id);
	}

	void AudioDevice::freeBuffer(AudioDevice_Data * audiodevice){
		SDL_LockAudioDevice(audiodevice->id);
		if (audiodevice->ownBuffer && audiodevice->buffer){
			delete audiodevice->buffer;
			audiodevice->buffer = nullptr;
			audiodevice->ownBuffer = false;
		}
		audiodevice->pos = 0;
		SDL_UnlockAudioDevice(audiodevice->id);
	}

	int AudioDevice::getAudioSpec(State & state, AudioDevice_Data * audiodevice) {
		Stack * stack = state.stack;
		AudioSpec * interfaceAudioSpec = state.getInterface<AudioSpec>("LuaSDL_AudioSpec");
		interfaceAudioSpec->push(audiodevice->audioSpec);
		return 1;
	}

	int AudioDevice::getBuffer(State & state, LuaSDL::AudioDevice_Data * audiodevice){
		AudioBuffer * interfaceAudioBuffer = state.getInterface<AudioBuffer>("LuaSDL_AudioBuffer");
		if (audiodevice->buffer){
			interfaceAudioBuffer->push(audiodevice->buffer, !audiodevice->ownBuffer);
		}
		else{
			state.stack->pushNil();
		}
		return 1;
	}

	int AudioDevice::setBuffer(State & state, LuaSDL::AudioDevice_Data * audiodevice){
		AudioBuffer * interfaceAudioBuffer = state.getInterface<AudioBuffer>("LuaSDL_AudioBuffer");
		SDL_LockAudioDevice(audiodevice->id);
		freeBuffer(audiodevice);
		audiodevice->buffer = interfaceAudioBuffer->get(1);
		SDL_UnlockAudioDevice(audiodevice->id);
		return 0;
	}

	int AudioDevice::resetCallback(State & state, AudioDevice_Data * audiodevice){
		SDL_LockAudioDevice(audiodevice->id);
		createBuffer(audiodevice);
		audiodevice->audioSpec->userdata = reinterpret_cast<void*>(audiodevice);
		audiodevice->audioSpec->callback = AudioDevice::audioCallback;
		SDL_UnlockAudioDevice(audiodevice->id);
		return 0;
	}

	int AudioDevice::customCallback(State & state, AudioDevice_Data * audiodevice){
		Stack * stack = state.stack;
		SDL_LockAudioDevice(audiodevice->id);
		freeBuffer(audiodevice);
		if (stack->is<LUA_TLIGHTUSERDATA>(1)){
			audiodevice->audioSpec->callback = reinterpret_cast<SDL_AudioCallback>(stack->to<void*>(1));
			if (stack->is<LUA_TLIGHTUSERDATA>(2)){
				audiodevice->audioSpec->userdata = stack->to<void*>(2);
			}
			else{
				audiodevice->audioSpec->userdata = nullptr;
			}
		}
		SDL_UnlockAudioDevice(audiodevice->id);
		return 0;
	}

	void AudioDevice::destructor(State & state, AudioDevice_Data * audiodevice){
		SDL_PauseAudioDevice(audiodevice->id, 1);
		SDL_CloseAudioDevice(audiodevice->id);
		freeBuffer(audiodevice);
		delete audiodevice;
	}

	void initAudioDevice(State * state, Module & module){
		INIT_OBJECT(AudioDevice);
		//module["AudioDevice"] = lua_SDL_OpenAudioDevice;
	}

};
