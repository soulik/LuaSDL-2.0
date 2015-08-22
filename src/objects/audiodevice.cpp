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

		int allowedChanges = SDL_AUDIO_ALLOW_ANY_CHANGE;
		if (stack->is<LUA_TNUMBER>(4)){
			allowedChanges = stack->to<int>(4);
		}

		if (!inSpec->callback){
			inSpec->callback = AudioDevice::audioCallback;
		}
		inSpec->userdata = reinterpret_cast<void*>(adata);
		adata->buffer = new AudioBuffer_internal();
		const std::string device = stack->to<const std::string>(1);

		SDL_AudioDeviceID id = SDL_OpenAudioDevice(
			device.c_str(),
			(stack->to<bool>(2)) ? 1 : 0,
			inSpec,
			outSpec,
			allowedChanges
			);
		if (id >= 2){
			AudioDevice * interfaceAudioDevice = state.getInterface<AudioDevice>("LuaSDL_AudioDevice");

			adata->id = id;
			adata->audioSpec = outSpec;
			AudioBuffer::setAudioBufferFormat(adata->buffer, AUDIO_U8);
			adata->buffer->clear();
			adata->pos = 0;
			adata->ownBuffer = true;

			return adata;
		}
		else{
			delete adata->buffer;
			delete adata;
			delete outSpec;
			return nullptr;
		}
	}

	int AudioDevice::getAudioSpec(State & state, AudioDevice_Data * audiodevice) {
		Stack * stack = state.stack;
		AudioSpec * interfaceAudioSpec = state.getInterface<AudioSpec>("LuaSDL_AudioSpec");
		interfaceAudioSpec->push(audiodevice->audioSpec);
		return 1;
	}

	int AudioDevice::getBuffer(State & state, LuaSDL::AudioDevice_Data * audiodevice){
		AudioBuffer * interfaceAudioBuffer = state.getInterface<AudioBuffer>("LuaSDL_AudioBuffer");
		interfaceAudioBuffer->push(audiodevice->buffer, !audiodevice->ownBuffer);
		return 1;
	}

	int AudioDevice::setBuffer(State & state, LuaSDL::AudioDevice_Data * audiodevice){
		AudioBuffer * interfaceAudioBuffer = state.getInterface<AudioBuffer>("LuaSDL_AudioBuffer");
		SDL_LockAudioDevice(audiodevice->id);
		if (audiodevice->ownBuffer){
			delete audiodevice->buffer;
			audiodevice->ownBuffer = false;
		}
		audiodevice->buffer = interfaceAudioBuffer->get(1);
		SDL_UnlockAudioDevice(audiodevice->id);
		return 0;
	}

	void initAudioDevice(State * state, Module & module){
		INIT_OBJECT(AudioDevice);
		//module["AudioDevice"] = lua_SDL_OpenAudioDevice;
	}

};
