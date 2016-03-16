#ifndef LUA_SDL_OBJECTS_AUDIODEVICE_H
#define LUA_SDL_OBJECTS_AUDIODEVICE_H

#include "common.hpp"
#include "objects/audiobuffer.hpp"

namespace LuaSDL {
	struct AudioDevice_Data {
		SDL_AudioDeviceID id;
		SDL_AudioSpec * audioSpec;
		AudioBuffer_internal * buffer;
		volatile size_t pos;
		bool ownBuffer;

		AudioDevice_Data(){
			id = 0;
			audioSpec = nullptr;
			buffer = nullptr;
			pos = 0;
			ownBuffer = false;
		}
		~AudioDevice_Data(){
			if (audioSpec){
				delete audioSpec;
				audioSpec = nullptr;
			}
			if (ownBuffer && buffer){
				delete buffer;
				buffer = nullptr;
				ownBuffer = false;
			}
		}

	};
	class AudioDevice : public Object<AudioDevice_Data> {
	public:
		explicit AudioDevice(State * state) : Object<AudioDevice_Data>(state) {
			LUTOK_METHOD("play", &AudioDevice::playAudio);
			LUTOK_METHOD("pause", &AudioDevice::pauseAudio);
			LUTOK_METHOD("lock", &AudioDevice::lockAudio);
			LUTOK_METHOD("unlock", &AudioDevice::unlockAudio);
			LUTOK_METHOD("resetCallback", &AudioDevice::resetCallback);
			LUTOK_METHOD("customCallback", &AudioDevice::customCallback);
			LUTOK_PROPERTY("id", &AudioDevice::getAudioID, &AudioDevice::nullMethod);
			LUTOK_PROPERTY("audioSpec", &AudioDevice::getAudioSpec, &AudioDevice::nullMethod);	
			LUTOK_PROPERTY("status", &AudioDevice::getAudioStatus, &AudioDevice::nullMethod);	
			LUTOK_PROPERTY("connected", &AudioDevice::isAudioConnected, &AudioDevice::nullMethod);	
			LUTOK_PROPERTY("buffer", &AudioDevice::getBuffer, &AudioDevice::setBuffer);	
			LUTOK_PROPERTY("pos", &AudioDevice::getBufferPos, &AudioDevice::setBufferPos);	
		}

		AudioDevice_Data * constructor(State & state, bool & managed);

		void destructor(State & state, AudioDevice_Data * audiodevice);
		int playAudio(State & state, AudioDevice_Data * audiodevice);
		int pauseAudio(State & state, AudioDevice_Data * audiodevice);
		int lockAudio(State & state, AudioDevice_Data * audiodevice);
		int unlockAudio(State & state, AudioDevice_Data * audiodevice);
		int getAudioID(State & state, AudioDevice_Data * audiodevice);
		int getAudioSpec(State & state, AudioDevice_Data * audiodevice);
		int getAudioStatus(State & state, AudioDevice_Data * audiodevice);
		int getBufferPos(State & state, AudioDevice_Data * audiodevice);
		int setBufferPos(State & state, AudioDevice_Data * audiodevice);
		int isAudioConnected(State & state, AudioDevice_Data * audiodevice);
		int getBuffer(State & state, AudioDevice_Data * audiodevice);
		int setBuffer(State & state, AudioDevice_Data * audiodevice);
		int resetCallback(State & state, AudioDevice_Data * audiodevice);
		int customCallback(State & state, AudioDevice_Data * audiodevice);

		static void audioCallback(void *, Uint8 *, int);

		void createBuffer(AudioDevice_Data * audiodevice);
		void freeBuffer(AudioDevice_Data * audiodevice);
	};
}

#endif
