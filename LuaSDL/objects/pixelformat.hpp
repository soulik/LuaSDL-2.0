#ifndef LUA_SDL_OBJECTS_PIXELFORMAT_H
#define LUA_SDL_OBJECTS_PIXELFORMAT_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_PixelFormat : public LObject<Lua_SDL_PixelFormat, SDL_PixelFormat*> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_PixelFormat, SDL_PixelFormat*, "PixelFormat") {

			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_PixelFormat, "getRGB", getRGB);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_PixelFormat, "getRGBA", getRGBA);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_PixelFormat, "mapRGB", mapRGB);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_PixelFormat, "mapRGBA", mapRGBA);

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "format", getName, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "format", getFormat, setFormat);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "BitsPerPixel", getBitsPerPixel, setBitsPerPixel);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "BytesPerPixel", getBytesPerPixel, setBytesPerPixel);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "Rmask", getRmask, setRmask);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "Gmask", getGmask, setGmask);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "Bmask", getBmask, setBmask);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "Amask", getAmask, setAmask);	
		}

		void destructor(SDL_PixelFormat * pixelformat){
			SDL_FreeFormat(pixelformat);
		}

		int inline LOBJECT_METHOD(mapRGB, SDL_PixelFormat * format){
			state.push_integer(
				SDL_MapRGB(
					format,
					(Uint8)state.to_integer(1),
					(Uint8)state.to_integer(2),
					(Uint8)state.to_integer(3)
					));

			return 1;
		}

		int inline LOBJECT_METHOD(mapRGBA, SDL_PixelFormat * format){
			state.push_integer(
				SDL_MapRGBA(
					format,
					(Uint8)state.to_integer(1),
					(Uint8)state.to_integer(2),
					(Uint8)state.to_integer(3),
					(Uint8)state.to_integer(4)
					));

			return 1;
		}

		int inline LOBJECT_METHOD(getRGB, SDL_PixelFormat * format){
			Uint8 r,g,b;

			SDL_GetRGB(
				state.to_integer(1),
				format,
				&r,&g,&b);

			state.push_integer(r);
			state.push_integer(g);
			state.push_integer(b);
			return 3;
		}

		int inline LOBJECT_METHOD(getRGBA, SDL_PixelFormat * format){
			Uint8 r,g,b,a;

			SDL_GetRGBA(
				state.to_integer(1),
				format,
				&r,&g,&b,&a);

			state.push_integer(r);
			state.push_integer(g);
			state.push_integer(b);
			state.push_integer(a);
			return 4;
		}

		int inline LOBJECT_METHOD(getName, SDL_PixelFormat * format){
			state.push_string(SDL_GetPixelFormatName(format->format));
			return 1;
		}

		int inline LOBJECT_METHOD(getFormat, SDL_PixelFormat * format){
			state.push_integer(format->format);
			return 1;
		}

		int inline LOBJECT_METHOD(setFormat, SDL_PixelFormat * format){
			format->format = state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getBitsPerPixel, SDL_PixelFormat * format){
			state.push_integer(format->BitsPerPixel);
			return 1;
		}

		int inline LOBJECT_METHOD(setBitsPerPixel, SDL_PixelFormat * format){
			format->BitsPerPixel = (Uint8)state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getBytesPerPixel, SDL_PixelFormat * format){
			state.push_integer(format->BytesPerPixel);
			return 1;
		}

		int inline LOBJECT_METHOD(setBytesPerPixel, SDL_PixelFormat * format){
			format->BytesPerPixel = (Uint8)state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getRmask, SDL_PixelFormat * format){
			state.push_integer(format->Rmask);
			return 1;
		}

		int inline LOBJECT_METHOD(setRmask, SDL_PixelFormat * format){
			format->Rmask = state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getGmask, SDL_PixelFormat * format){
			state.push_integer(format->Gmask);
			return 1;
		}

		int inline LOBJECT_METHOD(setGmask, SDL_PixelFormat * format){
			format->Gmask = state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getBmask, SDL_PixelFormat * format){
			state.push_integer(format->Bmask);
			return 1;
		}

		int inline LOBJECT_METHOD(setBmask, SDL_PixelFormat * format){
			format->Bmask = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getAmask, SDL_PixelFormat * format){
			state.push_integer(format->Amask);
			return 1;
		}
		int inline LOBJECT_METHOD(setAmask, SDL_PixelFormat * format){
			format->Amask = state.to_integer(1);
			return 0;
		}
	};
}

#endif