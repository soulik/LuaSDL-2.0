#include "objects/event.hpp"
#include <lua.hpp>

static int lua_SDL_PollEvent(lutok::state& state){
	if (state.is_nil(1)){
		SDL_Event event;
		if (SDL_PollEvent(&event)>0){
			LuaSDL::Lua_SDL_Event * e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
			SDL_Event * new_event = new SDL_Event;
			memcpy(new_event, &event, sizeof(SDL_Event));
			e->push(new_event);
			return 1;
		}else{
			return 0;
		}
	}else{
		LuaSDL::Lua_SDL_Event * e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
		SDL_Event * event = e->check(1);
		if (SDL_PollEvent(event)>0){
			if (state.is_boolean(2) && (state.to_boolean(1)==true)){
				e->push(event);
			}else{
				state.push_boolean(true);
			}
			return 1;
		}else{
			return 0;
		}
	}
}

static int lua_SDL_Event(lutok::state& state){
	LuaSDL::Lua_SDL_Event * e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
	SDL_Event * event = new SDL_Event;
	event->drop.file = nullptr;
	e->push(event);
	return 1;
}

static int lua_SDL_PumpEvents(lutok::state& state){
	SDL_PumpEvents();
	return 0;
}

static int lua_SDL_HasEvent(lutok::state& state){
	state.push_boolean(
		SDL_HasEvent(
			state.to_integer(1)) == SDL_TRUE);
	return 1;
}

static int lua_SDL_HasEvents(lutok::state& state){
	state.push_boolean(
		SDL_HasEvents(
			state.to_integer(1),
			state.to_integer(2)) == SDL_TRUE);
	return 1;
}

static int lua_SDL_FlushEvent(lutok::state& state){
	SDL_FlushEvent(state.to_integer(1));
	return 0;
}

static int lua_SDL_FlushEvents(lutok::state& state){
	SDL_FlushEvents(state.to_integer(1), state.to_integer(2));
	return 0;
}

static int lua_SDL_WaitEvent(lutok::state& state){
	if (state.is_nil(1)){
		SDL_Event event;
		if (SDL_WaitEvent(&event)>0){
			LuaSDL::Lua_SDL_Event * e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
			SDL_Event * new_event = new SDL_Event;
			memcpy(new_event, &event, sizeof(SDL_Event));
			e->push(new_event);
			return 1;
		}else{
			return 0;
		}
	}else{
		LuaSDL::Lua_SDL_Event * e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
		SDL_Event * event = e->check(1);
		if (SDL_WaitEvent(event)>0){
			if (state.is_boolean(2) && (state.to_boolean(1)==true)){
				e->push(event);
			}else{
				state.push_boolean(true);
			}
			return 1;
		}else{
			return 0;
		}
	}
}

static int lua_SDL_WaitEventTimeout(lutok::state& state){
	if ((state.get_top() == 1) && state.is_number(1)){
		SDL_Event event;
		if (SDL_WaitEventTimeout(&event, state.to_integer(1))>0){
			LuaSDL::Lua_SDL_Event * e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
			SDL_Event * new_event = new SDL_Event;
			memcpy(new_event, &event, sizeof(SDL_Event));
			e->push(new_event);
			return 1;
		}else{
			return 0;
		}
	}else{
		if ((state.get_top() == 2) && state.is_number(2)){
			LuaSDL::Lua_SDL_Event * e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
			SDL_Event * event = e->check(1);
			if (SDL_WaitEventTimeout(event, state.to_integer(1))>0){
				if (state.is_boolean(2) && (state.to_boolean(1)==true)){
					e->push(event);
				}else{
					state.push_boolean(true);
				}
				return 1;
			}else{
				return 0;
			}
		}else{
			return 0;
		}
	}
}

void LuaSDL::init_event(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
	module["Event"] = lua_SDL_Event;
	module["pollEvent"] = lua_SDL_PollEvent;
	module["pumpEvents"] = lua_SDL_PumpEvents;
	module["hasEvent"] = lua_SDL_HasEvent;
	module["hasEvents"] = lua_SDL_HasEvents;
	module["flushEvent"] = lua_SDL_FlushEvent;
	module["flushEvents"] = lua_SDL_FlushEvents;
	module["waitEvent"] = lua_SDL_WaitEvent;
	module["waitEventTimeout"] = lua_SDL_WaitEventTimeout;
}
