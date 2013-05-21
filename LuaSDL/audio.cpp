#include "common.hpp"

namespace LuaSDL {

	static int lua_SDL_AudioInit(lutok::state& state){
		state.push_boolean( SDL_AudioInit(state.to_string().c_str()) == 0 );
		return 1;
	}

	static int lua_SDL_AudioQuit(lutok::state& state){
		SDL_AudioQuit();
		return 0;
	}
	static int lua_SDL_AudioDeviceConnected(lutok::state& state){
		//SDL_AudioDeviceConnected
		return 0;
	}
	static int lua_SDL_GetNumAudioDrivers(lutok::state& state){
		state.push_integer(SDL_GetNumAudioDrivers());
		return 1;
	}
	static int lua_SDL_GetNumAudioDevices(lutok::state& state){
		state.push_integer(SDL_GetNumAudioDevices( (state.to_boolean(1)) ? 1 : 0));
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

	void init_audio(moduleDef & module){
		module["audioInit"] = lua_SDL_AudioInit;
		module["audioQuit"] = lua_SDL_AudioQuit;
	}
}