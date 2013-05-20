#include "objects/timer.hpp"
#include <lua.hpp>

//std::map<SDL_TimerID, int> LuaSDL::timerCallbacks;

static int lua_SDL_AddTimer(lutok::state& state){
	LuaSDL::Lua_SDL_Timer * t = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Timer);

	Uint32 interval = state.to_integer(1);
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
		t->push(timerid);
		return 1;
	}else{
		state.unref(ref);
		return 0;
	}
}

void LuaSDL::init_timer(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Timer);
	module["Timer"] = lua_SDL_AddTimer;
}
