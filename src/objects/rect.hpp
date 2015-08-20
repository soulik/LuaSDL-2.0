#ifndef LUA_SDL_OBJECTS_RECT_H
#define LUA_SDL_OBJECTS_RECT_H

#include "common.hpp"

namespace LuaSDL {

	class Rect : public Object<SDL_Rect> {
	public:
		explicit Rect(State * state) : Object<SDL_Rect>(state){
			LUTOK_METHOD("hasIntersection", &Rect::hasIntersection);
			LUTOK_METHOD("intersectWithRect", &Rect::intersectWithRect);
			LUTOK_METHOD("intersectWithLine", &Rect::intersectWithLine);
			LUTOK_METHOD("unionRect", &Rect::unionRect);

			LUTOK_PROPERTY("x", &Rect::getX, &Rect::setX);
			LUTOK_PROPERTY("y", &Rect::getY, &Rect::setY);
			LUTOK_PROPERTY("w", &Rect::getW, &Rect::setW);
			LUTOK_PROPERTY("h", &Rect::getH, &Rect::setH);

			LUTOK_PROPERTY("empty", &Rect::isEmpty, &Rect::nullMethod);
		}

		SDL_Rect * constructor(State & state, bool & managed);

		void destructor(State & state, SDL_Rect * rect){
			delete rect;
		}

		int hasIntersection(State & state, SDL_Rect * rectA);
		int intersectWithRect(State & state, SDL_Rect * rectA);
		int intersectWithLine(State & state, SDL_Rect * rectA);
		int unionRect(State & state, SDL_Rect * rectA);
		
		int isEmpty(State & state, SDL_Rect * rect);
		
		int getX(State & state, SDL_Rect * rect);
		int setX(State & state, SDL_Rect * rect);
		int getY(State & state, SDL_Rect * rect);
		int setY(State & state, SDL_Rect * rect);
		int getW(State & state, SDL_Rect * rect);
		int setW(State & state, SDL_Rect * rect);
		int getH(State & state, SDL_Rect * rect);
		int setH(State & state, SDL_Rect * rect);

		int operator_eq(State & state, SDL_Rect * rectA);
	};
}

#endif