#include "common.hpp"

namespace LuaSDL {

	static int lua_SDL_AudioInit(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			std::string driverName = stack->to<const std::string>(1);
			int retval = SDL_AudioInit(driverName.c_str());
			stack->push<bool>( retval == 0 );
			return 1;
		}else{
			const char * driver = SDL_GetCurrentAudioDriver();
			if (driver){
				int retval = SDL_AudioInit(driver);
				stack->push<bool>(retval == 0);
				return 1;
			}
			return 0;
		}
	}
	static int lua_SDL_AudioQuit(State & state){
		SDL_AudioQuit();
		return 0;
	}
	static int lua_SDL_AudioDeviceConnected(State & state){
#ifdef AUDIODEVICECONNECTED_DEFINED
		Stack * stack = state->stack;
		int retval = SDL_AudioDeviceConnected(stack->to<int>(1));
		if (retval>=0){
			stack->push<bool>(retval == 1);
			return 1;
		}else{
			return 0;
		}
#else
		return 0;
#endif
	}
	static int lua_SDL_GetNumAudioDrivers(State & state){
		Stack * stack = state.stack;
		stack->push<int>(SDL_GetNumAudioDrivers());
		return 1;
	}
	static int lua_SDL_GetNumAudioDevices(State & state){
		Stack * stack = state.stack;
		bool capture = false;
		if (stack->is<LUA_TBOOLEAN>(1)){
			capture = stack->to<bool>(1);
		}
		stack->push<int>(SDL_GetNumAudioDevices( (capture) ? 1 : 0));
		return 1;
	}
	static int lua_SDL_GetAudioDeviceName(State & state){
		Stack * stack = state.stack;
		const char * name = SDL_GetAudioDeviceName(stack->to<int>(1), (stack->to<bool>(2)) ? 1 : 0);
		if (name){
			stack->push<const std::string &>(name);
			return 1;
		}else{
			return 0;
		}
	}
	static int lua_SDL_GetAudioDriver(State & state){
		Stack * stack = state.stack;
		const char * name = SDL_GetAudioDriver(stack->to<int>(1));
		if (name){
			stack->push<const std::string &>(name);
			return 1;
		}else{
			return 0;
		}
	}
	static int lua_getAudioDrivers(State & state){
		Stack * stack = state.stack;
		stack->newTable();
		int ii=1;
		for (int i=0; i<SDL_GetNumAudioDrivers(); i++){
			const char * name = SDL_GetAudioDriver( i );
			if (name){
				stack->push<int>(ii++);
				stack->newTable();
					stack->setField<int>("id", i);
					stack->setField<const std::string &>("name", name);
				stack->setTable();
			}
		}
		return 1;
	}
	static int lua_getAudioDevices(State & state){
		Stack * stack = state.stack;
		stack->newTable();
		for (int capturing=0; capturing<2; capturing++){
			stack->push<const std::string &>( (capturing == 0) ? "playback" : "capture");
			stack->newTable();
			int ii=1;
			for (int i=0; i<SDL_GetNumAudioDevices(capturing); i++){
				const char * name = SDL_GetAudioDeviceName( i, capturing);
				if (name){
					stack->push<int>(ii++);
					stack->newTable();
						stack->setField<int>("id", i);
						stack->setField<const std::string &>("name", name);
					stack->setTable();
				}
			}
			stack->setTable();
		}
		return 1;
	}
	static int lua_SDL_GetAudioStatus(State & state){
		Stack * stack = state.stack;
		stack->push<int>(SDL_GetAudioStatus());
		return 1;
	}
	static int lua_SDL_GetCurrentAudioDriver(State & state){
		Stack * stack = state.stack;
		const char * name = SDL_GetCurrentAudioDriver();
		if (name){
			stack->push<const std::string &>(name);
			return 1;
		}else{
			return 0;
		}
	}
	static int lua_SDL_MixAudioFormat(State & state){
		Stack * stack = state.stack;

		//SDL_MixAudioFormat();
		return 0;
	}
	void initAudio(Module & module){
		module["audioInit"] = lua_SDL_AudioInit;
		module["audioQuit"] = lua_SDL_AudioQuit;
		module["audioDeviceConnected"] = lua_SDL_AudioDeviceConnected;
		module["getNumAudioDrivers"] = lua_SDL_GetNumAudioDrivers;
		module["getNumAudioDevices"] = lua_SDL_GetNumAudioDevices;
		module["getAudioDeviceName"] = lua_SDL_GetAudioDeviceName;
		module["getAudioDriver"] = lua_SDL_GetAudioDriver;
		module["getAudioDrivers"] = lua_getAudioDrivers;
		module["getAudioDevices"] = lua_getAudioDevices;
		module["getAudioStatus"] = lua_SDL_GetAudioStatus;
		module["getCurrentAudioDriver"] = lua_SDL_GetCurrentAudioDriver;
	}
}