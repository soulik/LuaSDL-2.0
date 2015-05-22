#include "objects/event.hpp"
#include <SDL_syswm.h>
#include <lua.hpp>

static int lua_SDL_PollEvent(State & state){
	if (stack->is<LUA_TNIL>(1)){
		SDL_Event event;
		if (SDL_PollEvent(&event)>0){
			LuaSDL::Lua_SDL_Event & e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
			SDL_Event * new_event = new SDL_Event;
			memcpy(new_event, &event, sizeof(SDL_Event));
			e.push(new_event);
			return 1;
		}else{
			return 0;
		}
	}else{
		LuaSDL::Lua_SDL_Event & e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
		SDL_Event * event = e.check(1);
		if (SDL_PollEvent(event)>0){
			if (stack->is<LUA_TBOOLEAN>(2) && (stack->to<bool>(1)==true)){
				e.push(event);
			}else{
				stack->push<bool>(true);
			}
			return 1;
		}else{
			return 0;
		}
	}
}

static int lua_SDL_Event(State & state){
	LuaSDL::Lua_SDL_Event & e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
	SDL_Event * event = new SDL_Event;
	event->drop.file = nullptr;
	event->syswm.msg = nullptr;
	e.push(event);
	return 1;
}

static int lua_SDL_PumpEvents(State & state){
	SDL_PumpEvents();
	return 0;
}

static int lua_SDL_HasEvent(State & state){
	stack->push<bool>(
		SDL_HasEvent(
			stack->to<int>(1)) == SDL_TRUE);
	return 1;
}

static int lua_SDL_HasEvents(State & state){
	stack->push<bool>(
		SDL_HasEvents(
			stack->to<int>(1),
			stack->to<int>(2)) == SDL_TRUE);
	return 1;
}

static int lua_SDL_FlushEvent(State & state){
	SDL_FlushEvent(stack->to<int>(1));
	return 0;
}

static int lua_SDL_FlushEvents(State & state){
	SDL_FlushEvents(stack->to<int>(1), stack->to<int>(2));
	return 0;
}

static int lua_SDL_WaitEvent(State & state){
	if (stack->is<LUA_TNIL>(1)){
		SDL_Event event;
		if (SDL_WaitEvent(&event)>0){
			LuaSDL::Lua_SDL_Event & e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
			SDL_Event * new_event = new SDL_Event;
			memcpy(new_event, &event, sizeof(SDL_Event));
			e.push(new_event);
			return 1;
		}else{
			return 0;
		}
	}else{
		LuaSDL::Lua_SDL_Event & e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
		SDL_Event * event = e.check(1);
		if (SDL_WaitEvent(event)>0){
			if (stack->is<LUA_TBOOLEAN>(2) && (stack->to<bool>(1)==true)){
				e.push(event);
			}else{
				stack->push<bool>(true);
			}
			return 1;
		}else{
			return 0;
		}
	}
}

static int lua_SDL_WaitEventTimeout(State & state){
	if ((state.get_top() == 1) && stack->is<LUA_TNUMBER>(1)){
		SDL_Event event;
		if (SDL_WaitEventTimeout(&event, stack->to<int>(1))>0){
			LuaSDL::Lua_SDL_Event & e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
			SDL_Event * new_event = new SDL_Event;
			memcpy(new_event, &event, sizeof(SDL_Event));
			e.push(new_event);
			return 1;
		}else{
			return 0;
		}
	}else{
		if ((state.get_top() == 2) && stack->is<LUA_TNUMBER>(2)){
			LuaSDL::Lua_SDL_Event & e = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Event);
			SDL_Event * event = e.check(1);
			if (SDL_WaitEventTimeout(event, stack->to<int>(1))>0){
				if (stack->is<LUA_TBOOLEAN>(2) && (stack->to<bool>(1)==true)){
					e.push(event);
				}else{
					stack->push<bool>(true);
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
	
	stack->newTable();
	stack->setField("timestamp", (const int) event->syswm.timestamp);

	if (msg){
			stack->newTable();
			stack->push<int>(1);
			stack->push<int>(msg->version.major);
			stack->setTable();
			stack->push<int>(2);
			stack->push<int>(msg->version.minor);
			stack->setTable();
			stack->push<int>(3);
			stack->push<int>(msg->version.patch);
			stack->setTable();
		state.push_literal("version");
		stack->setTable(); // "version" field

		stack->setField("subsystem", (const int)msg->subsystem);

		switch (msg->subsystem){
#if defined(SDL_VIDEO_DRIVER_WINDOWS)
		case SDL_SYSWM_WINDOWS:
			stack->setField("hwnd", (const int) msg->msg.win.hwnd);
			stack->setField("msg", (const int) msg->msg.win.msg);
			stack->setField("wParam", (const int) msg->msg.win.wParam);
			stack->setField("lParam", (const int) msg->msg.win.lParam);

			state.push_literal("wParam_ptr");
			state.push_lightuserdata((void*)msg->msg.win.wParam);
			stack->setTable(); // "wParam_ptr" field

			state.push_literal("lParam_ptr");
			state.push_lightuserdata((void*)msg->msg.win.lParam);
			stack->setTable(); // "lParam_ptr" field
			
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
	if (stack->is<LUA_TTABLE>(1)){
		event->syswm.type = SDL_SYSWMEVENT;
		if (event->syswm.msg == nullptr){
			event->syswm.msg = reinterpret_cast<SDL_SysWMmsg*>(SDL_malloc(sizeof(SDL_SysWMmsg)));
		}
		SDL_GetVersion(& event->syswm.msg->version);

		state.get_field(1,"subsystem");
		event->syswm.msg->subsystem = (SDL_SYSWM_TYPE) stack->to<int>(-1);
		stack->pop(1);
		event->syswm.timestamp = SDL_GetTicks();

		switch (event->syswm.msg->subsystem){
#if defined(SDL_VIDEO_DRIVER_WINDOWS)
		case SDL_SYSWM_WINDOWS:
			state.get_field(1,"hwnd");
			event->syswm.msg->msg.win.hwnd = (HWND)stack->to<int>(-1);

			state.get_field(1,"msg");
			event->syswm.msg->msg.win.msg = (UINT)stack->to<int>(-1);

			state.get_field(1,"wParam");
			event->syswm.msg->msg.win.wParam = (WPARAM)stack->to<int>(-1);

			state.get_field(1,"lParam");
			event->syswm.msg->msg.win.lParam = (LPARAM)stack->to<int>(-1);
			stack->pop(4);
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

void LuaSDL::init_event(State & state, Module & module){
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
