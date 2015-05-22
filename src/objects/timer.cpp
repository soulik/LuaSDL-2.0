#include "objects/timer.hpp"
#include "objects/event.hpp"
#include <lua.hpp>

//std::map<SDL_TimerID, int> LuaSDL::timerCallbacks;

static int lua_SDL_AddTimer(State & state){
	LuaSDL::Lua_SDL_Timer & t = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Timer);

	Uint32 interval = stack->to<int>(1);
	SDL_TimerCallback callback = LuaSDL::Lua_SDL_Timer::callback;

	//store lua callback in registry
	state.push_value(2);
	int ref = state.ref();
	void * param = reinterpret_cast<void*>(ref);

	SDL_TimerID timerid = SDL_AddTimer(
		interval,
		callback,
		param);
	if (timerid){
		LuaSDL::timerCallbacks[timerid] = ref;
		t.push(timerid);
		return 1;
	}else{
		state.unref(ref);
		return 0;
	}
}

Uint32 LuaSDL::Lua_SDL_Timer::callback(Uint32 interval, void *param){
	SDL_Event event;
	SDL_UserEvent userevent;
	userevent.type = SDL_USEREVENT;
	userevent.code = LUA_SDL_TIMER_CODE;
	userevent.data1 = param;
	userevent.data2 = NULL;

	event.type = SDL_USEREVENT;
	event.user = userevent;

    SDL_PushEvent(&event);
	return(interval);
}

void LuaSDL::init_timer(State & state, Module & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Timer);
	module["Timer"] = lua_SDL_AddTimer;
}
