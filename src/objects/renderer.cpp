#include "objects/renderer.hpp"
#include "objects/texture.hpp"
#include "objects/surface.hpp"
#include "objects/rect.hpp"
#include <lua.hpp>

namespace LuaSDL {

	int Renderer::clear(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		stack->push<bool>(SDL_RenderClear(renderer) == 0);
		return 1;
	}
	int Renderer::renderPresent(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		SDL_RenderPresent(renderer);
		return 0;
	}
	int Renderer::drawLine(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2) && stack->is<LUA_TNUMBER>(3) && stack->is<LUA_TNUMBER>(4)){
			stack->push<bool>(SDL_RenderDrawLine(renderer, stack->to<int>(1), stack->to<int>(2), stack->to<int>(3), stack->to<int>(4)) == 0);
			return 1;
		}
		else{
			return 0;
		}
	}

	int Renderer::drawLines(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TTABLE>(1)){
			int count = stack->objLen(1);
			if (count > 0){
				SDL_Point* points = new SDL_Point[count];
				int final_count = 0;

				for (int i = 0; i < count; i++){
					stack->getField(i+1);
					if (stack->is<LUA_TTABLE>(-1)){
						stack->getField("x", -1);
						stack->getField("y", -2);
						points[final_count].x = stack->to<int>(-2);
						points[final_count].y = stack->to<int>(-1);
						final_count++;
						stack->pop(3);
					}
					else{
						stack->pop(1);
					}
				}

				stack->push<bool>(SDL_RenderDrawLines(renderer, points, final_count) == 0);

				delete[] points;
				return 1;
			}
		}
		return 0;
	}
	int Renderer::drawPoint(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2)){
			stack->push<bool>(SDL_RenderDrawPoint(renderer, stack->to<int>(1), stack->to<int>(2)) == 0);
			return 1;
		}
		else{
			return 0;
		}
	}

	int Renderer::drawPoints(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TTABLE>(1)){
			int count = stack->objLen(1);
			if (count > 0){
				SDL_Point* points = new SDL_Point[count];
				int final_count = 0;

				for (int i = 0; i < count; i++){
					stack->getField(i + 1);
					if (stack->is<LUA_TTABLE>(-1)){
						stack->getField("x", -1);
						stack->getField("y", -2);
						points[final_count].x = stack->to<int>(-2);
						points[final_count].y = stack->to<int>(-1);
						final_count++;
						stack->pop(3);
					}
					else{
						stack->pop(1);
					}
				}

				stack->push<bool>(SDL_RenderDrawPoints(renderer, points, final_count) == 0);

				delete[] points;
				return 1;
			}
		}
		return 0;
	}

	int Renderer::createTexture(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Texture * interfaceTexture = state.getInterface<Texture>("LuaSDL_Texture");
		Uint32 format = 0;
		int access = 0;
		int w = 0;
		int h = 0;

		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2) && stack->is<LUA_TNUMBER>(3) && stack->is<LUA_TNUMBER>(4)){
			format = stack->to<int>(1);
			access = stack->to<int>(2);
			w = stack->to<int>(3);
			h = stack->to<int>(4);

			SDL_Texture * texture = SDL_CreateTexture(renderer, format, access, w, h);
			if (texture){
				interfaceTexture->push(texture, true);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;

		}
		return 0;
	}

	int Renderer::createTextureFromSurface(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Texture * interfaceTexture = state.getInterface<Texture>("LuaSDL_Texture");
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");

		if (!stack->is<LUA_TNIL>(1)){

			SDL_Surface * surface = interfaceSurface->get(1);
			if (surface){
				SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
				if (texture){
					interfaceTexture->push(texture, true);
				}
				else{
					stack->push<bool>(false);
				}
				return 1;
			}
		}
		return 0;
	}

	int Renderer::renderCopy(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Texture * interfaceTexture = state.getInterface<Texture>("LuaSDL_Texture");
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");

		if (!stack->is<LUA_TNIL>(1)){
			SDL_Texture * texture = interfaceTexture->get(1);
			SDL_Rect * src = NULL;
			SDL_Rect * dest = NULL;

			if (texture){
				if (stack->is<LUA_TUSERDATA>(2)){
					SDL_Rect * r = interfaceRect->get(2);
					if (r){
						src = r;
					}
				}
				if (stack->is<LUA_TUSERDATA>(3)){
					SDL_Rect * r = interfaceRect->get(3);
					if (r){
						dest = r;
					}
				}

				int result = SDL_RenderCopy(renderer, texture, src, dest);
				stack->push<bool>(result == 0);
				return 1;
			}
		}
		return 0;
	}

	int Renderer::renderCopyEx(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Texture * interfaceTexture = state.getInterface<Texture>("LuaSDL_Texture");
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");

		if (stack->is<LUA_TUSERDATA>(1)){
			SDL_Texture * texture = interfaceTexture->get(1);
			if (texture){
				SDL_Rect * src = NULL;
				SDL_Rect * dest = NULL;
				double angle = 0.0f;
				SDL_Point center;
				SDL_RendererFlip flip = SDL_FLIP_NONE;

				if (stack->is<LUA_TUSERDATA>(2)){
					SDL_Rect * r = interfaceRect->get(2);
					if (r){
						src = r;
					}
				}
				if (stack->is<LUA_TUSERDATA>(3)){
					SDL_Rect * r = interfaceRect->get(3);
					if (r){
						dest = r;
					}
				}
				if (stack->is<LUA_TNUMBER>(4)){
					angle = stack->to<LUA_NUMBER>(4);
				}
				if (stack->is<LUA_TNUMBER>(6)){
					flip = (SDL_RendererFlip)stack->to<int>(6);
				}

				int result = 0;

				if (stack->is<LUA_TTABLE>(5)){
					stack->getField("x", 5);
					stack->getField("y", 5);
					center.x = stack->to<int>(-2);
					center.y = stack->to<int>(-1);
					stack->pop(2);
					result = SDL_RenderCopyEx(renderer, texture, src, dest, angle, &center, flip);
				}
				else{
					result = SDL_RenderCopyEx(renderer, texture, src, dest, angle, NULL, flip);
				}

				stack->push<bool>(result == 0);
				return 1;
			}
		}
		return 0;
	}

	static int lua_SDL_GetRenderDrivers(State & state){
		Stack * stack = state.stack;
		int driversCount = SDL_GetNumRenderDrivers();
		stack->newTable();
		int i = 0;
		for (int index = 0; index < driversCount; index++){
			SDL_RendererInfo info;
			if (SDL_GetRenderDriverInfo(index, &info) == 0){
				stack->push<int>(++i);
				stack->newTable();
				stack->setField<const std::string &>("name", info.name);
				stack->setField<int>("flags",info.flags);
				stack->setField<int>("max_texture_width", info.max_texture_width);
				stack->setField<int>("max_texture_height", info.max_texture_height);
				stack->setField<int>("num_texture_formats", info.num_texture_formats);
				stack->push<const std::string &>("texture_formats");
				stack->newTable();
				for (Uint32 j = 0; j < ((info.num_texture_formats <= 16) ? info.num_texture_formats : 16); j++){
					stack->push<int>(j + 1);
					stack->push<int>(info.texture_formats[j]);
					stack->setTable();
				}
				stack->setTable();

				stack->setTable();
			}
		}

		return 1;
	}

	int Renderer::drawRect(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
		SDL_Rect * rect = NULL;
		if (stack->is<LUA_TUSERDATA>(1)){
			SDL_Rect * r = interfaceRect->get(1);
			if (r){
				rect = r;
			}
		}
		stack->push<bool>(SDL_RenderDrawRect(renderer, rect) == 0);
		return 1;
	}
	int Renderer::drawRects(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
		if (stack->is<LUA_TTABLE>(1)){
			int count = stack->objLen(1);
			int final_count = 0;
			const SDL_Rect * rects = new SDL_Rect[count];
			for (int i = 0; i < count; i++){
				stack->getField(i+1, 1);

				SDL_Rect * rect = interfaceRect->get(-1);
				if (rect){
					rect[final_count].x = rect->x;
					rect[final_count].y = rect->y;
					rect[final_count].w = rect->w;
					rect[final_count].h = rect->h;

					final_count++;
				}
				stack->pop(1);
			}

			stack->push<bool>(SDL_RenderDrawRects(renderer, rects, final_count) == 0);
			delete[] rects;
			return 1;
		}
		return 0;
	}
	int Renderer::drawFillRect(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
		SDL_Rect * rect = NULL;
		if (!stack->is<LUA_TNIL>(1)){
			SDL_Rect * r = interfaceRect->get(1);
			if (r){
				rect = r;
			}
		}
		stack->push<bool>(SDL_RenderFillRect(renderer, rect) == 0);
		return 1;
	}
	int Renderer::drawFillRects(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
		if (stack->is<LUA_TTABLE>(1)){
			int count = stack->objLen(1);
			int final_count = 0;
			const SDL_Rect * rects = new SDL_Rect[count];
			for (int i = 0; i < count; i++){
				stack->getField(i + 1, 1);

				SDL_Rect * rect = interfaceRect->get(-1);
				if (rect){
					rect[final_count].x = rect->x;
					rect[final_count].y = rect->y;
					rect[final_count].w = rect->w;
					rect[final_count].h = rect->h;

					final_count++;
				}
				stack->pop(1);
			}

			stack->push<bool>(SDL_RenderFillRects(renderer, rects, final_count) == 0);
			delete[] rects;
			return 1;
		}
		return 0;
	}
	int Renderer::readPixels(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
		SDL_Rect * rect = NULL;
		Uint32 format = 0;
		void * pixels = NULL;
		int pitch = 0;

		if (stack->is<LUA_TLIGHTUSERDATA>(3) && stack->is<LUA_TNUMBER>(4)){
			if (!stack->is<LUA_TNIL>(1)){
				SDL_Rect * r = interfaceRect->get(1);
				if (r){
					rect = r;
				}
			}
			if (stack->is<LUA_TNUMBER>(2)){
				format = stack->to<int>(2);
			}
			pixels = (void *)stack->to<void*>(3);
			pitch = stack->to<int>(4);

			stack->push<bool>(SDL_RenderReadPixels(renderer, rect, format, pixels, pitch) == 0);
			return 1;
		}
		return 0;
	}
	int Renderer::setRenderTarget(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Texture * interfaceTexture = state.getInterface<Texture>("LuaSDL_Texture");
		if (!stack->is<LUA_TNIL>(1)){
			SDL_Texture * texture = interfaceTexture->get(1);
			if (texture){
				stack->push<bool>(SDL_SetRenderTarget(renderer, texture) == 0);
				return 1;
			}
		}
		return 0;
	}

	int Renderer::getClipRect(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");

		SDL_Rect * rect = new SDL_Rect;
		SDL_RenderGetClipRect(renderer, rect);
		interfaceRect->push(rect, true);
		return 1;
	}
	int Renderer::setClipRect(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
		SDL_Rect * rect = interfaceRect->get(1);
		if (rect){
			SDL_RenderSetClipRect(renderer, rect);
		}
		return 0;
	}

	int Renderer::getViewport(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");

		SDL_Rect * rect = new SDL_Rect;
		SDL_RenderGetViewport(renderer, rect);
		interfaceRect->push(rect, true);
		return 1;
	}
	int Renderer::setViewport(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Rect * interfaceRect = state.getInterface<Rect>("LuaSDL_Rect");
		SDL_Rect * rect = interfaceRect->get(1);
		if (rect){
			SDL_RenderSetViewport(renderer, rect);
		}
		return 0;
	}

	int Renderer::getRenderDrawColor(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		Uint8 r, g, b, a;
		if (SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a) == 0){
			stack->newTable();
			stack->setField("r", (const int)r);
			stack->setField("g", (const int)g);
			stack->setField("b", (const int)b);
			stack->setField("a", (const int)a);
			return 1;
		}
		else{
			return 0;
		}

	}
	int Renderer::setRenderDrawColor(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TTABLE>(1)){
			Uint8 r, g, b, a;
			stack->getField("r", 1);
			stack->getField("g", 1);
			stack->getField("b", 1);
			stack->getField("a", 1);
			r = (Uint8)stack->to<int>(-4);
			g = (Uint8)stack->to<int>(-3);
			b = (Uint8)stack->to<int>(-2);
			a = (Uint8)stack->to<int>(-1);
			stack->pop(4);

			SDL_SetRenderDrawColor(renderer, r, g, b, a);

		}
		return 0;
	}

	int Renderer::getRenderBlendMode(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		SDL_BlendMode mode;
		if (SDL_GetRenderDrawBlendMode(renderer, &mode) == 0){
			stack->push<int>(mode);
			return 1;
		}
		else{
			return 0;
		}

	}
	int Renderer::setRenderBlendMode(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		SDL_SetRenderDrawBlendMode(renderer, (SDL_BlendMode)stack->to<int>(1));
		return 0;
	}

	int Renderer::getRendererInfo(State & state, SDL_Renderer * renderer) {
		Stack * stack = state.stack;
		SDL_RendererInfo info;
		if (SDL_GetRendererInfo(renderer, &info) == 0){
			stack->newTable();
				stack->setField<const std::string &>("name", info.name);
				stack->setField<int>("flags", (const int)info.flags);
				stack->setField<int>("max_texture_width", (const int)info.max_texture_width);
				stack->setField<int>("max_texture_height", (const int)info.max_texture_height);
				stack->setField<int>("num_texture_formats", (const int)info.num_texture_formats);
			
				stack->newTable();
					for (Uint32 j = 0; j < ((info.num_texture_formats <= 16) ? info.num_texture_formats : 16); j++){
						stack->push<int>(j + 1);
						stack->push<int>(info.texture_formats[j]);
						stack->setTable();
					}
				stack->setField("texture_formats");
			return 1;
		}
		else{
			return 0;
		}

	}

	void initRenderer(State * state, Module & module){
		INIT_OBJECT(Renderer);
		module["getRenderDrivers"] = lua_SDL_GetRenderDrivers;
	}

};
