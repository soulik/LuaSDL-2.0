#ifndef LUA_SDL_OBJECTS_EVENT_H
#define LUA_SDL_OBJECTS_EVENT_H

#include "common.hpp"
#define LUA_SDL_TIMER_CODE	1000

namespace LuaSDL {

	class Event : public Object<SDL_Event> {
	public:
		explicit Event(State * state) : Object<SDL_Event>(state) {
			LUTOK_METHOD("push", &Event::pushEvent);
			//LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Event, "", null_method);

			LUTOK_PROPERTY("type", &Event::getEventType, &Event::setEventType);	
			LUTOK_PROPERTY("timestamp", &Event::getTimestamp, &Event::getTimestamp);	

			//SDL_WindowEvent
			LUTOK_PROPERTY("window_windowID", &Event::getWindow_windowID, &Event::setWindow_windowID);
			LUTOK_PROPERTY("window_event", &Event::getWindow_event, &Event::setWindow_event);
			LUTOK_PROPERTY("window_data1", &Event::getWindow_data1, &Event::setWindow_data1);
			LUTOK_PROPERTY("window_data2", &Event::getWindow_data2, &Event::setWindow_data2);

			//SDL_KeyboardEvent
			LUTOK_PROPERTY("keyboard_windowID", &Event::getKeyboard_windowID, &Event::setKeyboard_windowID);
			LUTOK_PROPERTY("keyboard_state", &Event::getKeyboard_state, &Event::setKeyboard_state);
			LUTOK_PROPERTY("keyboard_repeat", &Event::getKeyboard_repeat, &Event::setKeyboard_repeat);
			LUTOK_PROPERTY("keyboard_keysym_scancode", &Event::getKeyboard_keysym_scancode, &Event::setKeyboard_keysym_scancode);
			LUTOK_PROPERTY("keyboard_keysym_keycode", &Event::getKeyboard_keysym_keycode, &Event::setKeyboard_keysym_keycode);
			LUTOK_PROPERTY("keyboard_keysym_sym", &Event::getKeyboard_keysym_sym, &Event::setKeyboard_keysym_sym);
			LUTOK_PROPERTY("keyboard_keysym_mod", &Event::getKeyboard_keysym_mod, &Event::setKeyboard_keysym_mod);
			LUTOK_PROPERTY("keyboard_keysym_unicode", &Event::getKeyboard_keysym_unicode, &Event::setKeyboard_keysym_unicode);

			//SDL_TextEditingEvent
			LUTOK_PROPERTY("textediting_windowID", &Event::getTextediting_windowID, &Event::setTextediting_windowID);
			LUTOK_PROPERTY("textediting_text", &Event::getTextediting_text, &Event::setTextediting_text);
			LUTOK_PROPERTY("textediting_start", &Event::getTextediting_start, &Event::setTextediting_start);
			LUTOK_PROPERTY("textediting_length", &Event::getTextediting_length, &Event::setTextediting_length);

			//SDL_TextInputEvent
			LUTOK_PROPERTY("textinput_windowID", &Event::getTextinput_windowID, &Event::setTextinput_windowID);
			LUTOK_PROPERTY("textinput_text", &Event::getTextinput_text, &Event::setTextinput_text);

			//SDL_MouseMotionEvent
			LUTOK_PROPERTY("mousemotion_windowID", &Event::getMousemotion_windowID, &Event::setMousemotion_windowID);
			LUTOK_PROPERTY("mousemotion_which", &Event::getMousemotion_which, &Event::setMousemotion_which);
			LUTOK_PROPERTY("mousemotion_state", &Event::getMousemotion_state, &Event::setMousemotion_state);
			LUTOK_PROPERTY("mousemotion_x", &Event::getMousemotion_x, &Event::setMousemotion_x);
			LUTOK_PROPERTY("mousemotion_y", &Event::getMousemotion_y, &Event::setMousemotion_y);
			LUTOK_PROPERTY("mousemotion_xrel", &Event::getMousemotion_xrel, &Event::setMousemotion_xrel);
			LUTOK_PROPERTY("mousemotion_yrel", &Event::getMousemotion_yrel, &Event::setMousemotion_yrel);

			//SDL_MouseButtonEvent
			LUTOK_PROPERTY("mousebutton_windowID", &Event::getMousebutton_windowID, &Event::setMousebutton_windowID);
			LUTOK_PROPERTY("mousebutton_which", &Event::getMousebutton_which, &Event::setMousebutton_which);
			LUTOK_PROPERTY("mousebutton_button", &Event::getMousebutton_button, &Event::setMousebutton_button);
			LUTOK_PROPERTY("mousebutton_state", &Event::getMousebutton_state, &Event::setMousebutton_state);
			LUTOK_PROPERTY("mousebutton_x", &Event::getMousebutton_x, &Event::setMousebutton_x);
			LUTOK_PROPERTY("mousebutton_y", &Event::getMousebutton_y, &Event::setMousebutton_y);

			//SDL_MouseWheelEvent
			LUTOK_PROPERTY("mousewheel_windowID", &Event::getMousewheel_windowID, &Event::setMousewheel_windowID);
			LUTOK_PROPERTY("mousewheel_which", &Event::getMousewheel_which, &Event::setMousewheel_which);
			LUTOK_PROPERTY("mousewheel_x", &Event::getMousewheel_x, &Event::setMousewheel_x);
			LUTOK_PROPERTY("mousewheel_y", &Event::getMousewheel_y, &Event::setMousewheel_y);

			//SDL_JoyAxisEvent
			LUTOK_PROPERTY("joyaxis_which", &Event::getJoyaxis_which, &Event::setJoyaxis_which);
			LUTOK_PROPERTY("joyaxis_axis", &Event::getJoyaxis_axis, &Event::setJoyaxis_axis);
			LUTOK_PROPERTY("joyaxis_value", &Event::getJoyaxis_value, &Event::setJoyaxis_value);

			//SDL_JoyBallEvent
			LUTOK_PROPERTY("joyball_which", &Event::getJoyball_which, &Event::setJoyball_which);
			LUTOK_PROPERTY("joyball_ball", &Event::getJoyball_ball, &Event::setJoyball_ball);
			LUTOK_PROPERTY("joyball_xrel", &Event::getJoyball_xrel, &Event::setJoyball_xrel);
			LUTOK_PROPERTY("joyball_yrel", &Event::getJoyball_yrel, &Event::setJoyball_yrel);

			//SDL_JoyHatEvent
			LUTOK_PROPERTY("joyhat_which", &Event::getJoyhat_which, &Event::setJoyhat_which);
			LUTOK_PROPERTY("joyhat_hat", &Event::getJoyhat_hat, &Event::setJoyhat_hat);
			LUTOK_PROPERTY("joyhat_value", &Event::getJoyhat_value, &Event::setJoyhat_value);

			//SDL_JoyButtonEvent
			LUTOK_PROPERTY("joybutton_which", &Event::getJoybutton_which, &Event::setJoybutton_which);
			LUTOK_PROPERTY("joybutton_button", &Event::getJoybutton_button, &Event::setJoybutton_button);
			LUTOK_PROPERTY("joybutton_state", &Event::getJoybutton_state, &Event::setJoybutton_state);

			//SDL_JoyDeviceEvent
			LUTOK_PROPERTY("joydevice_which", &Event::getJoydevice_which, &Event::setJoydevice_which);

			//SDL_ControllerAxisEvent
			LUTOK_PROPERTY("controlleraxis_which", &Event::getControlleraxis_which, &Event::setControlleraxis_which);
			LUTOK_PROPERTY("controlleraxis_axis", &Event::getControlleraxis_axis, &Event::setControlleraxis_axis);
			LUTOK_PROPERTY("controlleraxis_value", &Event::getControlleraxis_value, &Event::setControlleraxis_value);

			//SDL_ControllerButtonEvent
			LUTOK_PROPERTY("controllerbutton_which", &Event::getControllerbutton_which, &Event::setControllerbutton_which);
			LUTOK_PROPERTY("controllerbutton_button", &Event::getControllerbutton_button, &Event::setControllerbutton_button);
			LUTOK_PROPERTY("controllerbutton_state", &Event::getControllerbutton_state, &Event::setControllerbutton_state);

			//SDL_ControllerDeviceEvent
			LUTOK_PROPERTY("controllerdevice_which", &Event::getControllerdevice_which, &Event::setControllerdevice_which);

			//SDL_TouchFingerEvent
			LUTOK_PROPERTY("touchfinger_touchId", &Event::getTouchfinger_touchId, &Event::setTouchfinger_touchId);
			LUTOK_PROPERTY("touchfinger_fingerId", &Event::getTouchfinger_fingerId, &Event::setTouchfinger_fingerId);
			LUTOK_PROPERTY("touchfinger_x", &Event::getTouchfinger_x, &Event::setTouchfinger_x);
			LUTOK_PROPERTY("touchfinger_y", &Event::getTouchfinger_y, &Event::setTouchfinger_y);
			LUTOK_PROPERTY("touchfinger_dx", &Event::getTouchfinger_dx, &Event::setTouchfinger_dx);
			LUTOK_PROPERTY("touchfinger_dy", &Event::getTouchfinger_dy, &Event::setTouchfinger_dy);

			//SDL_MultiGestureEvent
			LUTOK_PROPERTY("multigesture_touchId", &Event::getMultigesture_touchId, &Event::setMultigesture_touchId);
			LUTOK_PROPERTY("multigesture_dTheta", &Event::getMultigesture_dTheta, &Event::setMultigesture_dTheta);
			LUTOK_PROPERTY("multigesture_dDist", &Event::getMultigesture_dDist, &Event::setMultigesture_dDist);
			LUTOK_PROPERTY("multigesture_x", &Event::getMultigesture_x, &Event::setMultigesture_x);
			LUTOK_PROPERTY("multigesture_y", &Event::getMultigesture_y, &Event::setMultigesture_y);
			LUTOK_PROPERTY("multigesture_numFingers", &Event::getMultigesture_numFingers, &Event::setMultigesture_numFingers);

			//SDL_DollarGestureEvent
			LUTOK_PROPERTY("dollargesture_touchId", &Event::getDollargesture_touchId, &Event::setDollargesture_touchId);
			LUTOK_PROPERTY("dollargesture_gestureId", &Event::getDollargesture_gestureId, &Event::setDollargesture_gestureId);
			LUTOK_PROPERTY("dollargesture_numFingers", &Event::getDollargesture_numFingers, &Event::setDollargesture_numFingers);
			LUTOK_PROPERTY("dollargesture_error", &Event::getDollargesture_error, &Event::setDollargesture_error);
			LUTOK_PROPERTY("dollargesture_x", &Event::getDollargesture_x, &Event::setDollargesture_x);
			LUTOK_PROPERTY("dollargesture_y", &Event::getDollargesture_y, &Event::setDollargesture_y);

			//SDL_DropEvent
			LUTOK_PROPERTY("dropevent_file", &Event::getDrop_file, &Event::setDrop_file);

			//SDL_QuitEvent

			//SDL_UserEvent
			LUTOK_PROPERTY("userevent_windowID", &Event::getUser_windowID, &Event::setUser_windowID);
			LUTOK_PROPERTY("userevent_code", &Event::getUser_code, &Event::setUser_code);
			LUTOK_PROPERTY("userevent_data1", &Event::getUser_data1, &Event::setUser_data1);
			LUTOK_PROPERTY("userevent_data2", &Event::getUser_data2, &Event::setUser_data2);

			//SDL_SysWMEvent
			LUTOK_PROPERTY("syswm_msg", &Event::getSyswm_msg, &Event::setSyswm_msg);

		}

		void destructor(State & state, SDL_Event * event){
			if (event->type == SDL_DROPFILE){
				if (event->drop.file){
					SDL_free(event->drop.file);
				}
				if (event->syswm.msg){
					SDL_free(event->syswm.msg);
				}
			}
			delete event;
		}

		SDL_Event * constructor(State & state, bool & managed);

		int inline pushEvent(State & state, SDL_Event * event);

		//common getters/setters

		int inline getEventType(State & state, SDL_Event * event);
		int inline setEventType(State & state, SDL_Event * event);
		int inline getTimestamp(State & state, SDL_Event * event);
		int inline setTimestamp(State & state, SDL_Event * event);

		//event specific getters/setters

		int inline getWindow_windowID(State & state, SDL_Event * event);
		int inline setWindow_windowID(State & state, SDL_Event * event);

		int inline getWindow_event(State & state, SDL_Event * event);
		int inline setWindow_event(State & state, SDL_Event * event);

		int inline getWindow_data1(State & state, SDL_Event * event);
		int inline setWindow_data1(State & state, SDL_Event * event);

		int inline getWindow_data2(State & state, SDL_Event * event);
		int inline setWindow_data2(State & state, SDL_Event * event);

		int inline getKeyboard_windowID(State & state, SDL_Event * event);
		int inline setKeyboard_windowID(State & state, SDL_Event * event);

		int inline getKeyboard_state(State & state, SDL_Event * event);
		int inline setKeyboard_state(State & state, SDL_Event * event);

		int inline getKeyboard_repeat(State & state, SDL_Event * event);
		int inline setKeyboard_repeat(State & state, SDL_Event * event);

		int inline getKeyboard_keysym_scancode(State & state, SDL_Event * event);
		int inline setKeyboard_keysym_scancode(State & state, SDL_Event * event);
		int inline getKeyboard_keysym_keycode(State & state, SDL_Event * event);
		int inline setKeyboard_keysym_keycode(State & state, SDL_Event * event);

		int inline getKeyboard_keysym_sym(State & state, SDL_Event * event);
		int inline setKeyboard_keysym_sym(State & state, SDL_Event * event);

		int inline getKeyboard_keysym_mod(State & state, SDL_Event * event);
		int inline setKeyboard_keysym_mod(State & state, SDL_Event * event);

		int inline getKeyboard_keysym_unicode(State & state, SDL_Event * event);
		int inline setKeyboard_keysym_unicode(State & state, SDL_Event * event);

		int inline getTextediting_windowID(State & state, SDL_Event * event);
		int inline setTextediting_windowID(State & state, SDL_Event * event);

		int inline getTextediting_text(State & state, SDL_Event * event);
		int inline setTextediting_text(State & state, SDL_Event * event);

		int inline getTextediting_start(State & state, SDL_Event * event);
		int inline setTextediting_start(State & state, SDL_Event * event);

		int inline getTextediting_length(State & state, SDL_Event * event);
		int inline setTextediting_length(State & state, SDL_Event * event);

		int inline getTextinput_windowID(State & state, SDL_Event * event);
		int inline setTextinput_windowID(State & state, SDL_Event * event);

		int inline getTextinput_text(State & state, SDL_Event * event);
		int inline setTextinput_text(State & state, SDL_Event * event);

		int inline getMousemotion_windowID(State & state, SDL_Event * event);
		int inline setMousemotion_windowID(State & state, SDL_Event * event);

		int inline getMousemotion_which(State & state, SDL_Event * event);
		int inline setMousemotion_which(State & state, SDL_Event * event);

		int inline getMousemotion_state(State & state, SDL_Event * event);
		int inline setMousemotion_state(State & state, SDL_Event * event);

		int inline getMousemotion_x(State & state, SDL_Event * event);
		int inline setMousemotion_x(State & state, SDL_Event * event);

		int inline getMousemotion_y(State & state, SDL_Event * event);
		int inline setMousemotion_y(State & state, SDL_Event * event);

		int inline getMousemotion_xrel(State & state, SDL_Event * event);
		int inline setMousemotion_xrel(State & state, SDL_Event * event);

		int inline getMousemotion_yrel(State & state, SDL_Event * event);
		int inline setMousemotion_yrel(State & state, SDL_Event * event);

		int inline getMousebutton_windowID(State & state, SDL_Event * event);
		int inline setMousebutton_windowID(State & state, SDL_Event * event);

		int inline getMousebutton_which(State & state, SDL_Event * event);
		int inline setMousebutton_which(State & state, SDL_Event * event);

		int inline getMousebutton_button(State & state, SDL_Event * event);
		int inline setMousebutton_button(State & state, SDL_Event * event);

		int inline getMousebutton_state(State & state, SDL_Event * event);
		int inline setMousebutton_state(State & state, SDL_Event * event);

		int inline getMousebutton_x(State & state, SDL_Event * event);
		int inline setMousebutton_x(State & state, SDL_Event * event);

		int inline getMousebutton_y(State & state, SDL_Event * event);
		int inline setMousebutton_y(State & state, SDL_Event * event);

		int inline getMousewheel_windowID(State & state, SDL_Event * event);
		int inline setMousewheel_windowID(State & state, SDL_Event * event);

		int inline getMousewheel_which(State & state, SDL_Event * event);
		int inline setMousewheel_which(State & state, SDL_Event * event);

		int inline getMousewheel_x(State & state, SDL_Event * event);
		int inline setMousewheel_x(State & state, SDL_Event * event);

		int inline getMousewheel_y(State & state, SDL_Event * event);
		int inline setMousewheel_y(State & state, SDL_Event * event);

		int inline getJoyaxis_which(State & state, SDL_Event * event);
		int inline setJoyaxis_which(State & state, SDL_Event * event);

		int inline getJoyaxis_axis(State & state, SDL_Event * event);
		int inline setJoyaxis_axis(State & state, SDL_Event * event);

		int inline getJoyaxis_value(State & state, SDL_Event * event);
		int inline setJoyaxis_value(State & state, SDL_Event * event);

		int inline getJoyball_which(State & state, SDL_Event * event);
		int inline setJoyball_which(State & state, SDL_Event * event);

		int inline getJoyball_ball(State & state, SDL_Event * event);
		int inline setJoyball_ball(State & state, SDL_Event * event);

		int inline getJoyball_xrel(State & state, SDL_Event * event);
		int inline setJoyball_xrel(State & state, SDL_Event * event);

		int inline getJoyball_yrel(State & state, SDL_Event * event);
		int inline setJoyball_yrel(State & state, SDL_Event * event);

		int inline getJoyhat_which(State & state, SDL_Event * event);
		int inline setJoyhat_which(State & state, SDL_Event * event);

		int inline getJoyhat_hat(State & state, SDL_Event * event);
		int inline setJoyhat_hat(State & state, SDL_Event * event);

		int inline getJoyhat_value(State & state, SDL_Event * event);
		int inline setJoyhat_value(State & state, SDL_Event * event);

		int inline getJoybutton_which(State & state, SDL_Event * event);
		int inline setJoybutton_which(State & state, SDL_Event * event);

		int inline getJoybutton_button(State & state, SDL_Event * event);
		int inline setJoybutton_button(State & state, SDL_Event * event);

		int inline getJoybutton_state(State & state, SDL_Event * event);
		int inline setJoybutton_state(State & state, SDL_Event * event);

		int inline getJoydevice_which(State & state, SDL_Event * event);
		int inline setJoydevice_which(State & state, SDL_Event * event);

		int inline getControlleraxis_which(State & state, SDL_Event * event);
		int inline setControlleraxis_which(State & state, SDL_Event * event);

		int inline getControlleraxis_axis(State & state, SDL_Event * event);
		int inline setControlleraxis_axis(State & state, SDL_Event * event);

		int inline getControlleraxis_value(State & state, SDL_Event * event);
		int inline setControlleraxis_value(State & state, SDL_Event * event);

		int inline getControllerbutton_which(State & state, SDL_Event * event);
		int inline setControllerbutton_which(State & state, SDL_Event * event);

		int inline getControllerbutton_button(State & state, SDL_Event * event);
		int inline setControllerbutton_button(State & state, SDL_Event * event);

		int inline getControllerbutton_state(State & state, SDL_Event * event);
		int inline setControllerbutton_state(State & state, SDL_Event * event);

		int inline getControllerdevice_which(State & state, SDL_Event * event);
		int inline setControllerdevice_which(State & state, SDL_Event * event);

		int inline getTouchfinger_touchId(State & state, SDL_Event * event);
		int inline setTouchfinger_touchId(State & state, SDL_Event * event);

		int inline getTouchfinger_fingerId(State & state, SDL_Event * event);
		int inline setTouchfinger_fingerId(State & state, SDL_Event * event);

		int inline getTouchfinger_x(State & state, SDL_Event * event);
		int inline setTouchfinger_x(State & state, SDL_Event * event);

		int inline getTouchfinger_y(State & state, SDL_Event * event);
		int inline setTouchfinger_y(State & state, SDL_Event * event);

		int inline getTouchfinger_dx(State & state, SDL_Event * event);
		int inline setTouchfinger_dx(State & state, SDL_Event * event);

		int inline getTouchfinger_dy(State & state, SDL_Event * event);
		int inline setTouchfinger_dy(State & state, SDL_Event * event);

		int inline getMultigesture_touchId(State & state, SDL_Event * event);
		int inline setMultigesture_touchId(State & state, SDL_Event * event);

		int inline getMultigesture_dTheta(State & state, SDL_Event * event);
		int inline setMultigesture_dTheta(State & state, SDL_Event * event);

		int inline getMultigesture_dDist(State & state, SDL_Event * event);
		int inline setMultigesture_dDist(State & state, SDL_Event * event);

		int inline getMultigesture_x(State & state, SDL_Event * event);
		int inline setMultigesture_x(State & state, SDL_Event * event);

		int inline getMultigesture_y(State & state, SDL_Event * event);
		int inline setMultigesture_y(State & state, SDL_Event * event);

		int inline getMultigesture_numFingers(State & state, SDL_Event * event);
		int inline setMultigesture_numFingers(State & state, SDL_Event * event);

		int inline getDollargesture_touchId(State & state, SDL_Event * event);
		int inline setDollargesture_touchId(State & state, SDL_Event * event);

		int inline getDollargesture_gestureId(State & state, SDL_Event * event);
		int inline setDollargesture_gestureId(State & state, SDL_Event * event);

		int inline getDollargesture_numFingers(State & state, SDL_Event * event);
		int inline setDollargesture_numFingers(State & state, SDL_Event * event);

		int inline getDollargesture_error(State & state, SDL_Event * event);
		int inline setDollargesture_error(State & state, SDL_Event * event);

		int inline getDollargesture_x(State & state, SDL_Event * event);
		int inline setDollargesture_x(State & state, SDL_Event * event);

		int inline getDollargesture_y(State & state, SDL_Event * event);
		int inline setDollargesture_y(State & state, SDL_Event * event);

		int inline getDrop_file(State & state, SDL_Event * event);
		int setDrop_file(State & state, SDL_Event * event);

		int inline getUser_windowID(State & state, SDL_Event * event);
		int inline setUser_windowID(State & state, SDL_Event * event);

		int inline getUser_code(State & state, SDL_Event * event);
		int inline setUser_code(State & state, SDL_Event * event);

		int inline getUser_data1(State & state, SDL_Event * event);
		int inline setUser_data1(State & state, SDL_Event * event);

		int inline getUser_data2(State & state, SDL_Event * event);
		int inline setUser_data2(State & state, SDL_Event * event);

		int getSyswm_msg(State & state, SDL_Event * event);
		int setSyswm_msg(State & state, SDL_Event * event);
	};
}

#endif
