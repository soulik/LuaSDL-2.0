#include "objects/haptic.hpp"
#include "objects/hapticeffect.hpp"

namespace LuaSDL {

	SDL_Haptic * Haptic::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			SDL_Haptic * haptic = SDL_HapticOpen(stack->to<int>(1));
			if (haptic){
				return haptic;
			}
		}
		return nullptr;
	}

	inline static int lua_SDL_HapticOpened(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			stack->push<bool>(SDL_HapticOpened(stack->to<int>(1)) == 1);
			return 1;
		}
		return 0;
	}

	inline static int lua_SDL_HapticName(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			stack->push<const std::string &>(SDL_HapticName(stack->to<int>(1)));
			return 1;
		}
		return 0;
	}

	inline static int lua_SDL_NumHaptics(State & state){
		Stack * stack = state.stack;
		stack->push<int>(SDL_NumHaptics());
		return 1;
	}

	int inline Haptic::getIndex(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		stack->push<int>(SDL_HapticIndex(haptic));
		return 1;
	}

	int inline Haptic::getNumAxes(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		stack->push<int>(SDL_HapticNumAxes(haptic));
		return 1;
	}

	int inline Haptic::getNumEffects(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		stack->push<int>(SDL_HapticNumEffects(haptic));
		return 1;
	}

	int inline Haptic::getNumEffectsPlaying(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		stack->push<int>(SDL_HapticNumEffectsPlaying(haptic));
		return 1;
	}

	int inline Haptic::pause(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_HapticPause(haptic) == 0);
		return 1;
	}
	
	int inline Haptic::unpause(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_HapticUnpause(haptic) == 0);
		return 1;
	}

	int inline Haptic::query(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		stack->push<int>(SDL_HapticQuery(haptic));
		return 1;
	}

	int inline Haptic::stopAll(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_HapticStopAll(haptic) == 0);
		return 1;
	}
	int inline Haptic::stopEffect(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			stack->push<bool>(SDL_HapticStopEffect(haptic, stack->to<int>(1)) == 0);
			return 1;
		}
		else{
			return 0;
		}
	}
	int inline Haptic::runEffect(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			int iterations = SDL_HAPTIC_INFINITY;
			if (stack->is<LUA_TNUMBER>(2)){
				iterations = stack->to<int>(2);
			}

			stack->push<bool>(SDL_HapticRunEffect(haptic, stack->to<int>(1), iterations) == 0);
			return 1;
		}
		else{
			return 0;
		}
	}
	int inline Haptic::getEffectStatus(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			stack->push<int>(SDL_HapticGetEffectStatus(haptic, stack->to<int>(1)));
			return 1;
		}
		else{
			return 0;
		}
	}

	int inline Haptic::isEffectSupported(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		HapticEffect * interfaceHapticEffect = state.getInterface<HapticEffect>("LuaSDL_HapticEffect");
		if (stack->is<LUA_TUSERDATA>(1)){
			HapticEffect_pack * he = interfaceHapticEffect->get(1);
			if (he){
				stack->push<bool>(SDL_HapticEffectSupported(haptic, &he->effect) == SDL_TRUE);
				return 1;
			}
		}
		return 0;
	}


	int inline Haptic::rumbleInit(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_HapticRumbleInit(haptic) == 0);
		return 1;
	}
	int inline Haptic::rumblePlay(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TNUMBER>(2)){
			stack->push<bool>(SDL_HapticRumblePlay(haptic, stack->to<LUA_NUMBER>(1), stack->to<int>(2)) == 0);
			return 1;
		}
		else{
			return 0;
		}
	}
	int inline Haptic::rumbleStop(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_HapticRumbleStop(haptic) == 0);
		return 1;
	}
	int inline Haptic::isRumbleSupported(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_HapticRumbleSupported(haptic) == SDL_TRUE);
		return 1;
	}

	int inline Haptic::setAutoCenter(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			SDL_HapticSetAutocenter(haptic, stack->to<int>(1));
		}
		return 0;
	}

	int inline Haptic::setGain(State & state, SDL_Haptic * haptic){
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			SDL_HapticSetGain(haptic, stack->to<int>(1));
		}
		return 0;
	}



	void initHaptic(State * state, Module & module){
		INIT_OBJECT(Haptic);
		module["hapticOpened"] = lua_SDL_HapticOpened;
		module["hapticName"] = lua_SDL_HapticName;
		module["numHaptics"] = lua_SDL_NumHaptics;
	}
};