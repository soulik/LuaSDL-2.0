#ifndef LUA_SDL_OBJECTS_HAPTIC_H
#define LUA_SDL_OBJECTS_HAPTIC_H

#include "common.hpp"

namespace LuaSDL {

	class Haptic : public Object < SDL_Haptic > {
	public:
		explicit Haptic(State * state) : Object<SDL_Haptic>(state) {
			LUTOK_METHOD("pause", &Haptic::pause);
			LUTOK_METHOD("unpause", &Haptic::unpause);
			LUTOK_METHOD("query", &Haptic::query);
			LUTOK_METHOD("stopAll", &Haptic::stopAll);
			LUTOK_METHOD("stopEffect", &Haptic::stopEffect);
			LUTOK_METHOD("runEffect", &Haptic::runEffect);
			LUTOK_METHOD("effectStatus", &Haptic::getEffectStatus);
			LUTOK_METHOD("effectSupported", &Haptic::isEffectSupported);

			LUTOK_METHOD("rumbleInit", &Haptic::rumbleInit);
			LUTOK_METHOD("rumblePlay", &Haptic::rumblePlay);
			LUTOK_METHOD("rumbleStop", &Haptic::rumbleStop);

			LUTOK_PROPERTY("index", &Haptic::getIndex, &Haptic::nullMethod);
			LUTOK_PROPERTY("numAxes", &Haptic::getNumAxes, &Haptic::nullMethod);
			LUTOK_PROPERTY("numEffects", &Haptic::getNumEffects, &Haptic::nullMethod);
			LUTOK_PROPERTY("numEffectsPlaying", &Haptic::getNumEffectsPlaying, &Haptic::nullMethod);
			LUTOK_PROPERTY("rumbleSupported", &Haptic::isRumbleSupported, &Haptic::nullMethod);
			LUTOK_PROPERTY("autocenter", &Haptic::nullMethod, &Haptic::setAutoCenter);
			LUTOK_PROPERTY("gain", &Haptic::nullMethod, &Haptic::setGain);
		}

		SDL_Haptic * constructor(State & state, bool & managed);

		void destructor(State & state, SDL_Haptic * haptic){
			SDL_HapticClose(haptic);
		}

		int inline pause(State & state, SDL_Haptic * haptic);
		int inline unpause(State & state, SDL_Haptic * haptic);
		int inline query(State & state, SDL_Haptic * haptic);
		int inline stopAll(State & state, SDL_Haptic * haptic);
		int inline stopEffect(State & state, SDL_Haptic * haptic);
		int inline runEffect(State & state, SDL_Haptic * haptic);
		int inline getEffectStatus(State & state, SDL_Haptic * haptic);
		int inline isEffectSupported(State & state, SDL_Haptic * haptic);

		int inline rumbleInit(State & state, SDL_Haptic * haptic);
		int inline rumblePlay(State & state, SDL_Haptic * haptic);
		int inline rumbleStop(State & state, SDL_Haptic * haptic);
		int inline isRumbleSupported(State & state, SDL_Haptic * haptic);

		int inline getIndex(State & state, SDL_Haptic * haptic);
		int inline getNumAxes(State & state, SDL_Haptic * haptic);
		int inline getNumEffects(State & state, SDL_Haptic * haptic);
		int inline getNumEffectsPlaying(State & state, SDL_Haptic * haptic);

		int inline setAutoCenter(State & state, SDL_Haptic * haptic);
		int inline setGain(State & state, SDL_Haptic * haptic);
	};
}

#endif