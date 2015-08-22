#include "objects/audiobuffer.hpp"
#include <lua.hpp>

namespace LuaSDL {
	void AudioBuffer_internal::setSize(size_t _size, size_t element_size){
		if (_size > 0){
			size = _size;
			physicalSize = _size * element_size;
			if (!buffer){
				buffer = reinterpret_cast<Uint8*>(SDL_malloc(physicalSize));
			}
			else{
				buffer = reinterpret_cast<Uint8*>(SDL_realloc(buffer, physicalSize));
			}
		}
		else{
			size = 0;
			physicalSize = 0;
			freeBuffer();
		}
	}
	void AudioBuffer_internal::clear(){
		if (size > 0){
			SDL_memset(buffer, 0, physicalSize);
		}
	}

	int inline AudioBuffer::clearBuffer(State & state, AudioBuffer_internal * audiobuffer) {
		Stack * stack = state.stack;
		audiobuffer->clear();
		return 0;
	}
	int inline AudioBuffer::getFormat(State & state, AudioBuffer_internal * audiobuffer) {
		Stack * stack = state.stack;
		stack->push<int>(audiobuffer->format);
		return 1;
	}
	int AudioBuffer::setFormat(State & state, AudioBuffer_internal * audiobuffer) {
		Stack * stack = state.stack;
		int newformat = stack->to<int>(1);
		setAudioBufferFormat(audiobuffer, newformat);
		return 0;
	}
	int inline AudioBuffer::getPos(State & state, AudioBuffer_internal * audiobuffer) {
		Stack * stack = state.stack;
		stack->push<int>(audiobuffer->pos);
		return 1;
	}
	int AudioBuffer::setPos(State & state, AudioBuffer_internal * audiobuffer) {
		Stack * stack = state.stack;
		audiobuffer->pos = stack->to<int>(1);
		return 0;
	}

	int inline AudioBuffer::getLen(State & state, AudioBuffer_internal * audiobuffer) {
		Stack * stack = state.stack;
		stack->push<int>(audiobuffer->size);
		return 1;
	}
	int AudioBuffer::setLen(State & state, AudioBuffer_internal * audiobuffer) {
		Stack * stack = state.stack;
		Uint32 newlen = stack->to<int>(1);

		if ((newlen != audiobuffer->size) && (newlen >= 0)){
			audiobuffer->setSize(newlen, getFormatElementSize(audiobuffer->format));
			audiobuffer->pos = 0;
		}
		return 0;
	}

	int AudioBuffer::getData(State & state, AudioBuffer_internal * audiobuffer) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			size_t index = stack->to<int>(1);
			if ((index >= 0) && (index < audiobuffer->size)){
				if (audiobuffer->getValue){
					audiobuffer->getValue(state, audiobuffer->buffer, index);
					return 1;
				}
				else{
					return 0;
				}
			}
			else{
				return 0;
			}
		}
		else{
			stack->newTable();
			for (size_t index = 0; index < audiobuffer->size; index++){
				stack->push<int>(index + 1);
				audiobuffer->getValue(state, audiobuffer->buffer, index);
				stack->setTable();
			}
			return 1;
		}
	}
	int AudioBuffer::setData(State & state, AudioBuffer_internal * audiobuffer) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			size_t index = stack->to<int>(1);
			if ((index >= 0) && (index < audiobuffer->size)){
				if (audiobuffer->setValue){
					audiobuffer->setValue(state, audiobuffer->buffer, index, 2);
				}
			}
		}
		else if (stack->is<LUA_TTABLE>(1)){
			size_t items = stack->objLen(1);
			size_t offset = 0;
			size_t max_items = items;
			if (stack->is<LUA_TNUMBER>(2)){
				offset = stack->to<int>(2);
				if (offset < 0){
					offset = 0;
				}
			}
			if (stack->is<LUA_TNUMBER>(3)){
				max_items = stack->to<int>(3);
				if (max_items < 0){
					max_items = 0;
				}
			}
			if (offset + max_items > audiobuffer->size){
				audiobuffer->setSize(offset + max_items, getFormatElementSize(audiobuffer->format));
			}
			for (size_t index = 0; index < max_items; index++){
				stack->getField(index + 1, 1);
				audiobuffer->setValue(state, audiobuffer->buffer, index + offset, -1);
				stack->pop(1);
			}
			stack->push<int>(max_items);
			return 1;
		}
		return 0;
	}

	size_t AudioBuffer::getFormatElementSize(int format){
		switch (format){
		case AUDIO_U8:
		case AUDIO_S8:
			return 1;
		case AUDIO_U16LSB:
		case AUDIO_S16LSB:
		case AUDIO_U16MSB:
		case AUDIO_S16MSB:
			return 2;
		case AUDIO_S32LSB:
		case AUDIO_S32MSB:
		case AUDIO_F32LSB:
		case AUDIO_F32MSB:
			return 4;
		}
		return 0;
	}

	void inline Lua_AudioBuffer_get_U8(State & state, Uint8 * buffer, size_t a_index){
		Stack * stack = state.stack;
		stack->push<int>(buffer[a_index]);
	}
	void inline Lua_AudioBuffer_get_S8(State & state, Uint8 * buffer, size_t a_index){
		Stack * stack = state.stack;
		stack->push<int>(buffer[a_index]);
	}
	void inline Lua_AudioBuffer_get_U16LE(State & state, Uint8 * buffer, size_t a_index){
		Stack * stack = state.stack;
		stack->push<int>(((Uint16*)buffer)[a_index]);
	}
	void inline Lua_AudioBuffer_get_U16BE(State & state, Uint8 * buffer, size_t a_index){
		Stack * stack = state.stack;
		stack->push<int>(((Uint16*)buffer)[a_index]);
	}
	void inline Lua_AudioBuffer_get_S16LE(State & state, Uint8 * buffer, size_t a_index){
		Stack * stack = state.stack;
		stack->push<int>(((Sint16*)buffer)[a_index]);
	}
	void inline Lua_AudioBuffer_get_S16BE(State & state, Uint8 * buffer, size_t a_index){
		Stack * stack = state.stack;
		stack->push<int>(((Sint16*)buffer)[a_index]);
	}
	void inline Lua_AudioBuffer_get_U32LE(State & state, Uint8 * buffer, size_t a_index){
		Stack * stack = state.stack;
		stack->push<int>(((Uint32*)buffer)[a_index]);
	}
	void inline Lua_AudioBuffer_get_U32BE(State & state, Uint8 * buffer, size_t a_index){
		Stack * stack = state.stack;
		stack->push<int>(((Uint32*)buffer)[a_index]);
	}
	void inline Lua_AudioBuffer_get_S32LE(State & state, Uint8 * buffer, size_t a_index){
		Stack * stack = state.stack;
		stack->push<int>(((Sint32*)buffer)[a_index]);
	}
	void inline Lua_AudioBuffer_get_S32BE(State & state, Uint8 * buffer, size_t a_index){
		Stack * stack = state.stack;
		stack->push<int>(((Sint32*)buffer)[a_index]);
	}
	void inline Lua_AudioBuffer_get_F32(State & state, Uint8 * buffer, size_t a_index){
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(((float*)buffer)[a_index]);
	}


	void inline Lua_AudioBuffer_set_U8(State & state, Uint8 * buffer, size_t a_index, int l_index){
		Stack * stack = state.stack;
		((Uint8*)buffer)[a_index] = (Uint8)stack->to<int>(l_index);
	}
	void inline Lua_AudioBuffer_set_S8(State & state, Uint8 * buffer, size_t a_index, int l_index){
		Stack * stack = state.stack;
		((Sint8*)buffer)[a_index] = (Sint8)stack->to<int>(l_index);
	}
	void inline Lua_AudioBuffer_set_U16LE(State & state, Uint8 * buffer, size_t a_index, int l_index){
		Stack * stack = state.stack;
		((Uint16*)buffer)[a_index] = (Uint16)stack->to<int>(l_index);
	}
	void inline Lua_AudioBuffer_set_U16BE(State & state, Uint8 * buffer, size_t a_index, int l_index){
		Stack * stack = state.stack;
		((Uint16*)buffer)[a_index] = (Uint16)stack->to<int>(l_index);
	}
	void inline Lua_AudioBuffer_set_S16LE(State & state, Uint8 * buffer, size_t a_index, int l_index){
		Stack * stack = state.stack;
		((Sint16*)buffer)[a_index] = (Sint16)stack->to<int>(l_index);
	}
	void inline Lua_AudioBuffer_set_S16BE(State & state, Uint8 * buffer, size_t a_index, int l_index){
		Stack * stack = state.stack;
		((Sint16*)buffer)[a_index] = (Sint16)stack->to<int>(l_index);
	}
	void inline Lua_AudioBuffer_set_U32LE(State & state, Uint8 * buffer, size_t a_index, int l_index){
		Stack * stack = state.stack;
		((Uint32*)buffer)[a_index] = (Uint32)stack->to<int>(l_index);
	}
	void inline Lua_AudioBuffer_set_U32BE(State & state, Uint8 * buffer, size_t a_index, int l_index){
		Stack * stack = state.stack;
		((Uint32*)buffer)[a_index] = (Uint32)stack->to<int>(l_index);
	}
	void inline Lua_AudioBuffer_set_S32LE(State & state, Uint8 * buffer, size_t a_index, int l_index){
		Stack * stack = state.stack;
		((Sint32*)buffer)[a_index] = (Sint32)stack->to<int>(l_index);
	}
	void inline Lua_AudioBuffer_set_S32BE(State & state, Uint8 * buffer, size_t a_index, int l_index){
		Stack * stack = state.stack;
		((Sint32*)buffer)[a_index] = (Sint32)stack->to<int>(l_index);
	}
	void inline Lua_AudioBuffer_set_F32(State & state, Uint8 * buffer, size_t a_index, int l_index){
		Stack * stack = state.stack;
		((float*)buffer)[a_index] = (float)stack->to<LUA_NUMBER>(l_index);
	}

	bool AudioBuffer::setAudioBufferFormat(AudioBuffer_internal * audiobuffer, int format){
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

	AudioBuffer_internal * AudioBuffer::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		AudioBuffer * interfaceAudioBuffer = state.getInterface<AudioBuffer>("LuaSDL_AudioBuffer");
		AudioBuffer_internal * audio_buffer = new AudioBuffer_internal();

		if (stack->is<LUA_TNUMBER>(1)){
			audio_buffer->size = stack->to<int>(1);
		}

		if (stack->is<LUA_TNUMBER>(2)){
			AudioBuffer::setAudioBufferFormat(audio_buffer, stack->to<int>(2));
		}
		else{
			AudioBuffer::setAudioBufferFormat(audio_buffer, AUDIO_U8);
		}
		audio_buffer->clear();
		return audio_buffer;
	}

	void initAudioBuffer(State * state, Module & module){
		INIT_OBJECT(AudioBuffer);
		//module["AudioBuffer"] = lua_AudioBuffer;
	}
};

