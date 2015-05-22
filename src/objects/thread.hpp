#ifndef LUA_SDL_OBJECTS_THREAD_H
#define LUA_SDL_OBJECTS_THREAD_H

#include "common.hpp"

namespace LuaSDL {
	struct LuaThread {
		lutok::state *state;
		SDL_Thread * thread;
		SDL_threadID tid;
		SDL_cond * cond;
		const char *channel;
		struct LuaThread *previous, *next;
	};
	class Lua_SDL_Thread : public LObject<Lua_SDL_Thread, LuaThread *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_Thread, LuaThread *, "Thread") {
			/*
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Thread, "start", null_method);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Thread, "send", null_method);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Thread, "receive", null_method);
			*/
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Thread, LuaThread *, "", null_method, null_method);	
		}

		void destructor(lutok::state & state, LuaThread * luathread){
		}

		int LOBJECT_METHOD(method, LuaThread * luathread){
		}
	};
}

#endif
