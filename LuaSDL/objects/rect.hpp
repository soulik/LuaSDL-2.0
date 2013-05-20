#ifndef LUA_SDL_OBJECTS_RECT_H
#define LUA_SDL_OBJECTS_RECT_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_Rect : public LObject<Lua_SDL_Rect, SDL_Rect*> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_Rect, SDL_Rect*, "Rect") {
			
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Rect, "hasIntersection", hasIntersection);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Rect, "intersectWithRect", intersectWithRect);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Rect, "intersectWithLine", intersectWithLine);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Rect, "equals", equals);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Rect, "unionRect", unionRect);

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Rect, SDL_Rect*, "x", getX, setX);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Rect, SDL_Rect*, "y", getY, setY);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Rect, SDL_Rect*, "w", getW, setW);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Rect, SDL_Rect*, "h", getH, setH);	

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Rect, SDL_Rect*, "empty", isEmpty, null_method);

		}

		void destructor(lutok::state & s, SDL_Rect* rect){
			delete rect;
		}

		int inline LOBJECT_METHOD(equals, SDL_Rect * rect){
			LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
			state.push_boolean(SDL_RectEquals(rect, r->check(1)) == SDL_TRUE);
			return 1;
		}

		int inline LOBJECT_METHOD(hasIntersection, SDL_Rect * rect){
			LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
			state.push_boolean(SDL_HasIntersection(rect, r->check(1)) == SDL_TRUE);
			return 1;
		}

		int inline LOBJECT_METHOD(intersectWithRect, SDL_Rect * rect){
			LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
			SDL_Rect * new_rect = new SDL_Rect;

			if (SDL_IntersectRect(rect, r->check(1), new_rect) == SDL_TRUE){
				r->push(new_rect);
				return 1;
			}else{
				delete new_rect;
				return 0;
			}
		}

		int inline LOBJECT_METHOD(intersectWithLine, SDL_Rect * rect){
			int x1 = state.to_integer(2);
			int y1 = state.to_integer(3);
			int x2 = state.to_integer(4);
			int y2 = state.to_integer(5);

			if (SDL_IntersectRectAndLine(rect, &x1, &y1, &x2, &y2) == SDL_TRUE){
				state.push_integer(x1);
				state.push_integer(y1);
				state.push_integer(x2);
				state.push_integer(y2);
				return 4;
			}else{
				return 0;
			}
		}

		int inline LOBJECT_METHOD(unionRect, SDL_Rect * rect){
			LuaSDL::Lua_SDL_Rect * r = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Rect);
			SDL_Rect * new_rect = new SDL_Rect;

			SDL_UnionRect(rect, r->check(1), new_rect);
			r->push(new_rect);
			return 1;
		}

		int inline LOBJECT_METHOD(isEmpty, SDL_Rect * rect){
			state.push_boolean(SDL_RectEmpty(rect) == SDL_TRUE);
			return 1;
		}

		int inline LOBJECT_METHOD(getX, SDL_Rect * rect){
			state.push_integer(rect->x);
			return 1;
		}

		int inline LOBJECT_METHOD(setX, SDL_Rect * rect){
			rect->x = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getY, SDL_Rect * rect){
			state.push_integer(rect->y);
			return 1;
		}

		int inline LOBJECT_METHOD(setY, SDL_Rect * rect){
			rect->y = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getW, SDL_Rect * rect){
			state.push_integer(rect->w);
			return 1;
		}

		int inline LOBJECT_METHOD(setW, SDL_Rect * rect){
			rect->w = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getH, SDL_Rect * rect){
			state.push_integer(rect->h);
			return 1;
		}

		int inline LOBJECT_METHOD(setH, SDL_Rect * rect){
			rect->h = state.to_integer(1);
			return 0;
		}
	};
}

#endif