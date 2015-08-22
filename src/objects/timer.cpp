#include "objects/timer.hpp"
#include "objects/event.hpp"
#include <lua.hpp>

namespace LuaSDL {
	SDL_TimerID * Timer::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		Timer * interfaceTimer = state.getInterface<Timer>("LuaSDL_Timer");

		if (!stack->is<LUA_TNIL>(2)){
			Uint32 interval = stack->to<int>(1);

			//store lua callback in registry
			stack->pushValue(2);

			Timer_Params * tp = new Timer_Params;
			tp->ref = stack->ref();
			tp->state = &state;
			tp->type = stack->type(2);

			void * param = reinterpret_cast<void*>(tp);

			SDL_TimerID * timerId = new SDL_TimerID;
			SDL_TimerID _timerid = SDL_AddTimer(interval, callback, param);
			*timerId = _timerid;
			timerCallbacks[_timerid] = tp;
			return timerId;
		}
		return nullptr;
	}

	int Timer::stopTimer(State & state, SDL_TimerID * timerid){
		Stack * stack = state.stack;
		SDL_TimerID id = *timerid;

		timerCallbacksMap::iterator it;
		it = timerCallbacks.find(id);
		if (it != timerCallbacks.end()){
			Timer_Params * tp = timerCallbacks[id];
			stack->unref(tp->ref);
			SDL_RemoveTimer(id);
			timerCallbacks.erase(it);
			delete tp;
		}
		return 0;
	}

	Uint32 Timer::callback(Uint32 interval, void *param){
		Timer_Params * tp = reinterpret_cast<Timer_Params*>(param);
		/*
		if (tp->type == LUA_TFUNCTION){
			State * state = tp->state;
			Stack * stack = state->stack;

			if (tp->ref != LUA_NOREF){
				stack->regValue(tp->ref);
				if (stack->is<LUA_TFUNCTION>(-1)){
					stack->push<int>(interval);
					stack->call(1, 0);
				}
			}

			return(interval);
		}
		else{
		*/
		SDL_Event event;
		SDL_UserEvent userevent;
		userevent.type = SDL_USEREVENT;
		userevent.code = LUA_SDL_TIMER_CODE;
		userevent.data1 = reinterpret_cast<void*>(tp->ref);
		userevent.data2 = NULL;

		event.type = SDL_USEREVENT;
		event.user = userevent;

		SDL_PushEvent(&event);
		return(interval);
		//}
	}

	void initTimer(State * state, Module & module){
		INIT_OBJECT(Timer);
		//module["Timer"] = lua_SDL_AddTimer;
	}

};
