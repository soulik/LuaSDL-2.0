#include "objects/gamecontroller.hpp"
#include "objects/joystick.hpp"
#include <lua.hpp>

namespace LuaSDL {
	int GameController::getName(State & state, SDL_GameController * gamecontroller) {
		Stack * stack = state.stack;
		const char * name = SDL_GameControllerName(gamecontroller);
		if (name){
			stack->push<const std::string &>(name);
			return 1;
		}
		else{
			return 0;
		}
	}
	int GameController::isAttached(State & state, SDL_GameController * gamecontroller) {
		Stack * stack = state.stack;
		stack->push<bool>(SDL_GameControllerGetAttached(gamecontroller) == SDL_TRUE);
		return 1;
	}

	int GameController::getAxis(State & state, SDL_GameController * gamecontroller){
		Stack * stack = state.stack;
		stack->push<int>(SDL_GameControllerGetAxis(gamecontroller, static_cast<SDL_GameControllerAxis>(stack->to<int>(1))));
		return 1;
	}
	int GameController::getButton(State & state, SDL_GameController * gamecontroller){
		Stack * stack = state.stack;
		stack->push<int>(SDL_GameControllerGetButton(gamecontroller, static_cast<SDL_GameControllerButton>(stack->to<int>(1))));
		return 1;
	}

	int GameController::getJoystick(State & state, SDL_GameController * gamecontroller){
		Stack * stack = state.stack;
		Joystick * interfaceJoystick = state.getInterface<Joystick>("LuaSDL_Joystick");
		SDL_Joystick * joystick = SDL_GameControllerGetJoystick(gamecontroller);
		if (joystick){
			interfaceJoystick->push(joystick);
			return 1;
		}
		else{
			return 0;
		}
	}

	int GameController::getMapping(State & state, SDL_GameController * gamecontroller){
		Stack * stack = state.stack;
		char * mapping = SDL_GameControllerMapping(gamecontroller);
		if (mapping){
			stack->push<const std::string &>(mapping);
			return 1;
		}
		else{
			return 0;
		}
	}
	int GameController::setMapping(State & state, SDL_GameController * gamecontroller){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			const std::string mapping = stack->to<const std::string>(1);
			stack->push<bool>(SDL_GameControllerAddMapping(mapping.c_str()));
		}
		return 0;
	}

	int GameController::getBindForAxis(State & state, SDL_GameController * gamecontroller){
		Stack * stack = state.stack;

		SDL_GameControllerButtonBind bind = SDL_GameControllerGetBindForAxis(gamecontroller, static_cast<SDL_GameControllerAxis>(stack->to<int>(1)));
		
		stack->newTable();
		stack->setField<int>("bindType", bind.bindType);
		switch (bind.bindType){
		case SDL_CONTROLLER_BINDTYPE_AXIS:
			stack->setField<int>("value", bind.value.axis);
			break;
		case SDL_CONTROLLER_BINDTYPE_BUTTON:
			stack->setField<int>("value", bind.value.button);
			break;
		case SDL_CONTROLLER_BINDTYPE_HAT:
			stack->push<const std::string &>("value");
			stack->newTable();
			stack->setField<int>("hat", bind.value.hat.hat);
			stack->setField<int>("mask", bind.value.hat.hat_mask);
			stack->setTable();
			break;
		}
		
		return 1;
	}
	int GameController::getBindForButton(State & state, SDL_GameController * gamecontroller){
		Stack * stack = state.stack;
		SDL_GameControllerButtonBind bind = SDL_GameControllerGetBindForButton(gamecontroller, static_cast<SDL_GameControllerButton>(stack->to<int>(1)));

		stack->newTable();
		stack->setField<int>("bindType", bind.bindType);
		switch (bind.bindType){
		case SDL_CONTROLLER_BINDTYPE_AXIS:
			stack->setField<int>("value", bind.value.axis);
			break;
		case SDL_CONTROLLER_BINDTYPE_BUTTON:
			stack->setField<int>("value", bind.value.button);
			break;
		case SDL_CONTROLLER_BINDTYPE_HAT:
			stack->push<const std::string &>("value");
			stack->newTable();
			stack->setField<int>("hat", bind.value.hat.hat);
			stack->setField<int>("mask", bind.value.hat.hat_mask);
			stack->setTable();
			break;
		}
		return 1;
	}


	SDL_GameController * GameController::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		GameController * interfaceGameController = state.getInterface<GameController>("LuaSDL_GameController");
		SDL_GameController * gamecontroller = SDL_GameControllerOpen(stack->to<int>(1));
		return gamecontroller;
	}

	static int lua_SDL_GameControllerNameForIndex(State & state){
		Stack * stack = state.stack;
		const char * name = SDL_GameControllerNameForIndex(stack->to<int>(1));
		if (name){
			stack->push<const std::string &>(name);
			return 1;
		}
		else{
			return 0;
		}
	}

	static int lua_SDL_IsGameController(State & state){
		Stack * stack = state.stack;
		stack->push<bool>(SDL_IsGameController(stack->to<int>(1)) == SDL_TRUE);
		return 1;
	}

	static int lua_SDL_GameControllerUpdate(State & state){
		SDL_GameControllerUpdate();
		return 0;
	}

	static int lua_SDL_GameControllerGetAxisFromString(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			const std::string name = stack->to<const std::string>(1);
			SDL_GameControllerAxis axis = SDL_GameControllerGetAxisFromString(name.c_str());
			if (axis == SDL_CONTROLLER_AXIS_INVALID){
				stack->push<bool>(false);
			}
			else{
				stack->push<int>(axis);
			}
			return 1;
		}
		else{
			return 0;
		}
	}

	static int lua_SDL_GameControllerGetButtonFromString(State & state){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			const std::string name = stack->to<const std::string>(1);
			SDL_GameControllerButton button = SDL_GameControllerGetButtonFromString(name.c_str());
			if (button == SDL_CONTROLLER_BUTTON_INVALID){
				stack->push<bool>(false);
			}
			else{
				stack->push<int>(button);
			}
			return 1;
		}
		else{
			return 0;
		}
	}

	void initGameController(State * state, Module & module){
		INIT_OBJECT(GameController);
		//module["GameController"] = lua_SDL_GameControllerOpen;
		module["gameControllerNameForIndex"] = lua_SDL_GameControllerNameForIndex;
		module["isGameController"] = lua_SDL_IsGameController;
		module["gameControllerUpdate"] = lua_SDL_GameControllerUpdate;
		module["gameControllerGetAxisFromString"] = lua_SDL_GameControllerGetAxisFromString;
		module["gameControllerGetButtonFromString"] = lua_SDL_GameControllerGetButtonFromString;

	}

};