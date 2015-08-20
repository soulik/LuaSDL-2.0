#ifndef LUA_SDL_OBJECTS_TEXTURE_H
#define LUA_SDL_OBJECTS_TEXTURE_H

#include "common.hpp"

namespace LuaSDL {

	class Texture : public Object<SDL_Texture> {
	public:
		explicit Texture(State * state) : Object<SDL_Texture>(state){
			LUTOK_METHOD("lock", &Texture::lock);
			LUTOK_METHOD("unlock", &Texture::unlock);
			LUTOK_METHOD("update", &Texture::update);
			LUTOK_METHOD("query", &Texture::query);


			LUTOK_PROPERTY("alphaMod", &Texture::getAlphaMod, &Texture::setAlphaMod);
			LUTOK_PROPERTY("colorMod", &Texture::getColorMod, &Texture::setColorMod);
			LUTOK_PROPERTY("blendMode", &Texture::getBlendMode, &Texture::setBlendMode);

		}

		void destructor(State & state, SDL_Texture * texture){
			SDL_DestroyTexture(texture);
		}

		int lock(State & state, SDL_Texture * texture);
		int unlock(State & state, SDL_Texture * texture);
		int update(State & state, SDL_Texture * texture);

		int query(State & state, SDL_Texture  * texture){
			Stack * stack = state.stack;
			Uint32 format;
			int access;
			int w,h;

			if (SDL_QueryTexture(texture, &format, &access, &w, &h)==0){
				stack->push<int>(format);
				stack->push<int>(access);
				stack->push<int>(w);
				stack->push<int>(h);
				return 4;
			}else{
				return 0;
			}
		}

		int getAlphaMod(State & state, SDL_Texture  * texture){
			Uint8 alpha;
			if (SDL_GetTextureAlphaMod(texture, &alpha)==0){
				state.stack->push<int>(alpha);
				return 1;
			}else{
				return 0;
			}

		}
		int setAlphaMod(State & state, SDL_Texture  * texture){
			SDL_SetTextureAlphaMod(texture, (Uint8)state.stack->to<LUA_NUMBER>(1));
			return 0;
		}
		int getColorMod(State & state, SDL_Texture  * texture){
			Uint8 r,g,b;
			Stack * stack = state.stack;
			if (SDL_GetTextureColorMod(texture, &r, &g, &b)==0){
				stack->newTable();
				stack->setField("r", (const int)r);
				stack->setField("g", (const int)g);
				stack->setField("b", (const int)b);
				return 1;
			}else{
				return 0;
			}

		}
		int setColorMod(State & state, SDL_Texture  * texture){
			Stack * stack = state.stack;
			if (stack->is<LUA_TTABLE>(1)){
				Uint8 r,g,b;
				stack->getField("r", 1);
				stack->getField("g", 1);
				stack->getField("b", 1);
				r = (Uint8)stack->to<int>(-3);
				g = (Uint8)stack->to<int>(-2);
				b = (Uint8)stack->to<int>(-1);
				stack->pop(3);

				SDL_SetTextureColorMod(texture, r,g,b);

			}
			return 0;
		}
		int getBlendMode(State & state, SDL_Texture  * texture){
			SDL_BlendMode mode;
			if (SDL_GetTextureBlendMode(texture, &mode)==0){
				state.stack->push<int>(mode);
				return 1;
			}else{
				return 0;
			}

		}
		int setBlendMode(State & state, SDL_Texture  * texture){
			SDL_SetTextureBlendMode(texture, (SDL_BlendMode)state.stack->to<int>(1));
			return 0;
		}
	};
}

#endif
