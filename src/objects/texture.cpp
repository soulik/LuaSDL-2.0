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

	void initTexture(State * state, Module & module){
		state->registerInterface<Texture>("LuaSDL_Texture");
	}
}