#include "objects/event.hpp"
#include <SDL_syswm.h>
#include <lua.hpp>

namespace LuaSDL {
	int inline Event::pushEvent(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(SDL_PushEvent(event));
		return 1;
	}

	//common getters/setters

	int inline Event::getEventType(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->type);
		return 1;
	}
	int inline Event::setEventType(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->type = stack->to<int>(1);
		return 0;
	}
	int inline Event::getTimestamp(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(((SDL_CommonEvent*)event)->timestamp);
		return 1;
	}
	int inline Event::setTimestamp(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		((SDL_CommonEvent*)event)->timestamp = stack->to<int>(1);
		return 0;
	}

	//event specific getters/setters

	int inline Event::getWindow_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->window.windowID);
		return 1;
	}
	int inline Event::setWindow_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->window.windowID = stack->to<int>(1);
		return 0;
	}

	int inline Event::getWindow_event(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->window.event);
		return 1;
	}
	int inline Event::setWindow_event(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->window.event = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getWindow_data1(State & state, SDL_Event * event){
		Stack * stack = state.stack;
		stack->push<int>(event->window.data1);
		return 1;
	}
	int inline Event::setWindow_data1(State & state, SDL_Event * event){
		Stack * stack = state.stack;
		event->window.data1 = stack->to<int>(1);
		return 0;
	}

	int inline Event::getWindow_data2(State & state, SDL_Event * event){
		Stack * stack = state.stack;
		stack->push<int>(event->window.data2);
		return 1;
	}
	int inline Event::setWindow_data2(State & state, SDL_Event * event){
		Stack * stack = state.stack;
		event->window.data2 = stack->to<int>(1);
		return 0;
	}

	int inline Event::getKeyboard_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->key.windowID);
		return 1;
	}
	int inline Event::setKeyboard_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->key.windowID = stack->to<int>(1);
		return 0;
	}

	int inline Event::getKeyboard_state(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->key.state);
		return 1;
	}
	int inline Event::setKeyboard_state(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->key.state = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getKeyboard_repeat(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->key.repeat);
		return 1;
	}
	int inline Event::setKeyboard_repeat(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->key.repeat = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getKeyboard_keysym_scancode(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->key.keysym.scancode);
		return 1;
	}
	int inline Event::setKeyboard_keysym_scancode(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->key.keysym.scancode = (SDL_Scancode)stack->to<int>(1);
		return 0;
	}
	int inline Event::getKeyboard_keysym_keycode(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(SDL_SCANCODE_TO_KEYCODE(event->key.keysym.scancode));
		return 1;
	}
	int inline Event::setKeyboard_keysym_keycode(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->key.keysym.scancode = (SDL_Scancode)(stack->to<int>(1) & ~SDLK_SCANCODE_MASK);
		return 0;
	}

	int inline Event::getKeyboard_keysym_sym(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->key.keysym.sym);
		return 1;
	}
	int inline Event::setKeyboard_keysym_sym(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->key.keysym.sym = stack->to<int>(1);
		return 0;
	}

	int inline Event::getKeyboard_keysym_mod(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->key.keysym.mod);
		return 1;
	}
	int inline Event::setKeyboard_keysym_mod(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->key.keysym.mod = (Uint16)stack->to<int>(1);
		return 0;
	}

	int inline Event::getKeyboard_keysym_unicode(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->key.keysym.unused);
		return 1;
	}
	int inline Event::setKeyboard_keysym_unicode(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->key.keysym.unused = stack->to<int>(1);
		return 0;
	}

	int inline Event::getTextediting_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->edit.windowID);
		return 1;
	}
	int inline Event::setTextediting_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->edit.windowID = stack->to<int>(1);
		return 0;
	}

	int inline Event::getTextediting_text(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<const std::string &>(event->edit.text);
		return 1;
	}
	int inline Event::setTextediting_text(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		const std::string text = stack->to<const std::string>(1);
		size_t text_len = text.length();
		size_t len = (text_len < SDL_TEXTEDITINGEVENT_TEXT_SIZE - 1) ? text_len : SDL_TEXTEDITINGEVENT_TEXT_SIZE - 1;
		strncpy(event->edit.text, text.c_str(), len);
		return 0;
	}

	int inline Event::getTextediting_start(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->edit.start);
		return 1;
	}
	int inline Event::setTextediting_start(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->edit.start = stack->to<int>(1);
		return 0;
	}

	int inline Event::getTextediting_length(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->edit.length);
		return 1;
	}
	int inline Event::setTextediting_length(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->edit.length = stack->to<int>(1);
		return 0;
	}

	int inline Event::getTextinput_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->text.windowID);
		return 1;
	}
	int inline Event::setTextinput_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->text.windowID = stack->to<int>(1);
		return 0;
	}

	int inline Event::getTextinput_text(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<const std::string &>(event->text.text);
		return 1;
	}
	int inline Event::setTextinput_text(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		const std::string text = stack->to<const std::string>(1);
		size_t text_len = text.length();
		size_t len = (text_len < SDL_TEXTINPUTEVENT_TEXT_SIZE - 1) ? text_len : SDL_TEXTINPUTEVENT_TEXT_SIZE - 1;
		strncpy(event->text.text, text.c_str(), len);
		return 0;
	}

	int inline Event::getMousemotion_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->motion.windowID);
		return 1;
	}
	int inline Event::setMousemotion_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->motion.windowID = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousemotion_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->motion.which);
		return 1;
	}
	int inline Event::setMousemotion_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->motion.which = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousemotion_state(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->motion.state);
		return 1;
	}
	int inline Event::setMousemotion_state(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->motion.state = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousemotion_x(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->motion.x);
		return 1;
	}
	int inline Event::setMousemotion_x(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->motion.x = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousemotion_y(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->motion.y);
		return 1;
	}
	int inline Event::setMousemotion_y(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->motion.y = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousemotion_xrel(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->motion.xrel);
		return 1;
	}
	int inline Event::setMousemotion_xrel(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->motion.xrel = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousemotion_yrel(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->motion.yrel);
		return 1;
	}
	int inline Event::setMousemotion_yrel(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->motion.yrel = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousebutton_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->button.windowID);
		return 1;
	}
	int inline Event::setMousebutton_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->button.windowID = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousebutton_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->button.which);
		return 1;
	}
	int inline Event::setMousebutton_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->button.which = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousebutton_button(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->button.button);
		return 1;
	}
	int inline Event::setMousebutton_button(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->button.button = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousebutton_state(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->button.state);
		return 1;
	}
	int inline Event::setMousebutton_state(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->button.state = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousebutton_x(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->button.x);
		return 1;
	}
	int inline Event::setMousebutton_x(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->button.x = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousebutton_y(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->button.y);
		return 1;
	}
	int inline Event::setMousebutton_y(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->button.y = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousewheel_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->wheel.windowID);
		return 1;
	}
	int inline Event::setMousewheel_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->wheel.windowID = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousewheel_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->wheel.which);
		return 1;
	}
	int inline Event::setMousewheel_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->wheel.which = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousewheel_x(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->wheel.x);
		return 1;
	}
	int inline Event::setMousewheel_x(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->wheel.x = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMousewheel_y(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->wheel.y);
		return 1;
	}
	int inline Event::setMousewheel_y(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->wheel.y = stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoyaxis_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jaxis.which);
		return 1;
	}
	int inline Event::setJoyaxis_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jaxis.which = stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoyaxis_axis(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jaxis.axis);
		return 1;
	}
	int inline Event::setJoyaxis_axis(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jaxis.axis = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoyaxis_value(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jaxis.value);
		return 1;
	}
	int inline Event::setJoyaxis_value(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jaxis.value = (Sint16)stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoyball_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jball.which);
		return 1;
	}
	int inline Event::setJoyball_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jball.which = stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoyball_ball(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jball.ball);
		return 1;
	}
	int inline Event::setJoyball_ball(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jball.ball = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoyball_xrel(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jball.xrel);
		return 1;
	}
	int inline Event::setJoyball_xrel(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jball.xrel = (Sint16)stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoyball_yrel(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jball.yrel);
		return 1;
	}
	int inline Event::setJoyball_yrel(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jball.yrel = (Sint16)stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoyhat_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jhat.which);
		return 1;
	}
	int inline Event::setJoyhat_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jhat.which = stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoyhat_hat(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jhat.hat);
		return 1;
	}
	int inline Event::setJoyhat_hat(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jhat.hat = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoyhat_value(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jhat.value);
		return 1;
	}
	int inline Event::setJoyhat_value(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jhat.value = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoybutton_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jbutton.which);
		return 1;
	}
	int inline Event::setJoybutton_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jbutton.which = stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoybutton_button(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jbutton.button);
		return 1;
	}
	int inline Event::setJoybutton_button(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jbutton.button = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoybutton_state(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jbutton.state);
		return 1;
	}
	int inline Event::setJoybutton_state(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jbutton.state = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getJoydevice_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->jdevice.which);
		return 1;
	}
	int inline Event::setJoydevice_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->jdevice.which = stack->to<int>(1);
		return 0;
	}

	int inline Event::getControlleraxis_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->caxis.which);
		return 1;
	}
	int inline Event::setControlleraxis_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->caxis.which = stack->to<int>(1);
		return 0;
	}

	int inline Event::getControlleraxis_axis(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->caxis.axis);
		return 1;
	}
	int inline Event::setControlleraxis_axis(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->caxis.axis = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getControlleraxis_value(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->caxis.value);
		return 1;
	}
	int inline Event::setControlleraxis_value(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->caxis.value = (Sint16)stack->to<int>(1);
		return 0;
	}

	int inline Event::getControllerbutton_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->cbutton.which);
		return 1;
	}
	int inline Event::setControllerbutton_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->cbutton.which = stack->to<int>(1);
		return 0;
	}

	int inline Event::getControllerbutton_button(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->cbutton.button);
		return 1;
	}
	int inline Event::setControllerbutton_button(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->cbutton.button = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getControllerbutton_state(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->cbutton.state);
		return 1;
	}
	int inline Event::setControllerbutton_state(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->cbutton.state = (Uint8)stack->to<int>(1);
		return 0;
	}

	int inline Event::getControllerdevice_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->cdevice.which);
		return 1;
	}
	int inline Event::setControllerdevice_which(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->cdevice.which = stack->to<int>(1);
		return 0;
	}

	int inline Event::getTouchfinger_touchId(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>((const int)event->tfinger.touchId);
		return 1;
	}
	int inline Event::setTouchfinger_touchId(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->tfinger.touchId = stack->to<int>(1);
		return 0;
	}

	int inline Event::getTouchfinger_fingerId(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>((const int)event->tfinger.fingerId);
		return 1;
	}
	int inline Event::setTouchfinger_fingerId(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->tfinger.fingerId = stack->to<int>(1);
		return 0;
	}

	int inline Event::getTouchfinger_x(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(event->tfinger.x);
		return 1;
	}
	int inline Event::setTouchfinger_x(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->tfinger.x = (float)stack->to<LUA_NUMBER>(1);
		return 0;
	}

	int inline Event::getTouchfinger_y(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(event->tfinger.y);
		return 1;
	}
	int inline Event::setTouchfinger_y(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->tfinger.y = (float)stack->to<LUA_NUMBER>(1);
		return 0;
	}

	int inline Event::getTouchfinger_dx(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(event->tfinger.dx);
		return 1;
	}
	int inline Event::setTouchfinger_dx(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->tfinger.dx = (float)stack->to<LUA_NUMBER>(1);
		return 0;
	}

	int inline Event::getTouchfinger_dy(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(event->tfinger.dy);
		return 1;
	}
	int inline Event::setTouchfinger_dy(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->tfinger.dy = (float)stack->to<LUA_NUMBER>(1);
		return 0;
	}

	int inline Event::getMultigesture_touchId(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>((const int)event->mgesture.touchId);
		return 1;
	}
	int inline Event::setMultigesture_touchId(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->mgesture.touchId = stack->to<int>(1);
		return 0;
	}

	int inline Event::getMultigesture_dTheta(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(event->mgesture.dTheta);
		return 1;
	}
	int inline Event::setMultigesture_dTheta(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->mgesture.dTheta = (float)stack->to<LUA_NUMBER>(1);
		return 0;
	}

	int inline Event::getMultigesture_dDist(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(event->mgesture.dDist);
		return 1;
	}
	int inline Event::setMultigesture_dDist(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->mgesture.dDist = (float)stack->to<LUA_NUMBER>(1);
		return 0;
	}

	int inline Event::getMultigesture_x(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(event->mgesture.x);
		return 1;
	}
	int inline Event::setMultigesture_x(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->mgesture.x = (float)stack->to<LUA_NUMBER>(1);
		return 0;
	}

	int inline Event::getMultigesture_y(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(event->mgesture.y);
		return 1;
	}
	int inline Event::setMultigesture_y(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->mgesture.y = (float)stack->to<LUA_NUMBER>(1);
		return 0;
	}

	int inline Event::getMultigesture_numFingers(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->mgesture.numFingers);
		return 1;
	}
	int inline Event::setMultigesture_numFingers(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->mgesture.numFingers = (Uint16)stack->to<int>(1);
		return 0;
	}

	int inline Event::getDollargesture_touchId(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>((const int)event->dgesture.touchId);
		return 1;
	}
	int inline Event::setDollargesture_touchId(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->dgesture.touchId = stack->to<int>(1);
		return 0;
	}

	int inline Event::getDollargesture_gestureId(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>((const int)event->dgesture.gestureId);
		return 1;
	}
	int inline Event::setDollargesture_gestureId(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->dgesture.gestureId = stack->to<int>(1);
		return 0;
	}

	int inline Event::getDollargesture_numFingers(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->dgesture.numFingers);
		return 1;
	}
	int inline Event::setDollargesture_numFingers(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->dgesture.numFingers = stack->to<int>(1);
		return 0;
	}

	int inline Event::getDollargesture_error(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(event->dgesture.error);
		return 1;
	}
	int inline Event::setDollargesture_error(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->dgesture.error = (float)stack->to<LUA_NUMBER>(1);
		return 0;
	}

	int inline Event::getDollargesture_x(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(event->dgesture.x);
		return 1;
	}
	int inline Event::setDollargesture_x(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->dgesture.x = (float)stack->to<LUA_NUMBER>(1);
		return 0;
	}

	int inline Event::getDollargesture_y(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<LUA_NUMBER>(event->dgesture.y);
		return 1;
	}
	int inline Event::setDollargesture_y(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->dgesture.y = (float)stack->to<LUA_NUMBER>(1);
		return 0;
	}

	int inline Event::getDrop_file(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<const std::string &>(event->drop.file);
		return 1;
	}
	int Event::setDrop_file(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		const std::string text = stack->to<const std::string>(1);
		size_t text_len = text.length();
		size_t len = (text_len < FILENAME_MAX - 1) ? text_len : FILENAME_MAX - 1;

		if (event->drop.file)
			event->drop.file = (char*)SDL_realloc(event->drop.file, len + 1);

		strncpy(event->drop.file, text.c_str(), len);
		return 0;
	}

	int inline Event::getUser_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->user.windowID);
		return 1;
	}
	int inline Event::setUser_windowID(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->user.windowID = stack->to<int>(1);
		return 0;
	}

	int inline Event::getUser_code(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		stack->push<int>(event->user.code);
		return 1;
	}
	int inline Event::setUser_code(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		event->user.code = stack->to<int>(1);
		return 0;
	}

	int inline Event::getUser_data1(State & state, SDL_Event * event){
		Stack * stack = state.stack;

		if (event->user.code == LUA_SDL_TIMER_CODE){
			int ref = reinterpret_cast<int>(event->user.data1);
			stack->rawGet(ref, LUA_REGISTRYINDEX);
			return 1;
		}
		else{
			int ref = static_cast<int>(reinterpret_cast<intptr_t>(event->user.data1));
			if (ref != LUA_NOREF && ref != 0){
				stack->regValue(ref);

				if (stack->is<LUA_TNIL>(-1)){
					stack->pop(1);
					stack->push<void*>(event->user.data1);
				}
				return 1;
			}
		}
		return 0;
	}

	int inline Event::setUser_data1(State & state, SDL_Event * event){
		Stack * stack = state.stack;
		if (stack->is<LUA_TLIGHTUSERDATA>(1)){
			event->user.data1 = stack->to<void*>(1);
		}
		else{
			int oldRef = static_cast<int>(reinterpret_cast<intptr_t>(event->user.data1));
			if (oldRef != LUA_NOREF && oldRef != 0){
				stack->unref(oldRef);
			}
			if (!stack->is<LUA_TNIL>(1)){
				stack->pushValue(1);
				int ref = stack->ref();
				event->user.data1 = reinterpret_cast<void*>(ref);
			}
		}
		return 0;
	}

	int inline Event::getUser_data2(State & state, SDL_Event * event){
		Stack * stack = state.stack;
		int ref = static_cast<int>(reinterpret_cast<intptr_t>(event->user.data2));
		if (ref != LUA_NOREF && ref != 0){
			stack->regValue(ref);
			if (stack->is<LUA_TNIL>(-1)){
				stack->pop(1);
				stack->push<void*>(event->user.data2);
			}
			return 1;
		}
		return 0;
	}
	int inline Event::setUser_data2(State & state, SDL_Event * event){
		Stack * stack = state.stack;
		if (stack->is<LUA_TLIGHTUSERDATA>(1)){
			event->user.data2 = stack->to<void*>(1);
		}
		else{
			int oldRef = static_cast<int>(reinterpret_cast<intptr_t>(event->user.data2));
			if (oldRef != LUA_NOREF && oldRef != 0){
				stack->unref(oldRef);
			}
			if (!stack->is<LUA_TNIL>(1)){
				stack->pushValue(1);
				int ref = stack->ref();
				event->user.data2 = reinterpret_cast<void*>(ref);
			}
		}
		return 0;
	}

	static int lua_SDL_PollEvent(State & state){
		Stack * stack = state.stack;
		Event * interfaceEvent = state.getInterface<Event>("LuaSDL_Event");

		if (stack->is<LUA_TNIL>(1)){
			SDL_Event event;
			if (SDL_PollEvent(&event) > 0){
				SDL_Event * new_event = new SDL_Event;
				memcpy(new_event, &event, sizeof(SDL_Event));
				interfaceEvent->push(new_event, true);
				return 1;
			}
		}
		else{
			SDL_Event * event = interfaceEvent->get(1);
			if (event){
				if (SDL_PollEvent(event) > 0){
					if (stack->is<LUA_TBOOLEAN>(2) && (stack->to<bool>(1) == true)){
						interfaceEvent->push(event);
					}
					else{
						stack->push<bool>(true);
					}
					return 1;
				}
			}
		}
		return 0;
	}
	
	SDL_Event * Event::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		Event * interfaceEvent = state.getInterface<Event>("LuaSDL_Event");
		SDL_Event * event = new SDL_Event;
		event->drop.file = nullptr;
		event->syswm.msg = nullptr;
		return event;
	}

	static int lua_SDL_PumpEvents(State & state){
		Stack * stack = state.stack;
		SDL_PumpEvents();
		return 0;
	}

	static int lua_SDL_HasEvent(State & state){
		Stack * stack = state.stack;
		stack->push<bool>(
			SDL_HasEvent(
			stack->to<int>(1)) == SDL_TRUE);
		return 1;
	}

	static int lua_SDL_HasEvents(State & state){
		Stack * stack = state.stack;
		stack->push<bool>(
			SDL_HasEvents(
			stack->to<int>(1),
			stack->to<int>(2)) == SDL_TRUE);
		return 1;
	}

	static int lua_SDL_FlushEvent(State & state){
		Stack * stack = state.stack;
		SDL_FlushEvent(stack->to<int>(1));
		return 0;
	}

	static int lua_SDL_FlushEvents(State & state){
		Stack * stack = state.stack;
		SDL_FlushEvents(stack->to<int>(1), stack->to<int>(2));
		return 0;
	}

	static int lua_SDL_WaitEvent(State & state){
		Stack * stack = state.stack;
		Event * interfaceEvent = state.getInterface<Event>("LuaSDL_Event");
		
		if (stack->is<LUA_TNIL>(1)){
			SDL_Event event;
			if (SDL_WaitEvent(&event) > 0){
				SDL_Event * new_event = new SDL_Event;
				memcpy(new_event, &event, sizeof(SDL_Event));
				interfaceEvent->push(new_event, true);
				return 1;
			}
		}
		else{
			SDL_Event * event = interfaceEvent->get(1);
			if (event){
				if (SDL_WaitEvent(event) > 0){
					if (stack->is<LUA_TBOOLEAN>(2) && (stack->to<bool>(1) == true)){
						interfaceEvent->push(event);
					}
					else{
						stack->push<bool>(true);
					}
					return 1;
				}

			}
		}
		return 0;
	}

	static int lua_SDL_WaitEventTimeout(State & state){
		Stack * stack = state.stack;
		Event * interfaceEvent = state.getInterface<Event>("LuaSDL_Event");

		if ((stack->getTop() == 1) && stack->is<LUA_TNUMBER>(1)){
			SDL_Event event;
			if (SDL_WaitEventTimeout(&event, stack->to<int>(1)) > 0){
				
				SDL_Event * new_event = new SDL_Event;
				memcpy(new_event, &event, sizeof(SDL_Event));
				interfaceEvent->push(new_event, true);
				return 1;
			}
		}
		else{
			if ((stack->getTop() == 2) && stack->is<LUA_TNUMBER>(2)){
				SDL_Event * event = interfaceEvent->get(1);
				if (event){
					if (SDL_WaitEventTimeout(event, stack->to<int>(1)) > 0){
						if (stack->is<LUA_TBOOLEAN>(2) && (stack->to<bool>(1) == true)){
							interfaceEvent->push(event);
						}
						else{
							stack->push<bool>(true);
						}
						return 1;
					}
				}
			}
		}
		return 0;
	}

	int Event::getSyswm_msg(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		SDL_SysWMmsg * msg = event->syswm.msg;

		stack->newTable();
		stack->setField("timestamp", (const int)event->syswm.timestamp);

		if (msg){
			stack->newTable();
			stack->push<int>(1);
			stack->push<int>(msg->version.major);
			stack->setTable();
			stack->push<int>(2);
			stack->push<int>(msg->version.minor);
			stack->setTable();
			stack->push<int>(3);
			stack->push<int>(msg->version.patch);
			stack->setTable();
			stack->push<const std::string &>("version");
			stack->setTable(); // "version" field

			stack->setField("subsystem", (const int)msg->subsystem);

			switch (msg->subsystem){
#if defined(SDL_VIDEO_DRIVER_WINDOWS)
			case SDL_SYSWM_WINDOWS:
				stack->setField("hwnd", (const int)msg->msg.win.hwnd);
				stack->setField("msg", (const int)msg->msg.win.msg);
				stack->setField("wParam", (const int)msg->msg.win.wParam);
				stack->setField("lParam", (const int)msg->msg.win.lParam);

				stack->push<const std::string &>("wParam_ptr");
				stack->push<void*>((void*)msg->msg.win.wParam);
				stack->setTable(); // "wParam_ptr" field

				stack->push<const std::string &>("lParam_ptr");
				stack->push<void*>((void*)msg->msg.win.lParam);
				stack->setTable(); // "lParam_ptr" field

				break;
#endif
#if defined(SDL_VIDEO_DRIVER_X11)
			case SDL_SYSWM_X11:
				//msg->msg.x11.event
				break;
#endif
#if defined(SDL_VIDEO_DRIVER_DIRECTFB)
			case SDL_SYSWM_DIRECTFB:
				//msg->msg.dfb.event
				break;
#endif
#if defined(SDL_VIDEO_DRIVER_COCOA)
			case SDL_VIDEO_DRIVER_COCOA:
				//msg->msg.cocoa
				break;
#endif
#if defined(SDL_VIDEO_DRIVER_UIKIT)
			case SDL_VIDEO_DRIVER_UIKIT:
				//msg->msg.uikit
				break;
#endif
			case SDL_SYSWM_UNKNOWN:
				break;
			}
		}
		return 1;
	}

	int Event::setSyswm_msg(State & state, SDL_Event * event) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TTABLE>(1)){
			event->syswm.type = SDL_SYSWMEVENT;
			if (event->syswm.msg == nullptr){
				event->syswm.msg = reinterpret_cast<SDL_SysWMmsg*>(SDL_malloc(sizeof(SDL_SysWMmsg)));
			}
			SDL_GetVersion(&event->syswm.msg->version);

			stack->getField("subsystem", 1);
			event->syswm.msg->subsystem = (SDL_SYSWM_TYPE)stack->to<int>(-1);
			stack->pop(1);
			event->syswm.timestamp = SDL_GetTicks();

			switch (event->syswm.msg->subsystem){
#if defined(SDL_VIDEO_DRIVER_WINDOWS)
			case SDL_SYSWM_WINDOWS:
				stack->getField("hwnd", 1);
				event->syswm.msg->msg.win.hwnd = (HWND)stack->to<int>(-1);

				stack->getField("msg", 1);
				event->syswm.msg->msg.win.msg = (UINT)stack->to<int>(-1);

				stack->getField("wParam", 1);
				event->syswm.msg->msg.win.wParam = (WPARAM)stack->to<int>(-1);

				stack->getField("lParam", 1);
				event->syswm.msg->msg.win.lParam = (LPARAM)stack->to<int>(-1);
				stack->pop(4);
				break;
#endif
#if defined(SDL_VIDEO_DRIVER_X11)
			case SDL_SYSWM_X11:
				//msg->msg.x11.event
				break;
#endif
#if defined(SDL_VIDEO_DRIVER_DIRECTFB)
			case SDL_SYSWM_DIRECTFB:
				//msg->msg.dfb.event
				break;
#endif
#if defined(SDL_VIDEO_DRIVER_COCOA)
			case SDL_VIDEO_DRIVER_COCOA:
				//msg->msg.cocoa
				break;
#endif
#if defined(SDL_VIDEO_DRIVER_UIKIT)
			case SDL_VIDEO_DRIVER_UIKIT:
				//msg->msg.uikit
				break;
#endif
			case SDL_SYSWM_UNKNOWN:
				break;
			}
		}
		return 0;
	}

	void initEvent(State * state, Module & module){
		INIT_OBJECT(Event);
		//module["Event"] = lua_SDL_Event;
		module["pollEvent"] = lua_SDL_PollEvent;
		module["pumpEvents"] = lua_SDL_PumpEvents;
		module["hasEvent"] = lua_SDL_HasEvent;
		module["hasEvents"] = lua_SDL_HasEvents;
		module["flushEvent"] = lua_SDL_FlushEvent;
		module["flushEvents"] = lua_SDL_FlushEvents;
		module["waitEvent"] = lua_SDL_WaitEvent;
		module["waitEventTimeout"] = lua_SDL_WaitEventTimeout;
	}

};
