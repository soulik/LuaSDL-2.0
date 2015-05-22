#include "objects/surface.hpp"
#include "objects/rect.hpp"
#include "objects/cursor.hpp"
#include "objects/pixelformat.hpp"
#include "objects/renderer.hpp"

#include <lua.hpp>

static int lua_SDL_CreateRGBSurface(State & state){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	SDL_Surface * surface = SDL_CreateRGBSurface (
			stack->to<int>(1),
			stack->to<int>(2),
			stack->to<int>(3),
			stack->to<int>(4),
			stack->to<int>(5),
			stack->to<int>(6),
			stack->to<int>(7),
			stack->to<int>(8)
		);
	if (surface){
		s.push(surface);
		return 1;
	}else{
		return 0;
	}
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(blit, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	stack->push<bool>(
		SDL_BlitSurface(
			surface,
			(!stack->is<LUA_TNIL>(1)) ? r.check(1) : NULL,
			s.check(2),
			(!stack->is<LUA_TNIL>(3)) ? r.check(3) : NULL) == 0);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(upperBlit, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	stack->push<bool>(
		SDL_UpperBlit(
			surface,
			(!stack->is<LUA_TNIL>(1)) ? r.check(1) : NULL,
			s.check(2),
			(!stack->is<LUA_TNIL>(3)) ? r.check(3) : NULL) == 0);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(lowerBlit, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	stack->push<bool>(
		SDL_LowerBlit(
			surface,
			(!stack->is<LUA_TNIL>(1)) ? r.check(1) : NULL,
			s.check(2),
			(!stack->is<LUA_TNIL>(3)) ? r.check(3) : NULL) == 0);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(softStretch, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	stack->push<bool>(
		SDL_SoftStretch(
			surface,
			(!stack->is<LUA_TNIL>(1)) ? r.check(1) : NULL,
			s.check(2),
			(!stack->is<LUA_TNIL>(3)) ? r.check(3) : NULL) == 0);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(convert, SDL_Surface * surface){
	LuaSDL::Lua_SDL_PixelFormat & pf = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_PixelFormat);
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	
	Uint32 flags;
	if (stack->is<LUA_TNUMBER>(2)){
		flags = stack->to<int>(2);
	}else{
		flags = 0;
	}

	SDL_Surface * new_surface = SDL_ConvertSurface(surface, pf.check(1), flags);
	if (new_surface){
		s.push(new_surface);
		return 1;
	}else{
		return 0;
	}
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(getRawPixels, SDL_Surface * surface){
	Uint32 position = stack->to<int>(1);
	Uint8 pixel = ((Uint8*)surface->pixels)[position];
	stack->push<int>(pixel);
	return 1;
}
/*
	setRawPixels32(table)
*/

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(setRawPixels32, SDL_Surface * surface){
	size_t size=0;
	unsigned int * data;
	std::vector<unsigned int> _data;

	if (stack->is<LUA_TTABLE>(1)){
		size = getArray<unsigned int>(state, 1, _data);
		data = _data.data();

		//fix buffer overflow
		size_t max_size = surface->format->BytesPerPixel*surface->w*surface->h;
		size_t final_size = (size*sizeof(unsigned int) <= max_size) ? size*sizeof(unsigned int) : max_size;

		if (SDL_MUSTLOCK(surface)){
			if (SDL_LockSurface(surface) == 0){
				memcpy(surface->pixels, data, final_size);
				SDL_UnlockSurface(surface);
				stack->push<bool>(true);
			}else{
				stack->push<bool>(false);
			}
		}else{
			memcpy(surface->pixels, data, final_size);
			stack->push<bool>(true);
		}
	}else{
		stack->push<bool>(false);
	}
	return 1;
}

/*
	setRawPixels8(table)
*/

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(setRawPixels8, SDL_Surface * surface){
	size_t size=0;
	unsigned char * data;
	std::vector<unsigned char> _data;

	if (stack->is<LUA_TTABLE>(1)){
		size = getArray<unsigned char>(state, 1, _data);
		data = _data.data();

		//fix buffer overflow
		size_t max_size = surface->format->BytesPerPixel*surface->w*surface->h;
		size_t final_size = (size*sizeof(unsigned char) <= max_size) ? size*sizeof(unsigned char) : max_size;

		if (SDL_MUSTLOCK(surface)){
			if (SDL_LockSurface(surface) == 0){
				memcpy(surface->pixels, data, final_size);
				SDL_UnlockSurface(surface);
				stack->push<bool>(true);
			}else{
				stack->push<bool>(false);
			}
		}else{
			memcpy(surface->pixels, data, final_size);
			stack->push<bool>(true);
		}
	}else{
		stack->push<bool>(false);
	}
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(fillRect, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	if (stack->is<LUA_TNIL>(1)){
		stack->push<bool>(SDL_FillRect(surface, NULL, stack->to<int>(2)) == 0);
	}else{
		stack->push<bool>(SDL_FillRect(surface, r.check(1), stack->to<int>(2)) == 0);
	}
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(getClipRect, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	SDL_Rect * rect = new SDL_Rect;
	SDL_GetClipRect(surface, rect);
	r.push(rect);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(setClipRect, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	stack->push<bool>(
		SDL_SetClipRect(
			surface,
			(!stack->is<LUA_TNIL>(1)) ? r.check(1) : NULL) == SDL_TRUE);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(getFormat, SDL_Surface * surface){
	LuaSDL::Lua_SDL_PixelFormat & pf = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_PixelFormat);

	pf.push(surface->format, false);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(setFormat, SDL_Surface * surface){
	LuaSDL::Lua_SDL_PixelFormat & pf = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_PixelFormat);
	
	SDL_PixelFormat * format = pf.check(1);
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

static int lua_SDL_ConvertPixels(State & state){
	stack->push<bool>(SDL_ConvertPixels(
			stack->to<int>(1),
			stack->to<int>(2),
			stack->to<int>(3),
			state.to_lightuserdata(4),
			stack->to<int>(5),
			stack->to<int>(6),
			(void*)state.to_lightuserdata(7),
			stack->to<int>(8)
		) == 0);
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(createColorCursor, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Cursor & c = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Cursor);
	c.push(
		SDL_CreateColorCursor(
			surface,
			stack->to<int>(1),
			stack->to<int>(2)));
	return 1;
}

int LuaSDL::Lua_SDL_Surface::LOBJECT_METHOD(createSoftwareRenderer, SDL_Surface * surface){
	LuaSDL::Lua_SDL_Renderer & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Renderer);

	SDL_Renderer * renderer = SDL_CreateSoftwareRenderer(surface);
	if (renderer){
		r.push(renderer);
		return 1;
	}else{
		return 0;
	}
}

void LuaSDL::init_surface(State & state, Module & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	module["createRGBSurface"] = lua_SDL_CreateRGBSurface;
	module["convertPixels"] = lua_SDL_ConvertPixels;
}
