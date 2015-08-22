#ifndef LUA_SDL_OBJECTS_THREAD_H
#define LUA_SDL_OBJECTS_THREAD_H

#include "common.hpp"

namespace LuaSDL {
	/*
	struct LuaThread {
		lutok::state *state;
		SDL_Thread * thread;
		SDL_threadID tid;
		SDL_cond * cond;
		const char *channel;
		struct LuaThread *previous, *next;
	};
	class Thread : public Object<LuaThread> {
	public:
		explicit Thread(State * state) : Object<LuaThread>(state) {
			//LUTOK_METHOD("start", &Thread::null_method);
			//LUTOK_METHOD("send", &Thread::null_method);
			//LUTOK_METHOD("receive", &Thread::null_method);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Thread, LuaThread *, "", null_method, null_method);	
		}

		void destructor(State & state, LuaThread * luathread){
		}

		int method(State & state, LuaThread * luathread) {
		Stack * stack = state.stack;
		}
	};
	*/
}

#endif
