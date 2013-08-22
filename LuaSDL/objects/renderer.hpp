#ifndef LUA_SDL_OBJECTS_RENDERER_H
#define LUA_SDL_OBJECTS_RENDERER_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_Renderer : public LObject<Lua_SDL_Renderer, SDL_Renderer  *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_Renderer, SDL_Renderer *, "Renderer") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "createTexture", createTexture);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "createTextureFromSurface", createTextureFromSurface);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "renderCopy", renderCopy);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "renderCopyEx", renderCopyEx);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "readPixels", readPixels);

			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "clear", clear);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "drawLine", drawLine);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "drawLines", drawLines);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "drawPoint", drawPoint);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "drawPoints", drawPoints);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "drawRect", drawRect);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "drawRects", drawRects);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "drawFillRect", drawFillRect);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "drawFillRects", drawFillRects);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Renderer, "render", renderPresent);

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Renderer, SDL_Renderer *, "drawColor", getRenderDrawColor, setRenderDrawColor);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Renderer, SDL_Renderer *, "blendMode", getRenderBlendMode, setRenderBlendMode);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Renderer, SDL_Renderer *, "info", getRendererInfo, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Renderer, SDL_Renderer *, "clipRect", getClipRect, setClipRect);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Renderer, SDL_Renderer *, "viewport", getViewport, setViewport);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Renderer, SDL_Renderer *, "renderTarget", null_method, setRenderTarget);	

		}

		void destructor(lutok::state & s, SDL_Renderer * renderer){
			SDL_DestroyRenderer(renderer);
		}

		int LOBJECT_METHOD(createTexture, SDL_Renderer * renderer);
		int LOBJECT_METHOD(createTextureFromSurface, SDL_Renderer * renderer);
		int LOBJECT_METHOD(renderCopy, SDL_Renderer * renderer);
		int LOBJECT_METHOD(renderCopyEx, SDL_Renderer * renderer);
		int LOBJECT_METHOD(readPixels, SDL_Renderer * renderer);
		int LOBJECT_METHOD(setRenderTarget, SDL_Renderer * renderer);

		int LOBJECT_METHOD(clear, SDL_Renderer * renderer){
			state.push_boolean(SDL_RenderClear(renderer) == 0);
			return 1;
		}
		int LOBJECT_METHOD(renderPresent, SDL_Renderer * renderer){
			SDL_RenderPresent(renderer);
			return 0;
		}
		int LOBJECT_METHOD(drawLine, SDL_Renderer * renderer){
			if (state.is_number(1) && state.is_number(2) && state.is_number(3) && state.is_number(4)){
				state.push_boolean(SDL_RenderDrawLine(renderer,state.to_integer(1), state.to_integer(2), state.to_integer(3), state.to_integer(4)) == 0);
				return 1;
			}else{
				return 0;
			}
		}

		int LOBJECT_METHOD(drawLines, SDL_Renderer * renderer){
			if (state.is_table(1)){
				int count = state.obj_len(1);
				if (count>0){
					SDL_Point* points = new SDL_Point[count];
					int final_count = 0;

					for (int i=0; i< count; i++){
						state.push_integer(i+1);
						state.get_table(1); // 1 T
						if (state.is_table(-1)){
							state.get_field(-1, "x"); // 1 T x
							state.get_field(-2, "y"); // 1 T x y
							points[final_count].x = state.to_integer(-2);
							points[final_count].y = state.to_integer(-1);
							final_count++;
							state.pop(3);
						}else{
							state.pop(1);
						}
					}

					state.push_boolean(SDL_RenderDrawLines(renderer, points, final_count) == 0);

					delete[] points;
					return 1;
				}
			}
			return 0;
		}
		int LOBJECT_METHOD(drawPoint, SDL_Renderer * renderer){
			if (state.is_number(1) && state.is_number(2)){
				state.push_boolean(SDL_RenderDrawPoint(renderer, state.to_integer(1), state.to_integer(2)) == 0);
				return 1;
			}else{
				return 0;
			}
		}

		int LOBJECT_METHOD(drawPoints, SDL_Renderer * renderer){
			if (state.is_table(1)){
				int count = state.obj_len(1);
				if (count>0){
					SDL_Point* points = new SDL_Point[count];
					int final_count = 0;
					
					for (int i=0; i< count; i++){
						state.push_integer(i+1);
						state.get_table(1); // 1 T
						if (state.is_table(-1)){
							state.get_field(-1, "x"); // 1 T x
							state.get_field(-2, "y"); // 1 T x y
							points[final_count].x = state.to_integer(-2);
							points[final_count].y = state.to_integer(-1);
							final_count++;
							state.pop(3);
						}else{
							state.pop(1);
						}
					}

					state.push_boolean(SDL_RenderDrawPoints(renderer, points, final_count) == 0);
					
					delete[] points;
					return 1;
				}
			}
			return 0;
		}

		int LOBJECT_METHOD(drawRect, SDL_Renderer * renderer);
		int LOBJECT_METHOD(drawRects, SDL_Renderer * renderer);
		int LOBJECT_METHOD(drawFillRect, SDL_Renderer * renderer);
		int LOBJECT_METHOD(drawFillRects, SDL_Renderer * renderer);
		
		int LOBJECT_METHOD(getRenderDrawColor, SDL_Renderer * renderer){
			Uint8 r,g,b,a;
			if (SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a)==0){
				state.new_table();
				state.set_field("r", (const int)r);
				state.set_field("g", (const int)g);
				state.set_field("b", (const int)b);
				state.set_field("a", (const int)a);
				return 1;
			}else{
				return 0;
			}

		}
		int LOBJECT_METHOD(setRenderDrawColor, SDL_Renderer * renderer){
			if (state.is_table(1)){
				Uint8 r,g,b,a;
				state.get_field(1, "r");
				state.get_field(1, "g");
				state.get_field(1, "b");
				state.get_field(1, "a");
				r = (Uint8)state.to_integer(-4);
				g = (Uint8)state.to_integer(-3);
				b = (Uint8)state.to_integer(-2);
				a = (Uint8)state.to_integer(-1);
				state.pop(4);

				SDL_SetRenderDrawColor(renderer, r,g,b,a);

			}
			return 0;
		}

		int LOBJECT_METHOD(getRenderBlendMode, SDL_Renderer * renderer){
			SDL_BlendMode mode;
			if (SDL_GetRenderDrawBlendMode(renderer, &mode)==0){
				state.push_integer(mode);
				return 1;
			}else{
				return 0;
			}

		}
		int LOBJECT_METHOD(setRenderBlendMode, SDL_Renderer * renderer){
			SDL_SetRenderDrawBlendMode(renderer, (SDL_BlendMode)state.to_integer(1));
			return 0;
		}

		int LOBJECT_METHOD(getRendererInfo, SDL_Renderer * renderer){
			SDL_RendererInfo info;
			if (SDL_GetRendererInfo(renderer, &info)==0){
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
				return 1;
			}else{
				return 0;
			}

		}

		int LOBJECT_METHOD(getClipRect, SDL_Renderer * renderer);
		int LOBJECT_METHOD(setClipRect, SDL_Renderer * renderer);
		int LOBJECT_METHOD(getViewport, SDL_Renderer * renderer);
		int LOBJECT_METHOD(setViewport, SDL_Renderer * renderer);

	};
}

#endif
