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

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "Rloss", getRloss, setRloss);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "Gloss", getGloss, setGloss);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "Bloss", getBloss, setBloss);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "Aloss", getAloss, setAloss);	

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "Rshift", getRshift, setRshift);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "Gshift", getGshift, setGshift);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "Bshift", getBshift, setBshift);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_PixelFormat, SDL_PixelFormat*, "Ashift", getAshift, setAshift);
		}

		void destructor(lutok::state & s, SDL_PixelFormat * pixelformat){
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
			format->Rmask = (Uint8)state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getGmask, SDL_PixelFormat * format){
			state.push_integer(format->Gmask);
			return 1;
		}

		int inline LOBJECT_METHOD(setGmask, SDL_PixelFormat * format){
			format->Gmask = (Uint8)state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getBmask, SDL_PixelFormat * format){
			state.push_integer(format->Bmask);
			return 1;
		}

		int inline LOBJECT_METHOD(setBmask, SDL_PixelFormat * format){
			format->Bmask = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getAmask, SDL_PixelFormat * format){
			state.push_integer(format->Amask);
			return 1;
		}
		int inline LOBJECT_METHOD(setAmask, SDL_PixelFormat * format){
			format->Amask = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getRloss, SDL_PixelFormat * format){
			state.push_integer(format->Rloss);
			return 1;
		}
		int inline LOBJECT_METHOD(setRloss, SDL_PixelFormat * format){
			format->Rloss = (Uint8)state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getGloss, SDL_PixelFormat * format){
			state.push_integer(format->Gloss);
			return 1;
		}
		int inline LOBJECT_METHOD(setGloss, SDL_PixelFormat * format){
			format->Gloss = (Uint8)state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getBloss, SDL_PixelFormat * format){
			state.push_integer(format->Bloss);
			return 1;
		}
		int inline LOBJECT_METHOD(setBloss, SDL_PixelFormat * format){
			format->Bloss = (Uint8)state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getAloss, SDL_PixelFormat * format){
			state.push_integer(format->Aloss);
			return 1;
		}
		int inline LOBJECT_METHOD(setAloss, SDL_PixelFormat * format){
			format->Aloss = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getRshift, SDL_PixelFormat * format){
			state.push_integer(format->Rshift);
			return 1;
		}
		int inline LOBJECT_METHOD(setRshift, SDL_PixelFormat * format){
			format->Rshift = (Uint8)state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getGshift, SDL_PixelFormat * format){
			state.push_integer(format->Gshift);
			return 1;
		}
		int inline LOBJECT_METHOD(setGshift, SDL_PixelFormat * format){
			format->Gshift = (Uint8)state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getBshift, SDL_PixelFormat * format){
			state.push_integer(format->Bshift);
			return 1;
		}
		int inline LOBJECT_METHOD(setBshift, SDL_PixelFormat * format){
			format->Bshift = (Uint8)state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getAshift, SDL_PixelFormat * format){
			state.push_integer(format->Ashift);
			return 1;
		}
		int inline LOBJECT_METHOD(setAshift, SDL_PixelFormat * format){
			format->Ashift = (Uint8)state.to_integer(1);
			return 0;
		}
	};
}

#endif