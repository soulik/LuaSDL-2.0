#ifndef LUA_SDL_OBJECTS_SURFACE_H
#define LUA_SDL_OBJECTS_SURFACE_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_Surface : public LObject<Lua_SDL_Surface, SDL_Surface*> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_Surface, SDL_Surface*, "Surface") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Surface, "createSoftwareRenderer", createSoftwareRenderer);
			
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Surface, "blit", blit);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Surface, "lowerBlit", lowerBlit);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Surface, "upperBlit", upperBlit);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Surface, "softStretch", softStretch);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Surface, "convert", convert);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Surface, "convertFormat", convertFormat);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Surface, "fillRect", fillRect);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Surface, "lock", lock);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Surface, "unlock", unlock);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Surface, "createColorCursor", createColorCursor);

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Surface, SDL_Surface*, "format", getFormat, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Surface, SDL_Surface*, "w", getW, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Surface, SDL_Surface*, "h", getH, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Surface, SDL_Surface*, "pitch", getPitch, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Surface, SDL_Surface*, "clipRect", getClipRect, setClipRect);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Surface, SDL_Surface*, "refcount", getRefCount, setRefCount);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Surface, SDL_Surface*, "pixels", getPixels, setPixels);	

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Surface, SDL_Surface*, "colorKey", getColorKey, setColorKey);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Surface, SDL_Surface*, "alphaMod", getAlphaMod, setAlphaMod);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Surface, SDL_Surface*, "blendMode", getBlendMode, setBlendMode);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Surface, SDL_Surface*, "colorMod", getColorMod, setColorMod);	

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Surface, SDL_Surface*, "RLE", null_method, setRLE);	

		}

		void destructor(lutok::state & s, SDL_Surface* surface){
			SDL_FreeSurface(surface);
		}

		int LOBJECT_METHOD(createSoftwareRenderer, SDL_Surface * surface);

		int LOBJECT_METHOD(blit, SDL_Surface * surface);
		int LOBJECT_METHOD(lowerBlit, SDL_Surface * surface);
		int LOBJECT_METHOD(upperBlit, SDL_Surface * surface);
		int LOBJECT_METHOD(softStretch, SDL_Surface * surface);
		int LOBJECT_METHOD(convert, SDL_Surface * surface);

		int LOBJECT_METHOD(convertFormat, SDL_Surface * surface){
			Lua_SDL_Surface * s = LOBJECT_INSTANCE(Lua_SDL_Surface);

			SDL_Surface * new_surface = SDL_ConvertSurfaceFormat(surface, state.to_integer(1), state.to_integer(2));
			if (new_surface){
				s->push(new_surface);
				return 1;
			}else{
				return 0;
			}
		}

		int LOBJECT_METHOD(fillRect, SDL_Surface * surface);
		int LOBJECT_METHOD(getClipRect, SDL_Surface * surface);
		int LOBJECT_METHOD(setClipRect, SDL_Surface * surface);
		int LOBJECT_METHOD(getFormat, SDL_Surface * surface);
		int LOBJECT_METHOD(setFormat, SDL_Surface * surface);

		int inline LOBJECT_METHOD(lock, SDL_Surface * surface){
			state.push_boolean(SDL_LockSurface(surface) == 0);
			return 1;
		}
		int inline LOBJECT_METHOD(unlock, SDL_Surface * surface){
			SDL_UnlockSurface(surface);
			return 0;
		}

		int LOBJECT_METHOD(createColorCursor, SDL_Surface * surface);

		int inline LOBJECT_METHOD(getW, SDL_Surface * surface){
			state.push_integer(surface->w);
			return 1;
		}
		int inline LOBJECT_METHOD(getH, SDL_Surface * surface){
			state.push_integer(surface->h);
			return 1;
		}
		int inline LOBJECT_METHOD(getPitch, SDL_Surface * surface){
			state.push_integer(surface->pitch);
			return 1;
		}
		int inline LOBJECT_METHOD(getPixels, SDL_Surface * surface){
			state.push_lightuserdata(surface->pixels);
			return 1;
		}
		int inline LOBJECT_METHOD(setPixels, SDL_Surface * surface){
			surface->pixels = (void*)state.to_lightuserdata(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getRefCount, SDL_Surface * surface){
			state.push_integer(surface->refcount);
			return 1;
		}
		int inline LOBJECT_METHOD(setRefCount, SDL_Surface * surface){
			surface->refcount = state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getColorKey, SDL_Surface * surface){
			Uint32 colorKey;
			if (SDL_GetColorKey(surface, &colorKey) == 0){
				state.push_integer(colorKey);
				return 1;
			}else{
				return 0;
			}
		}
		int inline LOBJECT_METHOD(setColorKey, SDL_Surface * surface){
			if (state.is_number(1)){
				SDL_SetColorKey(surface, SDL_TRUE, state.to_integer(1));
			}else{
				SDL_SetColorKey(surface, SDL_FALSE, 0);
			}
			return 0;
		}
		int inline LOBJECT_METHOD(getAlphaMod, SDL_Surface * surface){
			Uint8 alpha;
			if (SDL_GetSurfaceAlphaMod(surface, &alpha) == 0){
				state.push_integer(alpha);
				return 1;
			}else{
				return 0;
			}
		}
		int inline LOBJECT_METHOD(setAlphaMod, SDL_Surface * surface){
			SDL_SetSurfaceAlphaMod(surface, (Uint8) state.to_integer(1));
			return 0;
		}
		int inline LOBJECT_METHOD(getBlendMode, SDL_Surface * surface){
			SDL_BlendMode blendMode;
			if (SDL_GetSurfaceBlendMode(surface, &blendMode) == 0){
				state.push_integer((int)blendMode);
				return 1;
			}else{
				return 0;
			}
		}
		int inline LOBJECT_METHOD(setBlendMode, SDL_Surface * surface){
			SDL_SetSurfaceBlendMode(surface, (SDL_BlendMode) state.to_integer(1));
			return 0;
		}
		int inline LOBJECT_METHOD(getColorMod, SDL_Surface * surface){
			Uint8 r,g,b;
			if (SDL_GetSurfaceColorMod(surface, &r, &g, &b) == 0){
				state.new_table();
					state.push_integer(r);
					state.set_field(-2,"r");
					state.push_integer(r);
					state.set_field(-2,"g");
					state.push_integer(r);
					state.set_field(-2,"b");
				return 1;
			}else{
				return 0;
			}
		}
		int inline LOBJECT_METHOD(setColorMod, SDL_Surface * surface){
			if (state.is_table(1)){
				state.get_field(1,"r");
				state.get_field(1,"g");
				state.get_field(1,"b");

				SDL_SetSurfaceColorMod(
					surface,
					(Uint8)state.to_integer(-3),
					(Uint8)state.to_integer(-2),
					(Uint8)state.to_integer(-1));
				state.pop(3);
			}
			return 0;
		}

		int inline LOBJECT_METHOD(setRLE, SDL_Surface * surface){
			SDL_SetSurfaceRLE(surface, state.to_integer(1));
			return 0;
		}
	};
}

#endif