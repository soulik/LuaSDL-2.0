#include "objects/surface.hpp"
#include <lua.hpp>

static int lua_SDL_CreateRGBSurface(lutok::state& state){
	LuaSDL::Lua_SDL_Surface * s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	SDL_Surface * surface = SDL_CreateRGBSurface (
			state.to_integer(1),
			state.to_integer(2),
			state.to_integer(3),
			state.to_integer(4),
			state.to_integer(5),
			state.to_integer(6),
			state.to_integer(7),
			state.to_integer(8)
		);
	if (surface){
		s->push(surface);
		return 1;
	}else{
		return 0;
	}
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(blit, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Surface * s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	state.push_boolean(
		SDL_BlitSurface(
			surface,
			(!state.is_nil(1)) ? r->check(1) : NULL,
			s->check(2),
			(!state.is_nil(3)) ? r->check(3) : NULL) == 0);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(upperBlit, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Surface * s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	state.push_boolean(
		SDL_UpperBlit(
			surface,
			(!state.is_nil(1)) ? r->check(1) : NULL,
			s->check(2),
			(!state.is_nil(3)) ? r->check(3) : NULL) == 0);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(lowerBlit, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Surface * s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	state.push_boolean(
		SDL_LowerBlit(
			surface,
			(!state.is_nil(1)) ? r->check(1) : NULL,
			s->check(2),
			(!state.is_nil(3)) ? r->check(3) : NULL) == 0);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(softStretch, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Surface * s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	state.push_boolean(
		SDL_SoftStretch(
			surface,
			(!state.is_nil(1)) ? r->check(1) : NULL,
			s->check(2),
			(!state.is_nil(3)) ? r->check(3) : NULL) == 0);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(convert, SDL_Surface * surface){
	LuaSDL::Lua_SDL_PixelFormat * pf = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_PixelFormat);
	LuaSDL::Lua_SDL_Surface * s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);

	SDL_Surface * new_surface = SDL_ConvertSurface(surface, pf->check(1), state.to_integer(2));
	if (new_surface){
		s->push(new_surface);
		return 1;
	}else{
		return 0;
	}
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(fillRect, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	state.push_boolean(SDL_FillRect(surface, r->check(1), state.to_integer(2)) == 0);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(getClipRect, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	SDL_Rect * rect = new SDL_Rect;
	SDL_GetClipRect(surface, rect);
	r->push(rect);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(setClipRect, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	state.push_boolean(
		SDL_SetClipRect(
			surface,
			(!state.is_nil(1)) ? r->check(1) : NULL) == SDL_TRUE);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(getFormat, SDL_Surface * surface){
	LuaSDL::Lua_SDL_PixelFormat * pf = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_PixelFormat);

	pf->push(surface->format, false);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(setFormat, SDL_Surface * surface){
	LuaSDL::Lua_SDL_PixelFormat * pf = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_PixelFormat);
	
	SDL_PixelFormat * format = pf->check(1);
	if (format){
		surface->format->format = format->format;
		surface->format->palette = format->palette;
		surface->format->BitsPerPixel = format->BitsPerPixel;
		surface->format->BytesPerPixel = format->BytesPerPixel;
		surface->format->Rmask = format->Rmask;
		surface->format->Gmask = format->Gmask;
		surface->format->Bmask = format->Bmask;
		surface->format->Amask = format->Amask;

		surface->format->Rloss = format->Rloss;
		surface->format->Gloss = format->Gloss;
		surface->format->Bloss = format->Bloss;
		surface->format->Aloss = format->Aloss;
		surface->format->Rshift = format->Rshift;
		surface->format->Gshift = format->Gshift;
		surface->format->Bshift = format->Bshift;
		surface->format->Ashift = format->Ashift;
	}
	return 0;
}

static int lua_SDL_ConvertPixels(lutok::state& state){
	state.push_boolean(SDL_ConvertPixels(
			state.to_integer(1),
			state.to_integer(2),
			state.to_integer(3),
			state.to_lightuserdata(4),
			state.to_integer(5),
			state.to_integer(6),
			(void*)state.to_lightuserdata(7),
			state.to_integer(8)
		) == 0);
	return 1;
}

void LuaSDL::init_surface(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	module["createRGBSurface"] = lua_SDL_CreateRGBSurface;
	module["convertPixels"] = lua_SDL_ConvertPixels;
}
