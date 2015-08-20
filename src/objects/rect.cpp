#include "objects/rect.hpp"
#include <lua.hpp>

namespace LuaSDL {
	void initRect(State * state, Module & module){
		state->registerInterface<Rect>("LuaSDL_Rect");
	}

	SDL_Rect * Rect::constructor(State & state, bool & managed){
		LUTOK2_NOT_USED(managed);
		SDL_Rect * obj = nullptr;
		Stack * stack = state.stack;
		Rect * interfaceRect = state.getInterface<Rect>("LuaBox2D_Rect");
		if (stack->is<LUA_TUSERDATA>(1)){
			SDL_Rect * rect = interfaceRect->get(1);
			if (rect){
				obj = new SDL_Rect(*rect);
			}
			else{
				return nullptr;
			}
		} else{
			obj = new SDL_Rect();
		}

		return obj;
	}


	inline int Rect::operator_eq(State & state, SDL_Rect * rectA){
		Rect * interfaceRect = state.getInterface<Rect>("LuaBox2D_Rect");
		SDL_Rect * rectB = interfaceRect->get(1);
		if (rectB){
			state.stack->push<bool>(SDL_RectEquals(rectA, rectB) == SDL_TRUE);
			return 1;
		}
		else{
			return 0;
		}
	}

	inline int Rect::hasIntersection(State & state, SDL_Rect * rectA){
		Rect * interfaceRect = state.getInterface<Rect>("LuaBox2D_Rect");
		SDL_Rect * rectB = interfaceRect->get(1);
		if (rectB){
			state.stack->push<bool>(SDL_HasIntersection(rectA, rectB) == SDL_TRUE);
			return 1;
		}
		else{
			return 0;
		}
	}

	inline int Rect::intersectWithRect(State & state, SDL_Rect * rectA){
		Rect * interfaceRect = state.getInterface<Rect>("LuaBox2D_Rect");
		SDL_Rect * rectB = interfaceRect->get(1);
		if (rectB){
			SDL_Rect * newRect = new SDL_Rect;

			if (SDL_IntersectRect(rectA, rectB, newRect) == SDL_TRUE){
				interfaceRect->push(newRect, true);
				return 1;
			}
			else{
				delete newRect;
			}
		}
		return 0;
	}

	inline int Rect::intersectWithLine(State & state, SDL_Rect * rectA){
		Stack * stack = state.stack;
		int x0 = stack->to<int>(1);
		int y0 = stack->to<int>(2);
		int x1 = stack->to<int>(3);
		int y1 = stack->to<int>(4);

		if (SDL_IntersectRectAndLine(rectA, &x0, &y0, &x1, &y1) == SDL_TRUE){
			stack->push<int>(x0);
			stack->push<int>(y0);
			stack->push<int>(x1);
			stack->push<int>(y1);
			return 4;
		}
		else{
			return 0;
		}
	}

	inline int Rect::unionRect(State & state, SDL_Rect * rectA){
		Rect * interfaceRect = state.getInterface<Rect>("LuaBox2D_Rect");
		SDL_Rect * rectB = interfaceRect->get(1);
		if (rectB){
			SDL_Rect * newRect = new SDL_Rect;

			SDL_UnionRect(rectA, rectB, newRect);
			interfaceRect->push(newRect, true);
			return 1;
		}
		else{
			return 0;
		}
	}

	inline int Rect::isEmpty(State & state, SDL_Rect * rect){
		state.stack->push<bool>(SDL_RectEmpty(rect) == SDL_TRUE);
		return 1;
	}

	inline int Rect::getX(State & state, SDL_Rect * rect){
		state.stack->push<int>(rect->x);
		return 1;
	}

	inline int Rect::setX(State & state, SDL_Rect * rect){
		rect->x = state.stack->to<int>(1);
		return 0;
	}

	inline int Rect::getY(State & state, SDL_Rect * rect){
		state.stack->push<int>(rect->y);
		return 1;
	}

	inline int Rect::setY(State & state, SDL_Rect * rect){
		rect->y = state.stack->to<int>(1);
		return 0;
	}

	inline int Rect::getW(State & state, SDL_Rect * rect){
		state.stack->push<int>(rect->w);
		return 1;
	}

	inline int Rect::setW(State & state, SDL_Rect * rect){
		rect->w = state.stack->to<int>(1);
		return 0;
	}

	inline int Rect::getH(State & state, SDL_Rect * rect){
		state.stack->push<int>(rect->h);
		return 1;
	}

	inline int Rect::setH(State & state, SDL_Rect * rect){
		rect->h = state.stack->to<int>(1);
		return 0;
	}

};