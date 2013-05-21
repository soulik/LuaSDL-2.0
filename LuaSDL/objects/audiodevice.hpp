#ifndef LUA_SDL_OBJECTS_AUDIODEVICE_H
#define LUA_SDL_OBJECTS_AUDIODEVICE_H

#include "common.hpp"

namespace LuaSDL {

	struct AudioDevice_Data {
		SDL_AudioDeviceID id;
		SDL_AudioSpec * audioSpec;
	};

	class Lua_SDL_AudioDevice : public LObject<Lua_SDL_AudioDevice, AudioDevice_Data *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_AudioDevice, AudioDevice_Data *, "AudioDevice") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_AudioDevice, "pause", pauseAudio);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_AudioDevice, "lock", lockAudio);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_AudioDevice, "unlock", unlockAudio);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioDevice, AudioDevice_Data *, "id", getAudioID, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioDevice, AudioDevice_Data *, "audioSpec", getAudioSpec, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioDevice, AudioDevice_Data *, "status", getAudioStatus, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioDevice, AudioDevice_Data *, "connected", isAudioConnected, null_method);	
		}

		void destructor(lutok::state & state, AudioDevice_Data * audiodevice){
			SDL_PauseAudioDevice(audiodevice->id, 1);
			SDL_CloseAudioDevice(audiodevice->id);
			delete audiodevice->audioSpec;
			delete audiodevice;
		}

		int LOBJECT_METHOD(pauseAudio, AudioDevice_Data * audiodevice){
			SDL_PauseAudioDevice(audiodevice->id, (state.to_boolean(1)) ? 1 : 0);
			return 0;
		}
		int LOBJECT_METHOD(lockAudio, AudioDevice_Data * audiodevice){
			SDL_LockAudioDevice(audiodevice->id);
			return 0;
		}
		int LOBJECT_METHOD(unlockAudio, AudioDevice_Data * audiodevice){
			SDL_UnlockAudioDevice(audiodevice->id);
			return 0;
		}
		int LOBJECT_METHOD(getAudioID, AudioDevice_Data * audiodevice){
			state.push_integer(audiodevice->id);
			return 1;
		}
		int LOBJECT_METHOD(getAudioSpec, AudioDevice_Data * audiodevice){
			Lua_SDL_AudioSpec * as = LOBJECT_INSTANCE(Lua_SDL_AudioSpec);
			as->push(audiodevice->audioSpec);
			return 1;
		}
		int LOBJECT_METHOD(getAudioStatus, AudioDevice_Data * audiodevice){
			state.push_integer(SDL_GetAudioDeviceStatus(audiodevice->id));
			return 1;
		}
		int LOBJECT_METHOD(isAudioConnected, AudioDevice_Data * audiodevice){
			/*
			int status = SDL_AudioDeviceConnected(audiodevice->id);
			if (status>=0){
				state.push_boolean(status == 1);
				return 1;
			}else{
				return 0;
			}
			*/
			return 0;
		}
	};
}

#endif
