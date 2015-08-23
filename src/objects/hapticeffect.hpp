#ifndef LUA_SDL_OBJECTS_HAPTIC_EFFECT_H
#define LUA_SDL_OBJECTS_HAPTIC_EFFECT_H

#include "common.hpp"

namespace LuaSDL {

	struct HapticEffect_pack {
		SDL_HapticEffect effect;
		SDL_Haptic * haptic;
		int id;
	};

	class HapticEffect : public Object < HapticEffect_pack > {
	public:
		explicit HapticEffect(State * state) : Object<HapticEffect_pack>(state) {
			LUTOK_METHOD("apply", &HapticEffect::apply);
			
			LUTOK_METHOD("run", &HapticEffect::run);
			LUTOK_METHOD("stop", &HapticEffect::stop);
			LUTOK_METHOD("update", &HapticEffect::update);

			LUTOK_PROPERTY("id", &HapticEffect::getId, &HapticEffect::nullMethod);
			LUTOK_PROPERTY("status", &HapticEffect::getStatus, &HapticEffect::nullMethod);
			LUTOK_PROPERTY("supported", &HapticEffect::isSupported, &HapticEffect::nullMethod);

			LUTOK_PROPERTY("type", &HapticEffect::getType, &HapticEffect::setType);
			LUTOK_PROPERTY("directionType", &HapticEffect::getDirectionType, &HapticEffect::setDirectionType);
			LUTOK_PROPERTY("direction1", &HapticEffect::getDirection1, &HapticEffect::setDirection1);
			LUTOK_PROPERTY("direction2", &HapticEffect::getDirection2, &HapticEffect::setDirection2);
			LUTOK_PROPERTY("direction3", &HapticEffect::getDirection3, &HapticEffect::setDirection3);
			LUTOK_PROPERTY("length", &HapticEffect::getLength, &HapticEffect::setLength);
			LUTOK_PROPERTY("delay", &HapticEffect::getDelay, &HapticEffect::setDelay);
			LUTOK_PROPERTY("button", &HapticEffect::getButton, &HapticEffect::setButton);
			LUTOK_PROPERTY("interval", &HapticEffect::getInterval, &HapticEffect::setInterval);
			LUTOK_PROPERTY("level", &HapticEffect::getLevel, &HapticEffect::setLevel);
			LUTOK_PROPERTY("attackLength", &HapticEffect::getAttackLength, &HapticEffect::setAttackLength);
			LUTOK_PROPERTY("attackLevel", &HapticEffect::getAttackLevel, &HapticEffect::setAttackLevel);
			LUTOK_PROPERTY("fadeLength", &HapticEffect::getFadeLength, &HapticEffect::setFadeLength);
			LUTOK_PROPERTY("fadeLevel", &HapticEffect::getFadeLevel, &HapticEffect::setFadeLevel);
			LUTOK_PROPERTY("magnitude", &HapticEffect::getMagnitude, &HapticEffect::setMagnitude);
			LUTOK_PROPERTY("offset", &HapticEffect::getOffset, &HapticEffect::setOffset);
			LUTOK_PROPERTY("phase", &HapticEffect::getPhase, &HapticEffect::setPhase);
			
			LUTOK_PROPERTY("rightSat1", &HapticEffect::getRightSat1, &HapticEffect::setRightSat1);
			LUTOK_PROPERTY("rightSat2", &HapticEffect::getRightSat2, &HapticEffect::setRightSat2);
			LUTOK_PROPERTY("rightSat3", &HapticEffect::getRightSat3, &HapticEffect::setRightSat3);
			LUTOK_PROPERTY("leftSat1", &HapticEffect::getLeftSat1, &HapticEffect::setLeftSat1);
			LUTOK_PROPERTY("leftSat2", &HapticEffect::getLeftSat2, &HapticEffect::setLeftSat2);
			LUTOK_PROPERTY("leftSat3", &HapticEffect::getLeftSat3, &HapticEffect::setLeftSat3);
			LUTOK_PROPERTY("rightCoeff1", &HapticEffect::getRightCoeff1, &HapticEffect::setRightCoeff1);
			LUTOK_PROPERTY("rightCoeff2", &HapticEffect::getRightCoeff2, &HapticEffect::setRightCoeff2);
			LUTOK_PROPERTY("rightCoeff3", &HapticEffect::getRightCoeff3, &HapticEffect::setRightCoeff3);
			LUTOK_PROPERTY("leftCoeff1", &HapticEffect::getLeftCoeff1, &HapticEffect::setLeftCoeff1);
			LUTOK_PROPERTY("leftCoeff2", &HapticEffect::getLeftCoeff2, &HapticEffect::setLeftCoeff2);
			LUTOK_PROPERTY("leftCoeff3", &HapticEffect::getLeftCoeff3, &HapticEffect::setLeftCoeff3);
			LUTOK_PROPERTY("deadband1", &HapticEffect::getDeadband1, &HapticEffect::setDeadband1);
			LUTOK_PROPERTY("deadband2", &HapticEffect::getDeadband2, &HapticEffect::setDeadband2);
			LUTOK_PROPERTY("deadband3", &HapticEffect::getDeadband3, &HapticEffect::setDeadband3);
			LUTOK_PROPERTY("center1", &HapticEffect::getCenter1, &HapticEffect::setCenter1);
			LUTOK_PROPERTY("center2", &HapticEffect::getCenter2, &HapticEffect::setCenter2);
			LUTOK_PROPERTY("center3", &HapticEffect::getCenter3, &HapticEffect::setCenter3);

			LUTOK_PROPERTY("start", &HapticEffect::getStart, &HapticEffect::setStart);
			LUTOK_PROPERTY("end", &HapticEffect::getEnd, &HapticEffect::setEnd);
			LUTOK_PROPERTY("largeMagnitude", &HapticEffect::getLargeMagnitude, &HapticEffect::setLargeMagnitude);
			LUTOK_PROPERTY("smallMagnitude", &HapticEffect::getSmallMagnitude, &HapticEffect::setSmallMagnitude);
			LUTOK_PROPERTY("channels", &HapticEffect::getChannels, &HapticEffect::setChannels);
			LUTOK_PROPERTY("period", &HapticEffect::getPeriod, &HapticEffect::setPeriod);
			LUTOK_PROPERTY("data", &HapticEffect::getData, &HapticEffect::setData);
			LUTOK_PROPERTY("samples", &HapticEffect::getSamples, &HapticEffect::nullMethod);
		}

		HapticEffect_pack * constructor(State & state, bool & managed);

		void destructor(State & state, HapticEffect_pack * hapticEffect){
			if (hapticEffect->effect.type == SDL_HAPTIC_CUSTOM && hapticEffect->effect.custom.data){
				SDL_free(hapticEffect->effect.custom.data);
			}
			if (hapticEffect->id >= 0 && hapticEffect->haptic){
				SDL_HapticDestroyEffect(hapticEffect->haptic, hapticEffect->id);
			}
			delete hapticEffect;
		}

		int inline getId(State & state, HapticEffect_pack * hapticEffect);
		int inline getStatus(State & state, HapticEffect_pack * hapticEffect);
		int inline isSupported(State & state, HapticEffect_pack * hapticEffect);

		int apply(State & state, HapticEffect_pack * hapticEffect);
		int run(State & state, HapticEffect_pack * hapticEffect);
		int stop(State & state, HapticEffect_pack * hapticEffect);
		int update(State & state, HapticEffect_pack * hapticEffect);

		int inline getType(State & state, HapticEffect_pack * hapticEffect);
		int inline setType(State & state, HapticEffect_pack * hapticEffect);
		int inline getDirectionType(State & state, HapticEffect_pack * hapticEffect);
		int inline setDirectionType(State & state, HapticEffect_pack * hapticEffect);
		int inline getDirection1(State & state, HapticEffect_pack * hapticEffect);
		int inline setDirection1(State & state, HapticEffect_pack * hapticEffect);
		int inline getDirection2(State & state, HapticEffect_pack * hapticEffect);
		int inline setDirection2(State & state, HapticEffect_pack * hapticEffect);
		int inline getDirection3(State & state, HapticEffect_pack * hapticEffect);
		int inline setDirection3(State & state, HapticEffect_pack * hapticEffect);
		int inline getLength(State & state, HapticEffect_pack * hapticEffect);
		int inline setLength(State & state, HapticEffect_pack * hapticEffect);
		int inline getDelay(State & state, HapticEffect_pack * hapticEffect);
		int inline setDelay(State & state, HapticEffect_pack * hapticEffect);
		int inline getButton(State & state, HapticEffect_pack * hapticEffect);
		int inline setButton(State & state, HapticEffect_pack * hapticEffect);
		int inline getInterval(State & state, HapticEffect_pack * hapticEffect);
		int inline setInterval(State & state, HapticEffect_pack * hapticEffect);
		int inline getLevel(State & state, HapticEffect_pack * hapticEffect);
		int inline setLevel(State & state, HapticEffect_pack * hapticEffect);
		int inline getAttackLength(State & state, HapticEffect_pack * hapticEffect);
		int inline setAttackLength(State & state, HapticEffect_pack * hapticEffect);
		int inline getAttackLevel(State & state, HapticEffect_pack * hapticEffect);
		int inline setAttackLevel(State & state, HapticEffect_pack * hapticEffect);
		int inline getFadeLength(State & state, HapticEffect_pack * hapticEffect);
		int inline setFadeLength(State & state, HapticEffect_pack * hapticEffect);
		int inline getFadeLevel(State & state, HapticEffect_pack * hapticEffect);
		int inline setFadeLevel(State & state, HapticEffect_pack * hapticEffect);
		int inline getMagnitude(State & state, HapticEffect_pack * hapticEffect);
		int inline setMagnitude(State & state, HapticEffect_pack * hapticEffect);
		int inline getOffset(State & state, HapticEffect_pack * hapticEffect);
		int inline setOffset(State & state, HapticEffect_pack * hapticEffect);
		int inline getPhase(State & state, HapticEffect_pack * hapticEffect);
		int inline setPhase(State & state, HapticEffect_pack * hapticEffect);
		
		int inline getRightSat1(State & state, HapticEffect_pack * hapticEffect);
		int inline getRightSat2(State & state, HapticEffect_pack * hapticEffect);
		int inline getRightSat3(State & state, HapticEffect_pack * hapticEffect);
		int inline setRightSat1(State & state, HapticEffect_pack * hapticEffect);
		int inline setRightSat2(State & state, HapticEffect_pack * hapticEffect);
		int inline setRightSat3(State & state, HapticEffect_pack * hapticEffect);
		int inline getLeftSat1(State & state, HapticEffect_pack * hapticEffect);
		int inline getLeftSat2(State & state, HapticEffect_pack * hapticEffect);
		int inline getLeftSat3(State & state, HapticEffect_pack * hapticEffect);
		int inline setLeftSat1(State & state, HapticEffect_pack * hapticEffect);
		int inline setLeftSat2(State & state, HapticEffect_pack * hapticEffect);
		int inline setLeftSat3(State & state, HapticEffect_pack * hapticEffect);
		int inline getRightCoeff1(State & state, HapticEffect_pack * hapticEffect);
		int inline getRightCoeff2(State & state, HapticEffect_pack * hapticEffect);
		int inline getRightCoeff3(State & state, HapticEffect_pack * hapticEffect);
		int inline setRightCoeff1(State & state, HapticEffect_pack * hapticEffect);
		int inline setRightCoeff2(State & state, HapticEffect_pack * hapticEffect);
		int inline setRightCoeff3(State & state, HapticEffect_pack * hapticEffect);
		int inline getLeftCoeff1(State & state, HapticEffect_pack * hapticEffect);
		int inline getLeftCoeff2(State & state, HapticEffect_pack * hapticEffect);
		int inline getLeftCoeff3(State & state, HapticEffect_pack * hapticEffect);
		int inline setLeftCoeff1(State & state, HapticEffect_pack * hapticEffect);
		int inline setLeftCoeff2(State & state, HapticEffect_pack * hapticEffect);
		int inline setLeftCoeff3(State & state, HapticEffect_pack * hapticEffect);
		int inline getDeadband1(State & state, HapticEffect_pack * hapticEffect);
		int inline getDeadband2(State & state, HapticEffect_pack * hapticEffect);
		int inline getDeadband3(State & state, HapticEffect_pack * hapticEffect);
		int inline setDeadband1(State & state, HapticEffect_pack * hapticEffect);
		int inline setDeadband2(State & state, HapticEffect_pack * hapticEffect);
		int inline setDeadband3(State & state, HapticEffect_pack * hapticEffect);
		int inline getCenter1(State & state, HapticEffect_pack * hapticEffect);
		int inline getCenter2(State & state, HapticEffect_pack * hapticEffect);
		int inline getCenter3(State & state, HapticEffect_pack * hapticEffect);
		int inline setCenter1(State & state, HapticEffect_pack * hapticEffect);
		int inline setCenter2(State & state, HapticEffect_pack * hapticEffect);
		int inline setCenter3(State & state, HapticEffect_pack * hapticEffect);

		int inline getStart(State & state, HapticEffect_pack * hapticEffect);
		int inline setStart(State & state, HapticEffect_pack * hapticEffect);
		int inline getEnd(State & state, HapticEffect_pack * hapticEffect);
		int inline setEnd(State & state, HapticEffect_pack * hapticEffect);
		int inline getLargeMagnitude(State & state, HapticEffect_pack * hapticEffect);
		int inline setLargeMagnitude(State & state, HapticEffect_pack * hapticEffect);
		int inline getSmallMagnitude(State & state, HapticEffect_pack * hapticEffect);
		int inline setSmallMagnitude(State & state, HapticEffect_pack * hapticEffect);
		int inline getChannels(State & state, HapticEffect_pack * hapticEffect);
		int inline setChannels(State & state, HapticEffect_pack * hapticEffect);
		int inline getPeriod(State & state, HapticEffect_pack * hapticEffect);
		int inline setPeriod(State & state, HapticEffect_pack * hapticEffect);
		int inline getData(State & state, HapticEffect_pack * hapticEffect);
		int inline setData(State & state, HapticEffect_pack * hapticEffect);
		int inline getSamples(State & state, HapticEffect_pack * hapticEffect);
	};
}

#endif