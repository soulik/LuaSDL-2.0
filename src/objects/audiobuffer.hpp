#ifndef LUA_SDL_OBJECTS_AUDIOBUFFER_H
#define LUA_SDL_OBJECTS_AUDIOBUFFER_H

#include "common.hpp"
#include <vector>

namespace LuaSDL {
	typedef void(*lua_AudioBufferGet)(State & state, Uint8 * buffer, size_t a_index);
	typedef void(*lua_AudioBufferSet)(State & state, Uint8 * buffer, size_t a_index, int l_index);

	class AudioBuffer_internal {
	private:
		void freeBuffer(){
			if (buffer){
				SDL_free(buffer);
			}
			buffer = nullptr;
		}
	public:
		AudioBuffer_internal(){
			buffer = nullptr;
			size = 0;
			physicalSize = 0;
			getValue = nullptr;
			setValue = nullptr;
			pos = 0;
		}
		~AudioBuffer_internal(){
			freeBuffer();
		}
		void setSize(size_t _size, size_t element_size);
		void clear();
		Uint8 * buffer;
		size_t physicalSize;
		size_t size;
		volatile size_t pos;
		SDL_AudioFormat format;
		lua_AudioBufferGet getValue;
		lua_AudioBufferSet setValue;
	};

	class AudioBuffer;
	
	typedef int (AudioBuffer::*lua_AudioBufferMethod)(State &, AudioBuffer_internal *);

	class AudioBuffer : public Object<AudioBuffer_internal> {
	public:
		explicit AudioBuffer(State * state) : Object<AudioBuffer_internal>(state) {
			LUTOK_METHOD("clear", &AudioBuffer::clearBuffer);
			LUTOK_METHOD("getData", &AudioBuffer::getData);
			LUTOK_METHOD("setData", &AudioBuffer::setData);
			LUTOK_PROPERTY("size", &AudioBuffer::getLen, &AudioBuffer::setLen);	
			//LUTOK_PROPERTY("data", &AudioBuffer::getDataTable, &AudioBuffer::nullMethod);	
			LUTOK_PROPERTY("format", &AudioBuffer::getFormat, &AudioBuffer::setFormat);	
			LUTOK_PROPERTY("pos", &AudioBuffer::getPos, &AudioBuffer::setPos);	
		}

		AudioBuffer_internal * constructor(State & state, bool & managed);

		void destructor(State & state, AudioBuffer_internal * audiobuffer){
			delete audiobuffer;
		}

		int inline clearBuffer(State & state, AudioBuffer_internal * audiobuffer);
		int inline getFormat(State & state, AudioBuffer_internal * audiobuffer);
		int setFormat(State & state, AudioBuffer_internal * audiobuffer);
		int inline getPos(State & state, AudioBuffer_internal * audiobuffer);
		int setPos(State & state, AudioBuffer_internal * audiobuffer);

		int inline getLen(State & state, AudioBuffer_internal * audiobuffer);
		int setLen(State & state, AudioBuffer_internal * audiobuffer);
		
		int getData(State & state, AudioBuffer_internal * audiobuffer);
		int setData(State & state, AudioBuffer_internal * audiobuffer);

		static size_t getFormatElementSize(int format);

		static bool setAudioBufferFormat(AudioBuffer_internal * audiobuffer, int format);
	};
}

#endif
