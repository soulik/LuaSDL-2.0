#include "objects/event.hpp"
#include <SDL_syswm.h>
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
	event->syswm.msg = nullptr;
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

int LuaSDL::Lua_SDL_Event::LOBJECT_METHOD(getSyswm_msg, SDL_Event * event){
	SDL_SysWMmsg * msg = event->syswm.msg;
	
	state.new_table();
	state.set_field("timestamp", (const int) event->syswm.timestamp);

	if (msg){
			state.new_table();
			state.push_integer(1);
			state.push_integer(msg->version.major);
			state.set_table();
			state.push_integer(2);
			state.push_integer(msg->version.minor);
			state.set_table();
			state.push_integer(3);
			state.push_integer(msg->version.patch);
			state.set_table();
		state.push_literal("version");
		state.set_table(); // "version" field

		state.set_field("subsystem", (const int)msg->subsystem);

		switch (msg->subsystem){
#if defined(SDL_VIDEO_DRIVER_WINDOWS)
		case SDL_SYSWM_WINDOWS:
			state.set_field("hwnd", (const int) msg->msg.win.hwnd);
			state.set_field("msg", (const int) msg->msg.win.msg);
			state.set_field("wParam", (const int) msg->msg.win.wParam);
			state.set_field("lParam", (const int) msg->msg.win.lParam);

			state.push_literal("wParam_ptr");
			state.push_lightuserdata((void*)msg->msg.win.wParam);
			state.set_table(); // "wParam_ptr" field

			state.push_literal("lParam_ptr");
			state.push_lightuserdata((void*)msg->msg.win.lParam);
			state.set_table(); // "lParam_ptr" field
			
			break;
#endif
#if defined(SDL_VIDEO_DRIVER_X11)
		case SDL_SYSWM_X11:
			//msg->msg.x11.event
			break;
#endif
#if defined(SDL_VIDEO_DRIVER_DIRECTFB)
		case SDL_SYSWM_DIRECTFB:
			//msg->msg.dfb.event
			break;
#endif
#if defined(SDL_VIDEO_DRIVER_COCOA)
		case SDL_VIDEO_DRIVER_COCOA:
			//msg->msg.cocoa
			break;
#endif
#if defined(SDL_VIDEO_DRIVER_UIKIT)
		case SDL_VIDEO_DRIVER_UIKIT:
			//msg->msg.uikit
			break;
#endif
		case SDL_SYSWM_UNKNOWN:
			break;
		}
	}
	return 1;
}
int LuaSDL::Lua_SDL_Event::LOBJECT_METHOD(setSyswm_msg, SDL_Event * event){
	if (state.is_table(1)){
		event->syswm.type = SDL_SYSWMEVENT;
		if (event->syswm.msg == nullptr){
			event->syswm.msg = reinterpret_cast<SDL_SysWMmsg*>(SDL_malloc(sizeof(SDL_SysWMmsg)));
		}
		SDL_GetVersion(& event->syswm.msg->version);

		state.get_field(1,"subsystem");
		event->syswm.msg->subsystem = (SDL_SYSWM_TYPE) state.to_integer(-1);
		state.pop(1);
		event->syswm.timestamp = SDL_GetTicks();

		switch (event->syswm.msg->subsystem){
#if defined(SDL_VIDEO_DRIVER_WINDOWS)
		case SDL_SYSWM_WINDOWS:
			state.get_field(1,"hwnd");
			event->syswm.msg->msg.win.hwnd = (HWND)state.to_integer(-1);

			state.get_field(1,"msg");
			event->syswm.msg->msg.win.msg = (UINT)state.to_integer(-1);

			state.get_field(1,"wParam");
			event->syswm.msg->msg.win.wParam = (WPARAM)state.to_integer(-1);

			state.get_field(1,"lParam");
			event->syswm.msg->msg.win.lParam = (LPARAM)state.to_integer(-1);
			state.pop(4);
			break;
#endif
#if defined(SDL_VIDEO_DRIVER_X11)
		case SDL_SYSWM_X11:
			//msg->msg.x11.event
			break;
#endif
#if defined(SDL_VIDEO_DRIVER_DIRECTFB)
		case SDL_SYSWM_DIRECTFB:
			//msg->msg.dfb.event
			break;
#endif
#if defined(SDL_VIDEO_DRIVER_COCOA)
		case SDL_VIDEO_DRIVER_COCOA:
			//msg->msg.cocoa
			break;
#endif
#if defined(SDL_VIDEO_DRIVER_UIKIT)
		case SDL_VIDEO_DRIVER_UIKIT:
			//msg->msg.uikit
			break;
#endif
		case SDL_SYSWM_UNKNOWN:
			break;
		}
	}
	return 0;
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
