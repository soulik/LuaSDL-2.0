#ifndef LUA_SDL_OBJECTS_AUDIOBUFFER_H
#define LUA_SDL_OBJECTS_AUDIOBUFFER_H

#include "common.hpp"
#include <vector>

namespace LuaSDL {
	typedef void(*lua_AudioBufferGet)(lutok::state & state, Uint8 * buffer, size_t a_index);
	typedef void(*lua_AudioBufferSet)(lutok::state & state, Uint8 * buffer, size_t a_index, int l_index);

	class AudioBuffer {
	private:
		void freeBuffer(){
			if (buffer){
				SDL_free(buffer);
			}
			buffer = nullptr;
		}
	public:
		AudioBuffer(){
			buffer = nullptr;
			size = 0;
			physicalSize = 0;
			getValue = nullptr;
			setValue = nullptr;
			pos = 0;
		}
		~AudioBuffer(){
			freeBuffer();
		}
		void setSize(size_t _size, size_t element_size){
			if (_size>0){
				size = _size;
				physicalSize = _size * element_size;
				if (!buffer){
					buffer = reinterpret_cast<Uint8*>(SDL_malloc(physicalSize));
				}else{
					buffer = reinterpret_cast<Uint8*>(SDL_realloc(buffer, physicalSize));
				}
			}else{
				size = 0;
				physicalSize = 0;
				freeBuffer();
			}
		}
		void clear(){
			if (size>0){
				SDL_memset(buffer, 0, physicalSize);
			}
		}
		Uint8 * buffer;
		size_t physicalSize;
		size_t size;
		volatile size_t pos;
		SDL_AudioFormat format;
		lua_AudioBufferGet getValue;
		lua_AudioBufferSet setValue;
	};
	
	class Lua_SDL_AudioBuffer;
	typedef int (Lua_SDL_AudioBuffer::*lua_AudioBufferMethod)(lutok::state & , AudioBuffer *);

	class Lua_SDL_AudioBuffer : public LObject<Lua_SDL_AudioBuffer, AudioBuffer *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_AudioBuffer, AudioBuffer *, "AudioBuffer") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_AudioBuffer, "clear", clearBuffer);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_AudioBuffer, "getData", getData);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_AudioBuffer, "setData", setData);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioBuffer, AudioBuffer *, "size", getLen, setLen);	
			//LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioBuffer, AudioBuffer *, "data", getDataTable, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioBuffer, AudioBuffer *, "format", getFormat, setFormat);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_AudioBuffer, AudioBuffer *, "pos", getPos, setPos);	
		}

		void destructor(lutok::state & state, AudioBuffer * audiobuffer){
			delete audiobuffer;
		}

		int inline LOBJECT_METHOD(clearBuffer, AudioBuffer * audiobuffer){
			audiobuffer->clear();
			return 0;
		}
		int inline LOBJECT_METHOD(getFormat, AudioBuffer * audiobuffer){
			state.push_integer(audiobuffer->format);
			return 1;
		}
		int LOBJECT_METHOD(setFormat, AudioBuffer * audiobuffer){
			int newformat = state.to_integer(1);
			setAudioBufferFormat(audiobuffer, newformat);			
			return 0;
		}
		int inline LOBJECT_METHOD(getPos, AudioBuffer * audiobuffer){
			state.push_integer(audiobuffer->pos);
			return 1;
		}
		int LOBJECT_METHOD(setPos, AudioBuffer * audiobuffer){
			audiobuffer->pos = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getLen, AudioBuffer * audiobuffer){
			state.push_integer(audiobuffer->size);
			return 1;
		}
		int LOBJECT_METHOD(setLen, AudioBuffer * audiobuffer){
			Uint32 newlen = state.to_integer(1);

			if ((newlen != audiobuffer->size) && (newlen>=0)){
				audiobuffer->setSize(newlen, getFormatElementSize(audiobuffer->format));
				audiobuffer->pos = 0;
			}
			return 0;
		}
		/*
		static int _getDataTable(lutok::state & state){
			Lua_SDL_AudioBuffer * thisobj = (Lua_SDL_AudioBuffer *)(state.to_lightuserdata(1));
			lua_AudioBufferMethod method = (lua_AudioBufferMethod)((void*)(state.to_lightuserdata(2)));
			AudioBuffer * audiobuffer = (AudioBuffer *)(state.to_lightuserdata(3));
			return (thisobj->*(method))(state, audiobuffer);
		}
		*/
		/*
		int LOBJECT_METHOD(getDataTable, AudioBuffer * audiobuffer){


			state.new_table();
			state.new_table();
				state.push_literal("__index");

				state.push_lightuserdata(this);
				state.push_lightuserdata(static_cast<void*>((lua_AudioBufferMethod)&LuaSDL::Lua_SDL_AudioBuffer::getData));
				state.push_lightuserdata(audiobuffer);
				state.push_cxx_closure(_getDataTable, 3);
				state.set_table();
				state.push_literal("__newindex");

				state.push_lightuserdata(this);
				state.push_lightuserdata((lua_AudioBufferMethod)&LuaSDL::Lua_SDL_AudioBuffer::setData);
				state.push_lightuserdata(audiobuffer);
				state.push_cxx_closure(_getDataTable, 3);
				state.set_table();
			state.set_metatable();
			return 1;
		}
		*/
		int LOBJECT_METHOD(getData, AudioBuffer * audiobuffer){
			if (state.is_number(1)){
				size_t index = state.to_integer(1);
				if ((index >= 0) && (index < audiobuffer->size)){
					if (audiobuffer->getValue){
						audiobuffer->getValue(state, audiobuffer->buffer, index);
						return 1;
					}else{
						return 0;
					}
				}else{
					return 0;
				}
			}else{
				state.new_table();
				for (size_t index=0; index < audiobuffer->size; index++){
					state.push_integer(index+1);
					audiobuffer->getValue(state, audiobuffer->buffer, index);
					state.set_table();
				}
				return 1;
			}
		}
		int LOBJECT_METHOD(setData, AudioBuffer * audiobuffer){
			if (state.is_number(1)){
				size_t index = state.to_integer(1);
				if ((index >= 0) && (index < audiobuffer->size)){
					if (audiobuffer->setValue){
						audiobuffer->setValue(state, audiobuffer->buffer, index, 2);
					}
				}
			}else if (state.is_table(1)){
				size_t items = state.obj_len(1);
				size_t offset = 0;
				size_t max_items = items;
				if (state.is_number(2)){
					offset = state.to_integer(2);
					if (offset<0){
						offset = 0;
					}
				}
				if (state.is_number(3)){
					max_items = state.to_integer(3);
					if (max_items<0){
						max_items = 0;
					}
				}
				if (offset+max_items > audiobuffer->size){
					audiobuffer->setSize(offset+max_items, getFormatElementSize(audiobuffer->format));
				}
				for (size_t index=0; index < max_items; index++){
					state.push_integer(index+1);
					state.get_table(1);
					audiobuffer->setValue(state, audiobuffer->buffer, index+offset, -1);
					state.pop(1);
				}
				state.push_integer(max_items);
				return 1;
			}
			return 0;
		}

		static size_t getFormatElementSize(int format){
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

		static bool setAudioBufferFormat(AudioBuffer * audiobuffer, int format);
	};
}

#endif
