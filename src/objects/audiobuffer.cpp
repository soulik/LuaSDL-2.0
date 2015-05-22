#include "objects/audiobuffer.hpp"
#include <lua.hpp>

void inline Lua_AudioBuffer_get_U8(State & state, Uint8 * buffer, size_t a_index){
	stack->push<int>(buffer[a_index]);
}
void inline Lua_AudioBuffer_get_S8(State & state, Uint8 * buffer, size_t a_index){
	stack->push<int>(buffer[a_index]);
}
void inline Lua_AudioBuffer_get_U16LE(State & state, Uint8 * buffer, size_t a_index){
	stack->push<int>(((Uint16*)buffer)[a_index]);
}
void inline Lua_AudioBuffer_get_U16BE(State & state, Uint8 * buffer, size_t a_index){
	stack->push<int>(((Uint16*)buffer)[a_index]);
}
void inline Lua_AudioBuffer_get_S16LE(State & state, Uint8 * buffer, size_t a_index){
	stack->push<int>(((Sint16*)buffer)[a_index]);
}
void inline Lua_AudioBuffer_get_S16BE(State & state, Uint8 * buffer, size_t a_index){
	stack->push<int>(((Sint16*)buffer)[a_index]);
}
void inline Lua_AudioBuffer_get_U32LE(State & state, Uint8 * buffer, size_t a_index){
	stack->push<int>(((Uint32*)buffer)[a_index]);
}
void inline Lua_AudioBuffer_get_U32BE(State & state, Uint8 * buffer, size_t a_index){
	stack->push<int>(((Uint32*)buffer)[a_index]);
}
void inline Lua_AudioBuffer_get_S32LE(State & state, Uint8 * buffer, size_t a_index){
	stack->push<int>(((Sint32*)buffer)[a_index]);
}
void inline Lua_AudioBuffer_get_S32BE(State & state, Uint8 * buffer, size_t a_index){
	stack->push<int>(((Sint32*)buffer)[a_index]);
}
void inline Lua_AudioBuffer_get_F32(State & state, Uint8 * buffer, size_t a_index){
	state.push_number(((float*)buffer)[a_index]);
}


void inline Lua_AudioBuffer_set_U8(State & state, Uint8 * buffer, size_t a_index, int l_index){
	((Uint8*)buffer)[a_index] = (Uint8)stack->to<int>(l_index);
}
void inline Lua_AudioBuffer_set_S8(State & state, Uint8 * buffer, size_t a_index, int l_index){
	((Sint8*)buffer)[a_index] = (Sint8)stack->to<int>(l_index);
}
void inline Lua_AudioBuffer_set_U16LE(State & state, Uint8 * buffer, size_t a_index, int l_index){
	((Uint16*)buffer)[a_index] = (Uint16)stack->to<int>(l_index);
}
void inline Lua_AudioBuffer_set_U16BE(State & state, Uint8 * buffer, size_t a_index, int l_index){
	((Uint16*)buffer)[a_index] = (Uint16)stack->to<int>(l_index);
}
void inline Lua_AudioBuffer_set_S16LE(State & state, Uint8 * buffer, size_t a_index, int l_index){
	((Sint16*)buffer)[a_index] = (Sint16)stack->to<int>(l_index);
}
void inline Lua_AudioBuffer_set_S16BE(State & state, Uint8 * buffer, size_t a_index, int l_index){
	((Sint16*)buffer)[a_index] = (Sint16)stack->to<int>(l_index);
}
void inline Lua_AudioBuffer_set_U32LE(State & state, Uint8 * buffer, size_t a_index, int l_index){
	((Uint32*)buffer)[a_index] = (Uint32)stack->to<int>(l_index);
}
void inline Lua_AudioBuffer_set_U32BE(State & state, Uint8 * buffer, size_t a_index, int l_index){
	((Uint32*)buffer)[a_index] = (Uint32)stack->to<int>(l_index);
}
void inline Lua_AudioBuffer_set_S32LE(State & state, Uint8 * buffer, size_t a_index, int l_index){
	((Sint32*)buffer)[a_index] = (Sint32)stack->to<int>(l_index);
}
void inline Lua_AudioBuffer_set_S32BE(State & state, Uint8 * buffer, size_t a_index, int l_index){
	((Sint32*)buffer)[a_index] = (Sint32)stack->to<int>(l_index);
}
void inline Lua_AudioBuffer_set_F32(State & state, Uint8 * buffer, size_t a_index, int l_index){
	((float*)buffer)[a_index] = (float)state.to_number(l_index);
}

bool LuaSDL::Lua_SDL_AudioBuffer::setAudioBufferFormat(LuaSDL::AudioBuffer * audiobuffer, int format){
	bool result = false;
	switch (format){
	case AUDIO_U8:
		audiobuffer->getValue = Lua_AudioBuffer_get_U8; audiobuffer->setValue = Lua_AudioBuffer_set_U8; result = true; break;
	case AUDIO_S8:
		audiobuffer->getValue = Lua_AudioBuffer_get_S8; audiobuffer->setValue = Lua_AudioBuffer_set_S8; result = true; break;
	case AUDIO_U16LSB:
		audiobuffer->getValue = Lua_AudioBuffer_get_U16LE; audiobuffer->setValue = Lua_AudioBuffer_set_U16LE; result = true; break;
	case AUDIO_S16LSB:
		audiobuffer->getValue = Lua_AudioBuffer_get_S16LE; audiobuffer->setValue = Lua_AudioBuffer_set_S16LE; result = true; break;
	case AUDIO_U16MSB:
		audiobuffer->getValue = Lua_AudioBuffer_get_U16BE; audiobuffer->setValue = Lua_AudioBuffer_set_U16BE; result = true; break;
	case AUDIO_S16MSB:
		audiobuffer->getValue = Lua_AudioBuffer_get_S16BE; audiobuffer->setValue = Lua_AudioBuffer_set_S16BE; result = true; break;
	case AUDIO_S32LSB:
		audiobuffer->getValue = Lua_AudioBuffer_get_S32LE; audiobuffer->setValue = Lua_AudioBuffer_set_S32LE; result = true; break;
	case AUDIO_S32MSB:
		audiobuffer->getValue = Lua_AudioBuffer_get_S32BE; audiobuffer->setValue = Lua_AudioBuffer_set_S32BE; result = true; break;
	case AUDIO_F32LSB:
		audiobuffer->getValue = Lua_AudioBuffer_get_F32; audiobuffer->setValue = Lua_AudioBuffer_set_F32; result = true; break;
	}
	if (result){
		size_t elmSize = getFormatElementSize(format);
		if (getFormatElementSize(audiobuffer->format) != elmSize){
			audiobuffer->setSize(audiobuffer->size, elmSize);
		}
		audiobuffer->format = format;
		audiobuffer->pos = 0;
	}

	return result;
}

static int lua_AudioBuffer(State & state){
	LuaSDL::Lua_SDL_AudioBuffer & ab = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_AudioBuffer);
	LuaSDL::AudioBuffer * audio_buffer = new LuaSDL::AudioBuffer();

	if (stack->is<LUA_TNUMBER>(1)){
		audio_buffer->size = stack->to<int>(1);
	}

	if (stack->is<LUA_TNUMBER>(2)){
		LuaSDL::Lua_SDL_AudioBuffer::setAudioBufferFormat(audio_buffer, stack->to<int>(2));
	}else{
		LuaSDL::Lua_SDL_AudioBuffer::setAudioBufferFormat(audio_buffer, AUDIO_U8);
	}
	ab.clearBuffer(state, audio_buffer);
	ab.push(audio_buffer);
	return 1;
}

void LuaSDL::init_audiobuffer(State & state, Module & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_AudioBuffer);
	module["AudioBuffer"] = lua_AudioBuffer;
}
