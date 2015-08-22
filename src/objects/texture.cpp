#include "objects/texture.hpp"
#include "objects/rect.hpp"

namespace LuaSDL {

	int Texture::lock(State & state, SDL_Texture * texture){
		Stack * stack = state.stack;
		SDL_Rect * rect;
		int pitch;
		void * pixels;

		if (stack->is<LUA_TUSERDATA>(1)){
			Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
			rect = interfaceRect->get(1);
			if (rect){
				if (SDL_LockTexture(texture, rect, &pixels, &pitch) == 0){
					stack->push<void*>(pixels);
					stack->push<int>(pitch);
					return 2;
				}
				else{
					stack->push<bool>(false);
				}
				return 1;
			}
		}
		return 0;
	}

	int Texture::unlock(State & state, SDL_Texture * texture){
		SDL_UnlockTexture(texture);
		return 0;
	}
	int Texture::update(State & state, SDL_Texture * texture){
		Stack * stack = state.stack;
		SDL_Rect * rect = NULL;
		int pitch;
		const void * pixels;

		if (stack->is<LUA_TUSERDATA>(2) && stack->is<LUA_TNUMBER>(3)){
			Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
			if (!stack->is<LUA_TNIL>(1)){
				rect = interfaceRect->get(1);
			}
			pixels = stack->to<void*>(2);
			pitch = stack->to<int>(3);

			if (rect && pixels){
				int result = SDL_UpdateTexture(texture, rect, &pixels, pitch);
				stack->push<bool>(result == 0);
				return 1;
			}
		}
		return 0;
	}

	int Texture::query(State & state, SDL_Texture  * texture){
		Stack * stack = state.stack;
		Uint32 format;
		int access;
		int w, h;

		if (SDL_QueryTexture(texture, &format, &access, &w, &h) == 0){
			stack->push<int>(format);
			stack->push<int>(access);
			stack->push<int>(w);
			stack->push<int>(h);
			return 4;
		}
		else{
			return 0;
		}
	}

	int Texture::getAlphaMod(State & state, SDL_Texture  * texture){
		Uint8 alpha;
		if (SDL_GetTextureAlphaMod(texture, &alpha) == 0){
			state.stack->push<int>(alpha);
			return 1;
		}
		else{
			return 0;
		}

	}
	int Texture::setAlphaMod(State & state, SDL_Texture  * texture){
		SDL_SetTextureAlphaMod(texture, (Uint8)state.stack->to<LUA_NUMBER>(1));
		return 0;
	}
	int Texture::getColorMod(State & state, SDL_Texture  * texture){
		Uint8 r, g, b;
		Stack * stack = state.stack;
		if (SDL_GetTextureColorMod(texture, &r, &g, &b) == 0){
			stack->newTable();
			stack->setField("r", (const int)r);
			stack->setField("g", (const int)g);
			stack->setField("b", (const int)b);
			return 1;
		}
		else{
			return 0;
		}

	}
	int Texture::setColorMod(State & state, SDL_Texture  * texture){
		Stack * stack = state.stack;
		if (stack->is<LUA_TTABLE>(1)){
			Uint8 r, g, b;
			stack->getField("r", 1);
			stack->getField("g", 1);
			stack->getField("b", 1);
			r = (Uint8)stack->to<int>(-3);
			g = (Uint8)stack->to<int>(-2);
			b = (Uint8)stack->to<int>(-1);
			stack->pop(3);

			SDL_SetTextureColorMod(texture, r, g, b);

		}
		return 0;
	}
	int Texture::getBlendMode(State & state, SDL_Texture  * texture){
		SDL_BlendMode mode;
		if (SDL_GetTextureBlendMode(texture, &mode) == 0){
			state.stack->push<int>(mode);
			return 1;
		}
		else{
			return 0;
		}

	}
	int Texture::setBlendMode(State & state, SDL_Texture  * texture){
		SDL_SetTextureBlendMode(texture, (SDL_BlendMode)state.stack->to<int>(1));
		return 0;
	}

	void initTexture(State * state, Module & module){
		INIT_OBJECT(Texture);
	}
}