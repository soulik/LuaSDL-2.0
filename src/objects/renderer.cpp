#include "objects/renderer.hpp"
#include "objects/texture.hpp"
#include "objects/surface.hpp"
#include "objects/rect.hpp"
#include <lua.hpp>

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(createTexture, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Texture & t = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Texture);
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
			t.push(texture);
		}else{
			stack->push<bool>(false);
		}
		return 1;

	}
	return 0;
}

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(createTextureFromSurface, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Texture & t = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Texture);
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);

	if (!stack->is<LUA_TNIL>(1)){

		SDL_Surface * surface = s.check(1);
		SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture){
			t.push(texture);
		}else{
			stack->push<bool>(false);
		}
		return 1;

	}
	return 0;
}

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(renderCopy, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Texture & t = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Texture);
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	if (!stack->is<LUA_TNIL>(1)){
		SDL_Texture * texture = t.check(1);
		SDL_Rect * src = NULL;
		SDL_Rect * dest = NULL;

		if (!stack->is<LUA_TNIL>(2)){
			src = r.check(2);
		}
		if (!stack->is<LUA_TNIL>(3)){
			dest = r.check(3);
		}

		int result = SDL_RenderCopy(renderer, texture, src, dest);
		stack->push<bool>(result == 0);
		return 1;

	}
	return 0;
}

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(renderCopyEx, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Texture & t = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Texture);
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	if (!stack->is<LUA_TNIL>(1)){
		SDL_Texture * texture = t.check(1);
		SDL_Rect * src = NULL;
		SDL_Rect * dest = NULL;
		double angle = 0.0f;
		SDL_Point center;
		SDL_RendererFlip flip = SDL_FLIP_NONE;

		if (!stack->is<LUA_TNIL>(2)){
			src = r.check(2);
		}
		if (!stack->is<LUA_TNIL>(3)){
			dest = r.check(3);
		}
		if (stack->is<LUA_TNUMBER>(4)){
			angle = state.to_number(4);
		}
		if (stack->is<LUA_TNUMBER>(6)){
			flip = (SDL_RendererFlip)stack->to<int>(6);
		}

		int result = 0;
		
		if (stack->is<LUA_TTABLE>(5)){
			state.get_field(5,"x");
			state.get_field(5,"y");
			center.x = stack->to<int>(-2);
			center.y = stack->to<int>(-1);
			stack->pop(2);
			result = SDL_RenderCopyEx(renderer, texture, src, dest, angle, &center, flip);
		}else{
			result = SDL_RenderCopyEx(renderer, texture, src, dest, angle, NULL, flip);
		}

		stack->push<bool>(result == 0);
		return 1;
	}
	return 0;
}

static int lua_SDL_GetRenderDrivers(State & state){
	int driversCount = SDL_GetNumRenderDrivers();
	stack->newTable();
	int i=0;
	for (int index=0; index<driversCount; index++){
		SDL_RendererInfo info;
		if (SDL_GetRenderDriverInfo(index, &info) == 0){
			stack->push<int>(++i);
			stack->newTable();
				stack->setField("name", (const std::string)info.name);
				stack->setField("flags", (const int)info.flags);
				stack->setField("max_texture_width", (const int)info.max_texture_width);
				stack->setField("max_texture_height", (const int)info.max_texture_height);
				stack->setField("num_texture_formats", (const int)info.num_texture_formats);
				state.push_literal("texture_formats");
				stack->newTable();
					for (Uint32 j=0; j < ((info.num_texture_formats <= 16) ? info.num_texture_formats : 16); j++){
						stack->push<int>(j+1);
						stack->push<int>(info.texture_formats[j]);
						stack->setTable();
					}
				stack->setTable();

			stack->setTable();
		}
	}

	return 1;
}

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(drawRect, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	SDL_Rect * rect = NULL;
	if (!stack->is<LUA_TNIL>(1)){
		rect = r.check(1);
	}
	stack->push<bool>(SDL_RenderDrawRect(renderer, rect) == 0);
	return 1;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(drawRects, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	if (stack->is<LUA_TTABLE>(1)){
		int count = state.obj_len(1);
		int final_count = 0;
		const SDL_Rect * rects = new SDL_Rect[count];
		for (int i=0; i<count; i++){
			stack->push<int>(i+1); // 1 i
			state.get_table(1); // 1 R

			SDL_Rect * rect = r.check(-1);
			rect[final_count].x = rect->x;
			rect[final_count].y = rect->y;
			rect[final_count].w = rect->w;
			rect[final_count].h = rect->h;

			stack->pop(1);
			final_count++;
		}

		stack->push<bool>(SDL_RenderDrawRects(renderer, rects, final_count) == 0);
		delete[] rects;
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(drawFillRect, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	SDL_Rect * rect = NULL;
	if (!stack->is<LUA_TNIL>(1)){
		rect = r.check(1);
	}
	stack->push<bool>(SDL_RenderFillRect(renderer, rect) == 0);
	return 1;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(drawFillRects, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	if (stack->is<LUA_TTABLE>(1)){
		int count = state.obj_len(1);
		int final_count = 0;
		const SDL_Rect * rects = new SDL_Rect[count];
		for (int i=0; i<count; i++){
			stack->push<int>(i+1); // 1 i
			state.get_table(1); // 1 R

			SDL_Rect * rect = r.check(-1);
			rect[final_count].x = rect->x;
			rect[final_count].y = rect->y;
			rect[final_count].w = rect->w;
			rect[final_count].h = rect->h;

			stack->pop(1);
			final_count++;
		}

		stack->push<bool>(SDL_RenderFillRects(renderer, rects, final_count) == 0);
		delete[] rects;
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(readPixels, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	SDL_Rect * rect = NULL;
	Uint32 format=0;
	void * pixels = NULL;
	int pitch = 0;

	if (state.is_userdata(3) && stack->is<LUA_TNUMBER>(4)){
		if (!stack->is<LUA_TNIL>(1)){
			rect = r.check(1);
		}
		if (stack->is<LUA_TNUMBER>(2)){
			format = stack->to<int>(2);
		}
		pixels = (void *)state.to_lightuserdata(3);
		pitch = stack->to<int>(4);

		stack->push<bool>(SDL_RenderReadPixels(renderer, rect, format, pixels, pitch) == 0);
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(setRenderTarget, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Texture & t = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Texture);
	if (!stack->is<LUA_TNIL>(1)){
		SDL_Texture * texture = t.check(1);
		if (texture){
			stack->push<bool>( SDL_SetRenderTarget(renderer, texture) == 0);
			return 1;
		}
	}
	return 0;
}

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(getClipRect, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	
	SDL_Rect * rect = new SDL_Rect;
	SDL_RenderGetClipRect(renderer, rect);
	r.push(rect);
	return 1;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(setClipRect, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	SDL_Rect * rect = r.check(1);
	if (rect){
		SDL_RenderSetClipRect(renderer, rect);
	}
	return 0;
}

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(getViewport, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	SDL_Rect * rect = new SDL_Rect;
	SDL_RenderGetViewport(renderer, rect);
	r.push(rect);
	return 1;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(setViewport, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect & r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	SDL_Rect * rect = r.check(1);
	if (rect){
		SDL_RenderSetViewport(renderer, rect);
	}
	return 0;
}


void LuaSDL::init_renderer(State & state, Module & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Renderer);
	module["getRenderDrivers"] = lua_SDL_GetRenderDrivers;
}
