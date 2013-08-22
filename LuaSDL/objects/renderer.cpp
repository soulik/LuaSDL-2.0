#include "objects/renderer.hpp"
#include "objects/texture.hpp"
#include "objects/surface.hpp"
#include "objects/rect.hpp"
#include <lua.hpp>

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(createTexture, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Texture * t = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Texture);
	Uint32 format = 0;
	int access = 0;
	int w = 0;
	int h = 0;

	if (state.is_number(1) && state.is_number(2) && state.is_number(3) && state.is_number(4)){
		format = state.to_integer(1);
		access = state.to_integer(2);
		w = state.to_integer(3);
		h = state.to_integer(4);

		SDL_Texture * texture = SDL_CreateTexture(renderer, format, access, w, h);
		if (texture){
			t->push(texture);
		}else{
			state.push_boolean(false);
		}
		return 1;

	}
	return 0;
}

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(createTextureFromSurface, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Texture * t = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Texture);
	LuaSDL::Lua_SDL_Surface * s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);

	if (!state.is_nil(1)){

		SDL_Surface * surface = s->check(1);
		SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture){
			t->push(texture);
		}else{
			state.push_boolean(false);
		}
		return 1;

	}
	return 0;
}

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(renderCopy, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Texture * t = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Texture);
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	if (!state.is_nil(1)){
		SDL_Texture * texture = t->check(1);
		SDL_Rect * src = NULL;
		SDL_Rect * dest = NULL;

		if (!state.is_nil(2)){
			src = r->check(2);
		}
		if (!state.is_nil(3)){
			dest = r->check(3);
		}

		int result = SDL_RenderCopy(renderer, texture, src, dest);
		state.push_boolean(result == 0);
		return 1;

	}
	return 0;
}

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(renderCopyEx, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Texture * t = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Texture);
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	if (!state.is_nil(1)){
		SDL_Texture * texture = t->check(1);
		SDL_Rect * src = NULL;
		SDL_Rect * dest = NULL;
		double angle = 0.0f;
		SDL_Point center;
		SDL_RendererFlip flip = SDL_FLIP_NONE;

		if (!state.is_nil(2)){
			src = r->check(2);
		}
		if (!state.is_nil(3)){
			dest = r->check(3);
		}
		if (state.is_number(4)){
			angle = state.to_number(4);
		}
		if (state.is_number(6)){
			flip = (SDL_RendererFlip)state.to_integer(6);
		}

		int result = 0;
		
		if (state.is_table(5)){
			state.get_field(5,"x");
			state.get_field(5,"y");
			center.x = state.to_integer(-2);
			center.y = state.to_integer(-1);
			state.pop(2);
			result = SDL_RenderCopyEx(renderer, texture, src, dest, angle, &center, flip);
		}else{
			result = SDL_RenderCopyEx(renderer, texture, src, dest, angle, NULL, flip);
		}

		state.push_boolean(result == 0);
		return 1;
	}
	return 0;
}

static int lua_SDL_GetRenderDrivers(lutok::state& state){
	int driversCount = SDL_GetNumRenderDrivers();
	state.new_table();
	int i=0;
	for (int index=0; index<driversCount; index++){
		SDL_RendererInfo info;
		if (SDL_GetRenderDriverInfo(index, &info) == 0){
			state.push_integer(++i);
			state.new_table();
				state.set_field("name", (const std::string)info.name);
				state.set_field("flags", (const int)info.flags);
				state.set_field("max_texture_width", (const int)info.max_texture_width);
				state.set_field("max_texture_height", (const int)info.max_texture_height);
				state.set_field("num_texture_formats", (const int)info.num_texture_formats);
				state.push_literal("texture_formats");
				state.new_table();
					for (Uint32 j=0; j < ((info.num_texture_formats <= 16) ? info.num_texture_formats : 16); j++){
						state.push_integer(j+1);
						state.push_integer(info.texture_formats[j]);
						state.set_table();
					}
				state.set_table();

			state.set_table();
		}
	}

	return 1;
}

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(drawRect, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	SDL_Rect * rect = NULL;
	if (!state.is_nil(1)){
		rect = r->check(1);
	}
	state.push_boolean(SDL_RenderDrawRect(renderer, rect) == 0);
	return 1;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(drawRects, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	if (state.is_table(1)){
		int count = state.obj_len(1);
		int final_count = 0;
		const SDL_Rect * rects = new SDL_Rect[count];
		for (int i=0; i<count; i++){
			state.push_integer(i+1); // 1 i
			state.get_table(1); // 1 R

			SDL_Rect * rect = r->check(-1);
			rect[final_count].x = rect->x;
			rect[final_count].y = rect->y;
			rect[final_count].w = rect->w;
			rect[final_count].h = rect->h;

			state.pop(1);
			final_count++;
		}

		state.push_boolean(SDL_RenderDrawRects(renderer, rects, final_count) == 0);
		delete[] rects;
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(drawFillRect, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	SDL_Rect * rect = NULL;
	if (!state.is_nil(1)){
		rect = r->check(1);
	}
	state.push_boolean(SDL_RenderFillRect(renderer, rect) == 0);
	return 1;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(drawFillRects, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	if (state.is_table(1)){
		int count = state.obj_len(1);
		int final_count = 0;
		const SDL_Rect * rects = new SDL_Rect[count];
		for (int i=0; i<count; i++){
			state.push_integer(i+1); // 1 i
			state.get_table(1); // 1 R

			SDL_Rect * rect = r->check(-1);
			rect[final_count].x = rect->x;
			rect[final_count].y = rect->y;
			rect[final_count].w = rect->w;
			rect[final_count].h = rect->h;

			state.pop(1);
			final_count++;
		}

		state.push_boolean(SDL_RenderFillRects(renderer, rects, final_count) == 0);
		delete[] rects;
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(readPixels, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	SDL_Rect * rect = NULL;
	Uint32 format=0;
	void * pixels = NULL;
	int pitch = 0;

	if (state.is_userdata(3) && state.is_number(4)){
		if (!state.is_nil(1)){
			rect = r->check(1);
		}
		if (state.is_number(2)){
			format = state.to_integer(2);
		}
		pixels = (void *)state.to_lightuserdata(3);
		pitch = state.to_integer(4);

		state.push_boolean(SDL_RenderReadPixels(renderer, rect, format, pixels, pitch) == 0);
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(setRenderTarget, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Texture * t = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Texture);
	if (!state.is_nil(1)){
		SDL_Texture * texture = t->check(1);
		if (texture){
			state.push_boolean( SDL_SetRenderTarget(renderer, texture) == 0);
			return 1;
		}
	}
	return 0;
}

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(getClipRect, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	
	SDL_Rect * rect = new SDL_Rect;
	SDL_RenderGetClipRect(renderer, rect);
	r->push(rect);
	return 1;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(setClipRect, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	SDL_Rect * rect = r->check(1);
	if (rect){
		SDL_RenderSetClipRect(renderer, rect);
	}
	return 0;
}

int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(getViewport, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);

	SDL_Rect * rect = new SDL_Rect;
	SDL_RenderGetViewport(renderer, rect);
	r->push(rect);
	return 1;
}
int LuaSDL::Lua_SDL_Renderer::LOBJECT_METHOD(setViewport, SDL_Renderer * renderer){
	LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
	SDL_Rect * rect = r->check(1);
	if (rect){
		SDL_RenderSetViewport(renderer, rect);
	}
	return 0;
}


void LuaSDL::init_renderer(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Renderer);
	module["getRenderDrivers"] = lua_SDL_GetRenderDrivers;
}
