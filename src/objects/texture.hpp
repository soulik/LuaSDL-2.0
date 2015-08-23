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

			LUTOK_METHOD("bind", &Texture::bind);
			LUTOK_METHOD("unbind", &Texture::unbind);

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

		int bind(State & state, SDL_Texture  * texture);
		int unbind(State & state, SDL_Texture  * texture);

		int query(State & state, SDL_Texture  * texture);

		int getAlphaMod(State & state, SDL_Texture  * texture);
		int setAlphaMod(State & state, SDL_Texture  * texture);
		int getColorMod(State & state, SDL_Texture  * texture);
		int setColorMod(State & state, SDL_Texture  * texture);
		int getBlendMode(State & state, SDL_Texture  * texture);
		int setBlendMode(State & state, SDL_Texture  * texture);
	};
}

#endif
