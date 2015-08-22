#ifndef LUA_SDL_OBJECTS_TIMER_H
#define LUA_SDL_OBJECTS_TIMER_H

#include "common.hpp"
#include <map>

namespace LuaSDL {
	struct Timer_Params {
		int ref;
		State * state;
		int type;
	};
	typedef std::map<SDL_TimerID, Timer_Params*> timerCallbacksMap;

	class Timer : public Object<SDL_TimerID> {
	private:
		timerCallbacksMap timerCallbacks;
	public:
		explicit Timer(State * state) : Object<SDL_TimerID>(state) {
			LUTOK_METHOD("stop", &Timer::stopTimer);
			//LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Timer, SDL_TimerID, "", null_method, null_method);	
		}

		SDL_TimerID * constructor(State & state, bool & managed);

		void destructor(State & state, SDL_TimerID * timerid){
			stopTimer(state, timerid);
			delete timerid;
		}
		
		int stopTimer(State & state, SDL_TimerID * timerid);
		static Uint32 callback(Uint32 interval, void *param);

	};
}

#endif
