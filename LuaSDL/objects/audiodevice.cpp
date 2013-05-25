#include "objects/audiospec.hpp"
#include "objects/audiodevice.hpp"
#include "objects/audiobuffer.hpp"
#include <lua.hpp>

void LuaSDL::Lua_SDL_AudioDevice::audioCallback(void * data, Uint8 * stream, int len){
	LuaSDL::AudioDevice_Data * adata = reinterpret_cast<LuaSDL::AudioDevice_Data *>(data);
	Uint8 * buffer = adata->buffer->buffer;
	size_t bytes_to_copy = len;

	if ((adata->buffer->pos + bytes_to_copy) > adata->buffer->physicalSize){
		bytes_to_copy = (adata->buffer->physicalSize - adata->buffer->pos);
	}
	if ((adata->pos + bytes_to_copy) > len){
		bytes_to_copy = (len - adata->pos);
	}

	SDL_memcpy(stream + adata->pos, buffer + adata->buffer->pos, bytes_to_copy);
	adata->buffer->pos = (adata->buffer->pos + bytes_to_copy) % adata->buffer->physicalSize;
	adata->pos = (adata->pos + bytes_to_copy) % len;
}

static int lua_SDL_OpenAudioDevice(lutok::state& state){
	LuaSDL::Lua_SDL_AudioSpec * as = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_AudioSpec);
	SDL_AudioSpec * inSpec = as->check(3);
	SDL_AudioSpec * outSpec = new SDL_AudioSpec;
	LuaSDL::AudioDevice_Data * adata = new LuaSDL::AudioDevice_Data;

	int allowedChanges = SDL_AUDIO_ALLOW_ANY_CHANGE;
	if (state.is_number(4)){
		allowedChanges = state.to_integer(4);
	}

	if (!inSpec->callback){
		inSpec->callback = LuaSDL::Lua_SDL_AudioDevice::audioCallback;
	}
	inSpec->userdata = reinterpret_cast<void*>(adata);
	adata->buffer = new LuaSDL::AudioBuffer();
	
	SDL_AudioDeviceID id = SDL_OpenAudioDevice(
			state.to_string(1).c_str(),
			(state.to_boolean(2)) ? 1 : 0,
			inSpec,
			outSpec,
			allowedChanges
		);
	if (id >= 2){
		LuaSDL::Lua_SDL_AudioDevice * ad = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_AudioDevice);
		
		adata->id = id;
		adata->audioSpec = outSpec;
		LuaSDL::Lua_SDL_AudioBuffer::setAudioBufferFormat(adata->buffer, AUDIO_U8);
		adata->buffer->clear();
		adata->pos = 0;

		ad->push(adata);
		return 1;
	}else{
		delete adata->buffer;
		delete adata;
		delete outSpec;
		return 0;
	}
}

int LuaSDL::Lua_SDL_AudioDevice::LOBJECT_METHOD(getAudioSpec, AudioDevice_Data * audiodevice){
	LuaSDL::Lua_SDL_AudioSpec * as = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_AudioSpec);
	as->push(audiodevice->audioSpec, false);
	return 1;
}

int LuaSDL::Lua_SDL_AudioDevice::LOBJECT_METHOD(getBuffer, LuaSDL::AudioDevice_Data * audiodevice){
	LuaSDL::Lua_SDL_AudioBuffer * ab = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_AudioBuffer);
	ab->push(audiodevice->buffer, false);
	return 1;
}

void LuaSDL::init_audiodevice(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_AudioDevice);
	module["AudioDevice"] = lua_SDL_OpenAudioDevice;
}
