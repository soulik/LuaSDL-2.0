local names = {"delay", "button", "interval", "level", "attackLength", "attackLevel", "fadeLength",	"fadeLevel","magnitude", "offset", "phase", "rightSat", "leftSat", "rightCoeff", "leftCoeff", "deadband", "center", "start", "end", "largeMagnitude", "smallMagnitude",	"channels", "period", "data", "samples"}
local names123 = {"RightSat", "LeftSat", "RightCoeff", "LeftCoeff", "Deadband", "Center",}

local values = {
	["delay"] = "delay",
	["button"] = "button",
	["interval"] = "interval", 
	["level"] = "level", 
	["attackLength"] = "attack_length",
	["attackLevel"] = "attack_level", 
	["fadeLength"] = "fade_length",
	["fadeLevel"] = "fade_level",
	["magnitude"] = "magnitude",
	["offset"] = "offset",
	["phase"] = "phase",
	["rightSat"] = "right_sat",
	["leftSat"] = "left_sat",
	["rightCoeff"] = "right_coeff",
	["leftCoeff"] = "left_coeff",
	["deadband"] = "deadband",
	["center"] = "center",
	["start"] = "start",
	["end"] = "end",
	["largeMagnitude"] = "large_magnitude",
	["smallMagnitude"] = "small_magnitude",
	["channels"] = "channels", 
	["period"] = "period", 
	["data"] = "data", 
	["samples"]= "samples",
}

local values123 = {
	["rightsat"] = "right_sat",
	["leftsat"] = "left_sat",
	["rightcoeff"] = "right_coeff",
	["leftcoeff"] = "left_coeff",
	["deadband"] = "deadband",
	["center"] = "center",
}

local template = [[
	int inline HapticEffect::get{{Name}}(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;

		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			stack->push<int>(hapticEffect->effect.constant.{{param}});
			return 1;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			stack->push<int>(hapticEffect->effect.periodic.{{param}});
			return 1;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			stack->push<int>(hapticEffect->effect.condition.{{param}});
			return 1;
		case SDL_HAPTIC_RAMP:
			stack->push<int>(hapticEffect->effect.ramp.{{param}});
			return 1;
		case SDL_HAPTIC_LEFTRIGHT:
			stack->push<int>(hapticEffect->effect.leftright.{{param}});
			return 1;
		case SDL_HAPTIC_CUSTOM:
			stack->push<int>(hapticEffect->effect.custom.{{param}});
			return 1;
		}
		return 0;
	}
	int inline HapticEffect::set{{Name}}(State & state, HapticEffect_pack * hapticEffect){
		Stack * stack = state.stack;
		switch (hapticEffect->effect.type){
		case SDL_HAPTIC_CONSTANT:
			hapticEffect->effect.constant.{{param}} = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SINE:
#ifdef SDL_HAPTIC_SQUARE
		case SDL_HAPTIC_SQUARE:
#endif
		case SDL_HAPTIC_TRIANGLE:
		case SDL_HAPTIC_SAWTOOTHUP:
		case SDL_HAPTIC_SAWTOOTHDOWN:
			hapticEffect->effect.periodic.{{param}} = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_SPRING:
		case SDL_HAPTIC_DAMPER:
		case SDL_HAPTIC_INERTIA:
		case SDL_HAPTIC_FRICTION:
			hapticEffect->effect.condition.{{param}} = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_RAMP:
			hapticEffect->effect.ramp.{{param}} = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_LEFTRIGHT:
			hapticEffect->effect.leftright.{{param}} = stack->to<int>(1);
			return 0;
		case SDL_HAPTIC_CUSTOM:
			hapticEffect->effect.custom.{{param}} = stack->to<int>(1);
			return 0;
		}
		return 0;
	}

]]

local template123 = [[
int inline HapticEffect::get{{Name}}{{i}}(State & state, HapticEffect_pack * hapticEffect){
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
			stack->push<int>(hapticEffect->effect.condition.{{param}}[{{i123}}]);
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
	int inline HapticEffect::set{{Name}}{{i}}(State & state, HapticEffect_pack * hapticEffect){
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
			hapticEffect->effect.condition.{{param}}[{{i123}}] = stack->to<int>(1);
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

]]
--[[
for _, name in ipairs(names) do
	local Name = name:sub(1,1):upper()..name:sub(2):lower()
	local output = template:gsub("{{(%w+)}}", {
		Name = Name,
		param = values[name],
	})
	print(output)
end
--]]
for _, Name in ipairs(names123) do
	local name = Name:lower()
	for i=1,3 do
		local output = template123:gsub("{{(%w+)}}", {
			Name = Name,
			param = values123[name],
			i = i,
			i123 = i-1,
		})
		print(output)
	end
end