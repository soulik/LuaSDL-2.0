#ifndef LUA_SDL_OBJECTS_TEXTURE_H
#define LUA_SDL_OBJECTS_TEXTURE_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_Texture : public LObject<Lua_SDL_Texture, SDL_Texture  *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_Texture, SDL_Texture *, "Renderer") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Texture, "lock", lock);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Texture, "unlock", unlock);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Texture, "update", update);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Texture, "query", query);


			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Texture, SDL_Texture *, "alphaMod", getAlphaMod, setAlphaMod);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Texture, SDL_Texture *, "colorMod", getColorMod, setColorMod);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Texture, SDL_Texture *, "blendMode", getBlendMode, setBlendMode);	

		}

		void destructor(lutok::state & s, SDL_Texture * texture){
			SDL_DestroyTexture(texture);
		}
		int LOBJECT_METHOD(lock, SDL_Texture * texture);
		int LOBJECT_METHOD(unlock, SDL_Texture * texture);
		int LOBJECT_METHOD(update, SDL_Texture * texture);

		int LOBJECT_METHOD(query, SDL_Texture * texture){
			Uint32 format;
			int access;
			int w,h;

			if (SDL_QueryTexture(texture, &format, &access, &w, &h)==0){
				state.push_integer(format);
				state.push_integer(access);
				state.push_integer(w);
				state.push_integer(h);
				return 4;
			}else{
				return 0;
			}
		}

		int LOBJECT_METHOD(getAlphaMod, SDL_Texture * texture){
			Uint8 alpha;
			if (SDL_GetTextureAlphaMod(texture, &alpha)==0){
				state.push_integer(alpha);
				return 1;
			}else{
				return 0;
			}

		}
		int LOBJECT_METHOD(setAlphaMod, SDL_Texture * texture){
			SDL_SetTextureAlphaMod(texture, (Uint8)state.to_integer(1));
			return 0;
		}
		int LOBJECT_METHOD(getColorMod, SDL_Texture * texture){
			Uint8 r,g,b;
			if (SDL_GetTextureColorMod(texture, &r, &g, &b)==0){
				state.new_table();
				state.set_field("r", (const int)r);
				state.set_field("g", (const int)g);
				state.set_field("b", (const int)b);
				return 1;
			}else{
				return 0;
			}

		}
		int LOBJECT_METHOD(setColorMod, SDL_Texture * texture){
			if (state.is_table(1)){
				Uint8 r,g,b;
				state.get_field(1, "r");
				state.get_field(1, "g");
				state.get_field(1, "b");
				r = (Uint8)state.to_integer(-3);
				g = (Uint8)state.to_integer(-2);
				b = (Uint8)state.to_integer(-1);
				state.pop(3);

				SDL_SetTextureColorMod(texture, r,g,b);

			}
			return 0;
		}
		int LOBJECT_METHOD(getBlendMode, SDL_Texture * texture){
			SDL_BlendMode mode;
			if (SDL_GetTextureBlendMode(texture, &mode)==0){
				state.push_integer(mode);
				return 1;
			}else{
				return 0;
			}

		}
		int LOBJECT_METHOD(setBlendMode, SDL_Texture * texture){
			SDL_SetTextureBlendMode(texture, (SDL_BlendMode)state.to_integer(1));
			return 0;
		}
	};
}

#endif
