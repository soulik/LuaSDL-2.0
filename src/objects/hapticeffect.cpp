#include "objects/haptic.hpp"
#include "objects/hapticeffect.hpp"

namespace LuaSDL {

	HapticEffect_pack * HapticEffect::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		HapticEffect_pack * he = new HapticEffect_pack;
		he->id = -1;
		he->haptic = nullptr;
		SDL_memset(&he->effect, 0, sizeof(SDL_HapticEffect));
		he->effect.custom.data = nullptr;
		he->effect.custom.samples = 0;
		he->effect.custom.channels = 1;
		return he;
	}

	int inline HapticEffect::getId(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		stack->push<int>(hapticEffect->id);
		return 1;
	}

	int HapticEffect::apply(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		Haptic * interfaceHaptic = state.getInterface<Haptic>("LuaSDL_Haptic");
		if (stack->is<LUA_TUSERDATA>(1)){
			SDL_Haptic * haptic = interfaceHaptic->get(1);
			if (haptic){
				int id = SDL_HapticNewEffect(haptic, &hapticEffect->effect);
				if (id >= 0){
					hapticEffect->id = id;
					hapticEffect->haptic = haptic;
					stack->push<bool>(true);
				}
				else{
					stack->push<bool>(false);
				}
				return 1;
			}
		}
		return 0;
	}

	int HapticEffect::run(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		if (hapticEffect->id>=0 && hapticEffect->haptic){
			int iterations = SDL_HAPTIC_INFINITY;
			if (stack->is<LUA_TNUMBER>(1)){
				iterations = stack->to<int>(1);
			}
			stack->push<bool>(SDL_HapticRunEffect(hapticEffect->haptic, hapticEffect->id, iterations) == 0);
			return 1;
		}
		else{
			return 0;
		}
	}
	int HapticEffect::stop(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		if (hapticEffect->id >= 0 && hapticEffect->haptic){
			stack->push<bool>(SDL_HapticStopEffect(hapticEffect->haptic, hapticEffect->id) == 0);
			return 1;
		}
		else{
			return 0;
		}
	}

	int HapticEffect::getStatus(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		if (hapticEffect->id >= 0 && hapticEffect->haptic){
			stack->push<int>(SDL_HapticGetEffectStatus(hapticEffect->haptic, hapticEffect->id));
			return 1;
		}
		else{
			return 0;
		}
	}

	int HapticEffect::update(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		if (hapticEffect->id >= 0 && hapticEffect->haptic){
			stack->push<bool>(SDL_HapticUpdateEffect(hapticEffect->haptic, hapticEffect->id, &hapticEffect->effect) == 0);
			return 1;
		}
		else{
			return 0;
		}
	}

	int HapticEffect::isSupported(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		if (hapticEffect->id >= 0 && hapticEffect->haptic){
			stack->push<bool>(SDL_HapticEffectSupported(hapticEffect->haptic, &hapticEffect->effect) == 0);
			return 1;
		}
		else{
			return 0;
		}
	}

	int inline HapticEffect::getType(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		stack->push<int>(hapticEffect->effect.type);
		return 1;
	}
	int inline HapticEffect::setType(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		int newType = stack->to<int>(1);
		if (hapticEffect->effect.type == SDL_HAPTIC_CUSTOM && newType != SDL_HAPTIC_CUSTOM){
			if (hapticEffect->effect.custom.data){
				SDL_free(hapticEffect->effect.custom.data);
			}
		}
		hapticEffect->effect.type = newType;
		return 0;
	}
	int inline HapticEffect::getDirectionType(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.direction.type);
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.direction.type);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.direction.type);
			return 1;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.direction.type);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.direction.type);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setDirectionType(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.direction.type = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.direction.type = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.direction.type = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.direction.type = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.direction.type = stack->to<int>(1);
			return 0;
		}
		return 0;
	}

	int inline HapticEffect::getDirection1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.direction.dir[0]);
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.direction.dir[0]);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.direction.dir[0]);
			return 1;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.direction.dir[0]);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.direction.dir[0]);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setDirection1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.direction.dir[0] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.direction.dir[0] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.direction.dir[0] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.direction.dir[0] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.direction.dir[0] = stack->to<int>(1);
			return 0;
		}
		return 0;
	}

	int inline HapticEffect::getDirection2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.direction.dir[1]);
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.direction.dir[1]);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.direction.dir[1]);
			return 1;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.direction.dir[1]);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.direction.dir[1]);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setDirection2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.direction.dir[1] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.direction.dir[1] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.direction.dir[1] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.direction.dir[1] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.direction.dir[1] = stack->to<int>(1);
			return 0;
		}
		return 0;
	}

	int inline HapticEffect::getDirection3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.direction.dir[2]);
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.direction.dir[2]);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.direction.dir[2]);
			return 1;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.direction.dir[2]);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.direction.dir[2]);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setDirection3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.direction.dir[2] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.direction.dir[2] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.direction.dir[2] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.direction.dir[2] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.direction.dir[2] = stack->to<int>(1);
			return 0;
		}
		return 0;
	}

	int inline HapticEffect::getLength(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.length);
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.length);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.length);
			return 1;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.length);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			stack->push<int>(hapticEffect->effect.leftright.length);
			return 1;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.length);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setLength(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.length = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.length = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.length = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.length = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			hapticEffect->effect.leftright.length = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.length = stack->to<int>(1);
			return 0;
		}
		return 0;
	}
	int inline HapticEffect::getDelay(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.delay);
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.delay);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.delay);
			return 1;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.delay);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.delay);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setDelay(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.delay = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.delay = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.delay = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.delay = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.delay = stack->to<int>(1);
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getButton(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.button);
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.button);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.button);
			return 1;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.button);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.button);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setButton(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.button = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.button = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.button = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.button = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.button = stack->to<int>(1);
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getInterval(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.interval);
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.interval);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.interval);
			return 1;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.interval);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.interval);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setInterval(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.interval = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.interval = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.interval = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.interval = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.interval = stack->to<int>(1);
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getLevel(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.level);
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}
	int inline HapticEffect::setLevel(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.level = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getAttackLength(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.attack_length);
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.attack_length);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.attack_length);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.attack_length);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setAttackLength(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.attack_length = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.attack_length = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.attack_length = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.attack_length = stack->to<int>(1);
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getAttackLevel(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.attack_level);
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.attack_level);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.attack_level);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.attack_level);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setAttackLevel(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.attack_level = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.attack_level = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.attack_level = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.attack_level = stack->to<int>(1);
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getFadeLength(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.fade_length);
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.fade_length);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.fade_length);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.fade_length);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setFadeLength(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.fade_length = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.fade_length = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.fade_length = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.fade_length = stack->to<int>(1);
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getFadeLevel(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.fade_level);
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.fade_level);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.fade_level);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.fade_level);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setFadeLevel(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.fade_level = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.fade_level = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.fade_level = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.fade_level = stack->to<int>(1);
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getMagnitude(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.magnitude);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}
	int inline HapticEffect::setMagnitude(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.magnitude = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getOffset(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.offset);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}
	int inline HapticEffect::setOffset(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.offset = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getPhase(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.phase);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}
	int inline HapticEffect::setPhase(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.phase = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getRightSat1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.right_sat[0]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setRightSat1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.right_sat[0] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getRightSat2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.right_sat[1]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setRightSat2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.right_sat[1] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getRightSat3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.right_sat[2]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setRightSat3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.right_sat[2] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getLeftSat1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.left_sat[0]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setLeftSat1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.left_sat[0] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getLeftSat2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.left_sat[1]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setLeftSat2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.left_sat[1] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getLeftSat3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.left_sat[2]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setLeftSat3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.left_sat[2] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getRightCoeff1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.right_coeff[0]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setRightCoeff1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.right_coeff[0] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getRightCoeff2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.right_coeff[1]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setRightCoeff2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.right_coeff[1] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getRightCoeff3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.right_coeff[2]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setRightCoeff3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.right_coeff[2] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getLeftCoeff1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.left_coeff[0]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setLeftCoeff1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.left_coeff[0] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getLeftCoeff2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.left_coeff[1]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setLeftCoeff2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.left_coeff[1] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getLeftCoeff3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.left_coeff[2]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setLeftCoeff3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.left_coeff[2] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getDeadband1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.deadband[0]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setDeadband1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.deadband[0] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getDeadband2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.deadband[1]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setDeadband2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.deadband[1] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getDeadband3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.deadband[2]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setDeadband3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.deadband[2] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getCenter1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.center[0]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setCenter1(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.center[0] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getCenter2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.center[1]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setCenter2(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.center[1] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getCenter3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.center[2]);
			return 1;
		case SDL_HAPTIC_RAMP:
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setCenter3(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.center[2] = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}

	int inline HapticEffect::getStart(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.start);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}
	int inline HapticEffect::setStart(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.start = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getEnd(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.end);
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}
	int inline HapticEffect::setEnd(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.end = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getLargeMagnitude(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			stack->push<int>(hapticEffect->effect.leftright.large_magnitude);
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}
	int inline HapticEffect::setLargeMagnitude(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			hapticEffect->effect.leftright.large_magnitude = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getSmallMagnitude(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			stack->push<int>(hapticEffect->effect.leftright.small_magnitude);
			return 1;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}
	int inline HapticEffect::setSmallMagnitude(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			hapticEffect->effect.leftright.small_magnitude = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_CUSTOM:
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getChannels(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.channels);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setChannels(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.channels = stack->to<int>(1);
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getPeriod(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.period);
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.period);
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setPeriod(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.period = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.period = stack->to<int>(1);
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getData(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			if (hapticEffect->effect.custom.data){
				stack->pushLString(reinterpret_cast<char*>(hapticEffect->effect.custom.data), hapticEffect->effect.custom.samples * hapticEffect->effect.custom.channels * sizeof(Uint16));
			}
			else{
				stack->push<const std::string &>("");
			}
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::setData(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			if (stack->is<LUA_TSTRING>(1) && hapticEffect->effect.custom.channels>0){
				const std::string data = stack->toLString(1);
				Uint16 samples = (data.length() / hapticEffect->effect.custom.channels) / sizeof(Uint16);

				if (hapticEffect->effect.custom.data && hapticEffect->effect.custom.samples != samples){
					hapticEffect->effect.custom.data = static_cast<Uint16*>(SDL_realloc(hapticEffect->effect.custom.data, data.length()));
				}
				else{
					hapticEffect->effect.custom.data = static_cast<Uint16*>(SDL_malloc(data.length()));
				}
				hapticEffect->effect.custom.samples = samples;
				SDL_memcpy(hapticEffect->effect.custom.data, data.c_str(), data.length());
			}
			return 0;
		}
		return 0;
	}


	int inline HapticEffect::getSamples(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			return 0;
		case SDL_HAPTIC_RAMP:
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			return 0;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.samples);
			return 1;
		}
		return 0;
	}

	void initHapticEffect(State * state, Module & module){
		INIT_OBJECT(HapticEffect);
		//module["hapticOpened"] = lua_SDL_HapticOpened;
		//module["hapticName"] = lua_SDL_HapticName;
		//module["numHaptics"] = lua_SDL_NumHaptics;
	}
};