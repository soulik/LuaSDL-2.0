#ifndef LUA_SDL_OBJECTS_TIMER_H
#define LUA_SDL_OBJECTS_TIMER_H

#include "common.hpp"
#include <map>

namespace LuaSDL {
	typedef std::map<SDL_TimerID, int> timerCallbacksMap;
	static timerCallbacksMap timerCallbacks;

	class Lua_SDL_Timer : public LObject<Lua_SDL_Timer, SDL_TimerID> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_Timer, SDL_TimerID, "Timer") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Timer, "stop", stopTimer);
			//LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Timer, SDL_TimerID, "", null_method, null_method);	
		}

		void destructor(lutok::state & s, SDL_TimerID timerid){
			stopTimer(s, timerid);
		}
		
		int LOBJECT_METHOD(stopTimer, SDL_TimerID timerid){
			timerCallbacksMap::iterator it;
			it = timerCallbacks.find(timerid);
			if (it != timerCallbacks.end() ){
				state.unref(timerCallbacks[timerid]);
				SDL_RemoveTimer(timerid);
				timerCallbacks.erase(it);
			}
			return 0;
		}
		static Uint32 callback(Uint32 interval, void *param);

	};
}

#endif
