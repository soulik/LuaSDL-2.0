#include "objects/audiospec.hpp"
#include <lua.hpp>
namespace LuaSDL {
	int AudioSpec::getFreq(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		stack->push<int>(audiospec->freq);
		return 1;
	}
	int AudioSpec::setFreq(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		audiospec->freq = stack->to<int>(1);
		return 0;
	}
	int AudioSpec::getFormat(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		stack->push<int>(audiospec->format);
		return 1;
	}
	int AudioSpec::setFormat(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		audiospec->format = static_cast<SDL_AudioFormat>(stack->to<int>(1));
		return 0;
	}
	int AudioSpec::getChannels(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		stack->push<int>(audiospec->channels);
		return 1;
	}
	int AudioSpec::setChannels(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		audiospec->channels = static_cast<Uint8>(stack->to<int>(1));
		return 0;
	}
	int AudioSpec::getSilence(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		stack->push<int>(audiospec->silence);
		return 1;
	}
	int AudioSpec::getSamples(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		stack->push<int>(audiospec->samples);
		return 1;
	}
	int AudioSpec::setSamples(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		audiospec->samples = static_cast<Uint16>(stack->to<int>(1));
		return 0;
	}
	int AudioSpec::getPadding(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		stack->push<int>(audiospec->padding);
		return 1;
	}
	int AudioSpec::setPadding(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		audiospec->padding = static_cast<Uint16>(stack->to<int>(1));
		return 0;
	}
	int AudioSpec::getSize(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		stack->push<int>(audiospec->size);
		return 1;
	}
	int AudioSpec::getCallback(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		return 0;
	}
	int AudioSpec::getUserdata(State & state, SDL_AudioSpec * audiospec) {
		Stack * stack = state.stack;
		return 0;
	}

	SDL_AudioSpec * AudioSpec::constructor(State & state, bool & managed){
		AudioSpec * interfaceAudioSpec = state.getInterface<AudioSpec>("LuaSDL_AudioSpec");

		SDL_AudioSpec * audiospec = new SDL_AudioSpec;

		audiospec->freq = 0;
		audiospec->format = 0;
		audiospec->channels = 0;
		audiospec->silence = 0;
		audiospec->samples = 0;
		audiospec->padding = 0;
		audiospec->size = 0;
		audiospec->callback = nullptr;
		audiospec->userdata = nullptr;

		return audiospec;
	}

	void initAudioSpec(State * state, Module & module){
		INIT_OBJECT(AudioSpec);
		//INIT_OBJECT(AudioSpec);
		//module["AudioSpec"] = lua_AudioSpec;
	}

};
