#include "objects/texture.hpp"
#include "objects/rect.hpp"
#include <lua.hpp>
/*
static int lua_Mix_LoadWAV(lutok::state& state){
	//LuaSDL::Lua_SDL_MixChunk * c = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_MixChunk);

	return 0;
}
*/

int LOBJECT_METHOD(LuaSDL::Lua_SDL_Texture::lock, SDL_Texture * texture){
	SDL_Rect * rect;
	int pitch;
	void * pixels;

	if (!state.is_nil(1)){
		LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
		rect = r.check(1);
		if (rect){
			if (SDL_LockTexture(texture, rect, &pixels, &pitch) == 0){
				state.push_lightuserdata(pixels);
				state.push_integer(pitch);
				return 2;
			}else{
				state.push_boolean(false);
			}
			return 1;
		}
	}
	return 0;
}
int LOBJECT_METHOD(LuaSDL::Lua_SDL_Texture::unlock, SDL_Texture * texture){
	SDL_UnlockTexture(texture);
	return 0;
}
int LOBJECT_METHOD(LuaSDL::Lua_SDL_Texture::update, SDL_Texture * texture){
	SDL_Rect * rect = NULL;
	int pitch;
	const void * pixels;

	if (state.is_userdata(2) && state.is_number(3)){
		LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
		if (!state.is_nil(1)){
			rect = r.check(1);
		}
		pixels = state.to_lightuserdata(2);
		pitch = state.to_integer(3);

		if (rect && pixels){
			int result = SDL_UpdateTexture(texture, rect, &pixels, pitch);
			state.push_boolean(result == 0);
			return 1;
		}
	}
	return 0;
}

void LuaSDL::init_texture(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Texture);
	//module["mixerLoadWAV"] = lua_Mix_LoadWAV;
}
