#include "common.hpp"

namespace LuaSDL {

	static int lua_SDL_AudioInit(lutok::state& state){
		if (state.is_string(1)){
			//std::string & str = state.to_string(1);
			//const char * driver = ;
			int retval = SDL_AudioInit(state.to_string(1).c_str());
			state.push_boolean( retval == 0 );
			return 1;
		}else{
			const char * driver = SDL_GetCurrentAudioDriver();
			if (driver){
				int retval = SDL_AudioInit(driver);
				state.push_boolean( retval == 0 );
				return 1;
			}
			return 0;
		}
	}
	static int lua_SDL_AudioQuit(lutok::state& state){
		SDL_AudioQuit();
		return 0;
	}
	static int lua_SDL_AudioDeviceConnected(lutok::state& state){
#ifdef AUDIODEVICECONNECTED_DEFINED
		int retval = SDL_AudioDeviceConnected(state.to_integer(1));
		if (retval>=0){
			state.push_boolean(retval == 1);
			return 1;
		}else{
			return 0;
		}
#else
		return 0;
#endif
	}
	static int lua_SDL_GetNumAudioDrivers(lutok::state& state){
		state.push_integer(SDL_GetNumAudioDrivers());
		return 1;
	}
	static int lua_SDL_GetNumAudioDevices(lutok::state& state){
		bool capture = false;
		if (state.is_boolean(1)){
			capture = state.to_boolean(1);
		}
		state.push_integer(SDL_GetNumAudioDevices( (capture) ? 1 : 0));
		return 1;
	}
	static int lua_SDL_GetAudioDeviceName(lutok::state& state){
		const char * name = SDL_GetAudioDeviceName( state.to_integer(1), (state.to_boolean(2)) ? 1 : 0);
		if (name){
			state.push_string(name);
			return 1;
		}else{
			return 0;
		}
	}
	static int lua_SDL_GetAudioDriver(lutok::state& state){
		const char * name = SDL_GetAudioDriver( state.to_integer(1));
		if (name){
			state.push_string(name);
			return 1;
		}else{
			return 0;
		}
	}
	static int lua_getAudioDrivers(lutok::state& state){
		state.new_table();
		int ii=1;
		for (int i=0; i<SDL_GetNumAudioDrivers(); i++){
			const char * name = SDL_GetAudioDriver( i );
			if (name){
				state.push_integer(ii++);
				state.new_table();
					state.push_literal("id");
					state.push_integer(i);
					state.set_table();

					state.push_literal("name");
					state.push_string(name);
					state.set_table();
				state.set_table();
			}
		}
		return 1;
	}
	static int lua_getAudioDevices(lutok::state& state){
		state.new_table();
		for (int capturing=0; capturing<2; capturing++){
			state.push_string( (capturing == 0) ? "playback" : "capture");
			state.new_table();
			int ii=1;
			for (int i=0; i<SDL_GetNumAudioDevices(capturing); i++){
				const char * name = SDL_GetAudioDeviceName( i, capturing);
				if (name){
					state.push_integer(ii++);
					state.new_table();
						state.push_literal("id");
						state.push_integer(i);
						state.set_table();

						state.push_literal("name");
						state.push_string(name);
						state.set_table();
					state.set_table();
				}
			}
			state.set_table();
		}
		return 1;
	}
	static int lua_SDL_GetAudioStatus(lutok::state& state){
		state.push_integer(SDL_GetAudioStatus());
		return 1;
	}
	static int lua_SDL_GetCurrentAudioDriver(lutok::state& state){
		const char * name = SDL_GetCurrentAudioDriver();
		if (name){
			state.push_string(name);
			return 1;
		}else{
			return 0;
		}
	}
	static int lua_SDL_MixAudioFormat(lutok::state& state){

		//SDL_MixAudioFormat();
		return 0;
	}
	void init_audio(moduleDef & module){
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