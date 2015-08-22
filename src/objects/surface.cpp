#include "objects/surface.hpp"
#include "objects/rect.hpp"
#include "objects/cursor.hpp"
#include "objects/pixelformat.hpp"
#include "objects/renderer.hpp"

#include <lua.hpp>

namespace LuaSDL {
	static int lua_SDL_ConvertPixels(State & state){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_ConvertPixels(
			stack->to<int>(1),
			stack->to<int>(2),
			stack->to<int>(3),
			stack->to<void*>(4),
			stack->to<int>(5),
			stack->to<int>(6),
			stack->to<void*>(7),
			stack->to<int>(8)
			) == 0);
		return 1;
	}

	SDL_Surface * Surface::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		SDL_Surface * newSurface = SDL_CreateRGBSurface(
			stack->to<int>(1),
			stack->to<int>(2),
			stack->to<int>(3),
			stack->to<int>(4),
			stack->to<int>(5),
			stack->to<int>(6),
			stack->to<int>(7),
			stack->to<int>(8)
			);
		return newSurface;
	}

	int Surface::convertFormat(State & state, SDL_Surface  * surface){
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		Uint32 flags;
		if (stack->is<LUA_TNUMBER>(2)){
			flags = stack->to<int>(2);
		}
		else{
			flags = 0;
		}

		SDL_Surface * newSurface = SDL_ConvertSurfaceFormat(surface, stack->to<int>(1), flags);
		if (newSurface){
			interfaceSurface->push(newSurface, true);
			return 1;
		}
		else{
			return 0;
		}
	}

	int Surface::blit(State & state, SDL_Surface * surface){
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");

		SDL_Rect * r1 = interfaceRect->get(1);
		SDL_Rect * r2 = interfaceRect->get(3);
		SDL_Surface * destSurface = interfaceSurface->get(2);
		
		if (destSurface){
			stack->push<bool>(
				SDL_BlitSurface(
				surface,
				(r1) ? r1 : NULL,
				destSurface,
				(r2) ? r2 : NULL) == 0);
			return 1;
		}
		else{
			return 0;
		}
	}

	int Surface::upperBlit(State & state, SDL_Surface * surface){
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");

		SDL_Rect * r1 = interfaceRect->get(1);
		SDL_Rect * r2 = interfaceRect->get(3);
		SDL_Surface * destSurface = interfaceSurface->get(2);

		if (destSurface){
			stack->push<bool>(
				SDL_UpperBlit(
				surface,
				(r1) ? r1 : NULL,
				destSurface,
				(r2) ? r2 : NULL) == 0);
			return 1;

		}
		else{
			return 0;
		}
	}

	int Surface::lowerBlit(State & state, SDL_Surface * surface){
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
		
		SDL_Rect * r1 = interfaceRect->get(1);
		SDL_Rect * r2 = interfaceRect->get(3);
		SDL_Surface * destSurface = interfaceSurface->get(2);

		if (destSurface){
			stack->push<bool>(
				SDL_LowerBlit(
				surface,
				(r1) ? r1 : NULL,
				destSurface,
				(r2) ? r2 : NULL) == 0);
			return 1;
		}
		else{
			return 0;
		}
	}

	int Surface::softStretch(State & state, SDL_Surface * surface){
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");

		SDL_Rect * r1 = interfaceRect->get(1);
		SDL_Rect * r2 = interfaceRect->get(3);
		SDL_Surface * destSurface = interfaceSurface->get(2);

		if (destSurface){
			stack->push<bool>(
				SDL_SoftStretch(
				surface,
				(r1) ? r1 : NULL,
				destSurface,
				(r2) ? r2 : NULL) == 0);
			return 1;
		}
		else{
			return 0;
		}
	}

	int Surface::convert(State & state, SDL_Surface * surface){
		Stack * stack = state.stack;
		PixelFormat * interfacePixelFormat = state.getInterface<PixelFormat>("LuaSDL_PixelFormat");
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
	
		Uint32 flags;
		if (stack->is<LUA_TNUMBER>(2)){
			flags = stack->to<int>(2);
		}else{
			flags = 0;
		}

		SDL_PixelFormat * pf = interfacePixelFormat->get(1);

		if (pf){
			SDL_Surface * newSurface = SDL_ConvertSurface(surface, pf, flags);
			if (newSurface){
				interfaceSurface->push(newSurface, true);
				return 1;
			}
		}

		return 0;
	}

	int Surface::getRawPixels(State & state, SDL_Surface * surface){
		Stack * stack = state.stack;
		Uint32 position = stack->to<int>(1);
		Uint8 pixel = ((Uint8*)surface->pixels)[position];
		stack->push<int>(pixel);
		return 1;
	}
	/*
		setRawPixels32(table)
	*/

	int Surface::setRawPixels32(State & state, SDL_Surface * surface){
		Stack * stack = state.stack;
		size_t size=0;
		unsigned int * data;
		std::vector<unsigned int> _data;

		if (stack->is<LUA_TTABLE>(1)){
			size = stack->objLen(1);
			//fix buffer overflow
			size_t maxSize = surface->format->BytesPerPixel*surface->w*surface->h;
			size_t finalSize = (size*sizeof(unsigned int) <= maxSize) ? size*sizeof(unsigned int) : maxSize;
			size_t elements = finalSize / sizeof(unsigned int);

			data = new unsigned int(elements);

			for (size_t i = 0; i < elements; i++){
				stack->getField(i + 1, 1);
				data[i] = static_cast<unsigned int>(stack->to<int>(-1));
				stack->pop();
			}

			if (SDL_MUSTLOCK(surface)){
				if (SDL_LockSurface(surface) == 0){
					memcpy(surface->pixels, data, finalSize);
					SDL_UnlockSurface(surface);
					stack->push<bool>(true);
				}else{
					stack->push<bool>(false);
				}
			}else{
				memcpy(surface->pixels, data, finalSize);
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

	int Surface::setRawPixels8(State & state, SDL_Surface * surface){
		Stack * stack = state.stack;
		size_t size=0;
		unsigned char * data;
		std::vector<unsigned char> _data;

		if (stack->is<LUA_TTABLE>(1)){
			size = stack->objLen(1);
			//fix buffer overflow
			size_t maxSize = surface->format->BytesPerPixel*surface->w*surface->h;
			size_t finalSize = (size*sizeof(unsigned char) <= maxSize) ? size*sizeof(unsigned char) : maxSize;
			size_t elements = finalSize / sizeof(unsigned char);

			data = new unsigned char(elements);

			for (size_t i = 0; i < elements; i++){
				stack->getField(i+1, 1);
				data[i] = static_cast<unsigned char>(stack->to<int>(-1));
				stack->pop();
			}

			if (SDL_MUSTLOCK(surface)){
				if (SDL_LockSurface(surface) == 0){
					memcpy(surface->pixels, data, finalSize);
					SDL_UnlockSurface(surface);
					stack->push<bool>(true);
				}else{
					stack->push<bool>(false);
				}
			}else{
				memcpy(surface->pixels, data, finalSize);
				stack->push<bool>(true);
			}

			delete[] data;
		}else{
			stack->push<bool>(false);
		}
		return 1;
	}

	int Surface::fillRect(State & state, SDL_Surface * surface){
		Stack * stack = state.stack;
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
		if (stack->is<LUA_TUSERDATA>(1)){
			SDL_Rect * rect = interfaceRect->get(1);
			if (rect){
				stack->push<bool>(SDL_FillRect(surface, rect, stack->to<int>(2)) == 0);
				return 1;
			}
		}else{
			stack->push<bool>(SDL_FillRect(surface, NULL, stack->to<int>(2)) == 0);
			return 1;
		}
		return 0;
	}

	int Surface::getClipRect(State & state, SDL_Surface * surface){
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
		SDL_Rect * rect = new SDL_Rect;
		SDL_GetClipRect(surface, rect);
		interfaceRect->push(rect);
		return 1;
	}

	int Surface::setClipRect(State & state, SDL_Surface * surface){
		Stack * stack = state.stack;
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
		SDL_Rect * rect = interfaceRect->get(1);

		stack->push<bool>(
			SDL_SetClipRect(
				surface,
				(rect) ? rect : NULL) == SDL_TRUE);
		return 1;
	}

	int Surface::getFormat(State & state, SDL_Surface * surface){
		PixelFormat * interfacePixelFormat = state.getInterface<PixelFormat>("LuaSDL_PixelFormat");
		interfacePixelFormat->push(surface->format);
		return 1;
	}

	int Surface::setFormat(State & state, SDL_Surface * surface){
		PixelFormat * interfacePixelFormat = state.getInterface<PixelFormat>("LuaSDL_PixelFormat");
	
		SDL_PixelFormat * format = interfacePixelFormat->get(1);
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

	int Surface::createColorCursor(State & state, SDL_Surface * surface){
		Stack * stack = state.stack;

		Cursor * interfaceCursor = state.getInterface<Cursor>("LuaSDL_Cursor");
		interfaceCursor->push(
			SDL_CreateColorCursor(
				surface,
				stack->to<int>(1),
				stack->to<int>(2)
			), true
		);
		return 1;
	}

	int Surface::createSoftwareRenderer(State & state, SDL_Surface * surface){
		Renderer * interfaceRenderer = state.getInterface<Renderer>("LuaSDL_Renderer");

		SDL_Renderer * renderer = SDL_CreateSoftwareRenderer(surface);
		if (renderer){
			interfaceRenderer->push(renderer, true);
			return 1;
		}else{
			return 0;
		}
	}

	int inline Surface::lock(State & state, SDL_Surface  * surface){
		state.stack->push<bool>(SDL_LockSurface(surface) == 0);
		return 1;
	}
	int inline Surface::unlock(State & state, SDL_Surface  * surface){
		SDL_UnlockSurface(surface);
		return 0;
	}

	int createColorCursor(State & state, SDL_Surface  * surface);

	int inline Surface::getW(State & state, SDL_Surface  * surface){
		state.stack->push<int>(surface->w);
		return 1;
	}
	int inline Surface::getH(State & state, SDL_Surface  * surface){
		state.stack->push<int>(surface->h);
		return 1;
	}
	int inline Surface::getPitch(State & state, SDL_Surface  * surface){
		state.stack->push<int>(surface->pitch);
		return 1;
	}
	int inline Surface::getPixels(State & state, SDL_Surface  * surface){
		state.stack->push<void*>(surface->pixels);
		return 1;
	}
	int inline Surface::setPixels(State & state, SDL_Surface  * surface){
		surface->pixels = (void*)state.stack->to<void*>(1);
		return 0;
	}
	int inline Surface::getRefCount(State & state, SDL_Surface  * surface){
		state.stack->push<int>(surface->refcount);
		return 1;
	}
	int inline Surface::setRefCount(State & state, SDL_Surface  * surface){
		surface->refcount = state.stack->to<int>(1);
		return 0;
	}
	int inline Surface::getColorKey(State & state, SDL_Surface  * surface){
		Uint32 colorKey;
		if (SDL_GetColorKey(surface, &colorKey) == 0){
			state.stack->push<int>(colorKey);
			return 1;
		}
		else{
			return 0;
		}
	}
	int inline Surface::setColorKey(State & state, SDL_Surface  * surface){
		if (state.stack->is<LUA_TNUMBER>(1)){
			SDL_SetColorKey(surface, SDL_TRUE, state.stack->to<int>(1));
		}
		else{
			SDL_SetColorKey(surface, SDL_FALSE, 0);
		}
		return 0;
	}
	int inline Surface::getAlphaMod(State & state, SDL_Surface  * surface){
		Uint8 alpha;
		if (SDL_GetSurfaceAlphaMod(surface, &alpha) == 0){
			state.stack->push<int>(alpha);
			return 1;
		}
		else{
			return 0;
		}
	}
	int inline Surface::setAlphaMod(State & state, SDL_Surface  * surface){
		SDL_SetSurfaceAlphaMod(surface, (Uint8)state.stack->to<int>(1));
		return 0;
	}
	int inline Surface::getBlendMode(State & state, SDL_Surface  * surface){
		SDL_BlendMode blendMode;
		if (SDL_GetSurfaceBlendMode(surface, &blendMode) == 0){
			state.stack->push<int>((int)blendMode);
			return 1;
		}
		else{
			return 0;
		}
	}
	int inline Surface::setBlendMode(State & state, SDL_Surface  * surface){
		SDL_SetSurfaceBlendMode(surface, (SDL_BlendMode)state.stack->to<int>(1));
		return 0;
	}
	int inline Surface::getColorMod(State & state, SDL_Surface  * surface){
		Stack * stack = state.stack;
		Uint8 r, g, b;
		if (SDL_GetSurfaceColorMod(surface, &r, &g, &b) == 0){
			stack->newTable();
			stack->setField<int>("r", r);
			stack->setField<int>("g", g);
			stack->setField<int>("b", b);
			return 1;
		}
		else{
			return 0;
		}
	}
	int inline Surface::setColorMod(State & state, SDL_Surface  * surface){
		Stack * stack = state.stack;
		if (stack->is<LUA_TTABLE>(1)){
			stack->getField("r", 1);
			stack->getField("g", 1);
			stack->getField("b", 1);

			SDL_SetSurfaceColorMod(
				surface,
				(Uint8)state.stack->to<int>(-3),
				(Uint8)state.stack->to<int>(-2),
				(Uint8)state.stack->to<int>(-1));
			stack->pop(3);
		}
		return 0;
	}

	int inline Surface::setRLE(State & state, SDL_Surface  * surface){
		SDL_SetSurfaceRLE(surface, state.stack->to<int>(1));
		return 0;
	}

	void Surface::destructor(State & state, SDL_Surface * surface){
		SDL_FreeSurface(surface);
	}

	void initSurface(State * state, Module & module){
		INIT_OBJECT(Surface);
		
		//module["createRGBSurface"] = lua_SDL_CreateRGBSurface;
		module["convertPixels"] = lua_SDL_ConvertPixels;
	}

};
