#ifndef LUA_SDL_OBJECTS_EVENT_H
#define LUA_SDL_OBJECTS_EVENT_H

#include "common.hpp"
#define LUA_SDL_TIMER_CODE	1000

namespace LuaSDL {

	class Lua_SDL_Event : public LObject<Lua_SDL_Event, SDL_Event *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_Event, SDL_Event *, "Event") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Event, "push", pushEvent);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Event, "", null_method);

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "type", getEventType, setEventType);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "timestamp", getTimestamp, getTimestamp);	

			//SDL_WindowEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "window_windowID", getWindow_windowID, setWindow_windowID);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "window_event", getWindow_event, setWindow_event);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "window_data1", getWindow_data1, setWindow_data1);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "window_data2", getWindow_data2, setWindow_data2);

			//SDL_KeyboardEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "keyboard_windowID", getKeyboard_windowID, setKeyboard_windowID);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "keyboard_state", getKeyboard_state, setKeyboard_state);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "keyboard_repeat", getKeyboard_repeat, setKeyboard_repeat);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "keyboard_keysym_scancode", getKeyboard_keysym_scancode, setKeyboard_keysym_scancode);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "keyboard_keysym_keycode", getKeyboard_keysym_keycode, setKeyboard_keysym_keycode);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "keyboard_keysym_sym", getKeyboard_keysym_sym, setKeyboard_keysym_sym);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "keyboard_keysym_mod", getKeyboard_keysym_mod, setKeyboard_keysym_mod);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "keyboard_keysym_unicode", getKeyboard_keysym_unicode, setKeyboard_keysym_unicode);

			//SDL_TextEditingEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "textediting_windowID", getTextediting_windowID, setTextediting_windowID);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "textediting_text", getTextediting_text, setTextediting_text);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "textediting_start", getTextediting_start, setTextediting_start);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "textediting_length", getTextediting_length, setTextediting_length);

			//SDL_TextInputEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "textinput_windowID", getTextinput_windowID, setTextinput_windowID);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "textinput_text", getTextinput_text, setTextinput_text);

			//SDL_MouseMotionEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousemotion_windowID", getMousemotion_windowID, setMousemotion_windowID);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousemotion_which", getMousemotion_which, setMousemotion_which);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousemotion_state", getMousemotion_state, setMousemotion_state);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousemotion_x", getMousemotion_x, setMousemotion_x);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousemotion_y", getMousemotion_y, setMousemotion_y);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousemotion_xrel", getMousemotion_xrel, setMousemotion_xrel);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousemotion_yrel", getMousemotion_yrel, setMousemotion_yrel);

			//SDL_MouseButtonEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousebutton_windowID", getMousebutton_windowID, setMousebutton_windowID);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousebutton_which", getMousebutton_which, setMousebutton_which);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousebutton_button", getMousebutton_button, setMousebutton_button);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousebutton_state", getMousebutton_state, setMousebutton_state);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousebutton_x", getMousebutton_x, setMousebutton_x);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousebutton_y", getMousebutton_y, setMousebutton_y);

			//SDL_MouseWheelEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousewheel_windowID", getMousewheel_windowID, setMousewheel_windowID);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousewheel_which", getMousewheel_which, setMousewheel_which);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousewheel_x", getMousewheel_x, setMousewheel_x);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "mousewheel_y", getMousewheel_y, setMousewheel_y);

			//SDL_JoyAxisEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joyaxis_which", getJoyaxis_which, setJoyaxis_which);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joyaxis_axis", getJoyaxis_axis, setJoyaxis_axis);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joyaxis_value", getJoyaxis_value, setJoyaxis_value);

			//SDL_JoyBallEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joyball_which", getJoyball_which, setJoyball_which);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joyball_ball", getJoyball_ball, setJoyball_ball);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joyball_xrel", getJoyball_xrel, setJoyball_xrel);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joyball_yrel", getJoyball_yrel, setJoyball_yrel);

			//SDL_JoyHatEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joyhat_which", getJoyhat_which, setJoyhat_which);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joyhat_hat", getJoyhat_hat, setJoyhat_hat);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joyhat_value", getJoyhat_value, setJoyhat_value);

			//SDL_JoyButtonEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joybutton_which", getJoybutton_which, setJoybutton_which);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joybutton_button", getJoybutton_button, setJoybutton_button);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joybutton_state", getJoybutton_state, setJoybutton_state);

			//SDL_JoyDeviceEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "joydevice_which", getJoydevice_which, setJoydevice_which);

			//SDL_ControllerAxisEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "controlleraxis_which", getControlleraxis_which, setControlleraxis_which);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "controlleraxis_axis", getControlleraxis_axis, setControlleraxis_axis);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "controlleraxis_value", getControlleraxis_value, setControlleraxis_value);

			//SDL_ControllerButtonEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "controllerbutton_which", getControllerbutton_which, setControllerbutton_which);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "controllerbutton_button", getControllerbutton_button, setControllerbutton_button);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "controllerbutton_state", getControllerbutton_state, setControllerbutton_state);

			//SDL_ControllerDeviceEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "controllerdevice_which", getControllerdevice_which, setControllerdevice_which);

			//SDL_TouchFingerEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "touchfinger_touchId", getTouchfinger_touchId, setTouchfinger_touchId);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "touchfinger_fingerId", getTouchfinger_fingerId, setTouchfinger_fingerId);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "touchfinger_x", getTouchfinger_x, setTouchfinger_x);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "touchfinger_y", getTouchfinger_y, setTouchfinger_y);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "touchfinger_dx", getTouchfinger_dx, setTouchfinger_dx);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "touchfinger_dy", getTouchfinger_dy, setTouchfinger_dy);

			//SDL_MultiGestureEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "multigesture_touchId", getMultigesture_touchId, setMultigesture_touchId);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "multigesture_dTheta", getMultigesture_dTheta, setMultigesture_dTheta);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "multigesture_dDist", getMultigesture_dDist, setMultigesture_dDist);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "multigesture_x", getMultigesture_x, setMultigesture_x);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "multigesture_y", getMultigesture_y, setMultigesture_y);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "multigesture_numFingers", getMultigesture_numFingers, setMultigesture_numFingers);

			//SDL_DollarGestureEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "dollargesture_touchId", getDollargesture_touchId, setDollargesture_touchId);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "dollargesture_gestureId", getDollargesture_gestureId, setDollargesture_gestureId);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "dollargesture_numFingers", getDollargesture_numFingers, setDollargesture_numFingers);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "dollargesture_error", getDollargesture_error, setDollargesture_error);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "dollargesture_x", getDollargesture_x, setDollargesture_x);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "dollargesture_y", getDollargesture_y, setDollargesture_y);

			//SDL_DropEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "dropevent_file", getDrop_file, setDrop_file);

			//SDL_QuitEvent

			//SDL_UserEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "userevent_windowID", getUser_windowID, setUser_windowID);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "userevent_code", getUser_code, setUser_code);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "userevent_data1", getUser_data1, setUser_data1);
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "userevent_data2", getUser_data2, setUser_data2);

			//SDL_SysWMEvent
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_Event, SDL_Event *, "syswm_msg", getSyswm_msg, setSyswm_msg);

		}

		void destructor(lutok::state & s, SDL_Event * event){
			if (event->type == SDL_DROPFILE){
				if (event->drop.file){
					SDL_free(event->drop.file);
				}
			}
			delete event;
		}

		int inline LOBJECT_METHOD(pushEvent, SDL_Event * event){
			state.push_integer(SDL_PushEvent(event));
			return 1;
		}

		//common getters/setters

		int inline LOBJECT_METHOD(getEventType, SDL_Event * event){
			state.push_integer(event->type);
			return 1;
		}
		int inline LOBJECT_METHOD(setEventType, SDL_Event * event){
			event->type = state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getTimestamp, SDL_Event * event){
			state.push_integer(((SDL_CommonEvent*)event)->timestamp);
			return 1;
		}
		int inline LOBJECT_METHOD(setTimestamp, SDL_Event * event){
			((SDL_CommonEvent*)event)->timestamp = state.to_integer(1);
			return 0;
		}

		//event specific getters/setters

		int inline LOBJECT_METHOD(getWindow_windowID, SDL_Event * event){
			state.push_integer(event->window.windowID);
			return 1;
		}
		int inline LOBJECT_METHOD(setWindow_windowID, SDL_Event * event){
			event->window.windowID = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getWindow_event, SDL_Event * event){
			state.push_integer(event->window.event);
			return 1;
		}
		int inline LOBJECT_METHOD(setWindow_event, SDL_Event * event){
			event->window.event = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getWindow_data1, SDL_Event * event){
			state.push_integer(event->window.data1);
			return 1;
		}
		int inline LOBJECT_METHOD(setWindow_data1, SDL_Event * event){
			event->window.data1 = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getWindow_data2, SDL_Event * event){
			state.push_integer(event->window.data2);
			return 1;
		}
		int inline LOBJECT_METHOD(setWindow_data2, SDL_Event * event){
			event->window.data2 = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getKeyboard_windowID, SDL_Event * event){
			state.push_integer(event->key.windowID);
			return 1;
		}
		int inline LOBJECT_METHOD(setKeyboard_windowID, SDL_Event * event){
			event->key.windowID = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getKeyboard_state, SDL_Event * event){
			state.push_integer(event->key.state);
			return 1;
		}
		int inline LOBJECT_METHOD(setKeyboard_state, SDL_Event * event){
			event->key.state = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getKeyboard_repeat, SDL_Event * event){
			state.push_integer(event->key.repeat);
			return 1;
		}
		int inline LOBJECT_METHOD(setKeyboard_repeat, SDL_Event * event){
			event->key.repeat = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getKeyboard_keysym_scancode, SDL_Event * event){
			state.push_integer(event->key.keysym.scancode);
			return 1;
		}
		int inline LOBJECT_METHOD(setKeyboard_keysym_scancode, SDL_Event * event){
			event->key.keysym.scancode = (SDL_Scancode)state.to_integer(1);
			return 0;
		}
		int inline LOBJECT_METHOD(getKeyboard_keysym_keycode, SDL_Event * event){
			state.push_integer(SDL_SCANCODE_TO_KEYCODE(event->key.keysym.scancode));
			return 1;
		}
		int inline LOBJECT_METHOD(setKeyboard_keysym_keycode, SDL_Event * event){
			event->key.keysym.scancode = (SDL_Scancode)(state.to_integer(1) & ~SDLK_SCANCODE_MASK);
			return 0;
		}

		int inline LOBJECT_METHOD(getKeyboard_keysym_sym, SDL_Event * event){
			state.push_integer(event->key.keysym.sym);
			return 1;
		}
		int inline LOBJECT_METHOD(setKeyboard_keysym_sym, SDL_Event * event){
			event->key.keysym.sym = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getKeyboard_keysym_mod, SDL_Event * event){
			state.push_integer(event->key.keysym.mod);
			return 1;
		}
		int inline LOBJECT_METHOD(setKeyboard_keysym_mod, SDL_Event * event){
			event->key.keysym.mod = (Uint16)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getKeyboard_keysym_unicode, SDL_Event * event){
			state.push_integer(event->key.keysym.unused);
			return 1;
		}
		int inline LOBJECT_METHOD(setKeyboard_keysym_unicode, SDL_Event * event){
			event->key.keysym.unused = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getTextediting_windowID, SDL_Event * event){
			state.push_integer(event->edit.windowID);
			return 1;
		}
		int inline LOBJECT_METHOD(setTextediting_windowID, SDL_Event * event){
			event->edit.windowID = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getTextediting_text, SDL_Event * event){
			state.push_string(event->edit.text);
			return 1;
		}
		int inline LOBJECT_METHOD(setTextediting_text, SDL_Event * event){
			std::string & text = state.to_string(1);
			size_t text_len = text.length();
			size_t len = (text_len < SDL_TEXTEDITINGEVENT_TEXT_SIZE-1) ? text_len : SDL_TEXTEDITINGEVENT_TEXT_SIZE-1;
			strncpy(event->edit.text, text.c_str(),len);
			return 0;
		}

		int inline LOBJECT_METHOD(getTextediting_start, SDL_Event * event){
			state.push_integer(event->edit.start);
			return 1;
		}
		int inline LOBJECT_METHOD(setTextediting_start, SDL_Event * event){
			event->edit.start = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getTextediting_length, SDL_Event * event){
			state.push_integer(event->edit.length);
			return 1;
		}
		int inline LOBJECT_METHOD(setTextediting_length, SDL_Event * event){
			event->edit.length = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getTextinput_windowID, SDL_Event * event){
			state.push_integer(event->text.windowID);
			return 1;
		}
		int inline LOBJECT_METHOD(setTextinput_windowID, SDL_Event * event){
			event->text.windowID = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getTextinput_text, SDL_Event * event){
			state.push_string(event->text.text);
			return 1;
		}
		int inline LOBJECT_METHOD(setTextinput_text, SDL_Event * event){
			std::string & text = state.to_string(1) ;
			size_t text_len = text.length();
			size_t len = (text_len < SDL_TEXTINPUTEVENT_TEXT_SIZE-1) ? text_len : SDL_TEXTINPUTEVENT_TEXT_SIZE-1;
			strncpy(event->text.text, text.c_str(),len);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousemotion_windowID, SDL_Event * event){
			state.push_integer(event->motion.windowID);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousemotion_windowID, SDL_Event * event){
			event->motion.windowID = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousemotion_which, SDL_Event * event){
			state.push_integer(event->motion.which);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousemotion_which, SDL_Event * event){
			event->motion.which = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousemotion_state, SDL_Event * event){
			state.push_integer(event->motion.state);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousemotion_state, SDL_Event * event){
			event->motion.state = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousemotion_x, SDL_Event * event){
			state.push_integer(event->motion.x);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousemotion_x, SDL_Event * event){
			event->motion.x = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousemotion_y, SDL_Event * event){
			state.push_integer(event->motion.y);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousemotion_y, SDL_Event * event){
			event->motion.y = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousemotion_xrel, SDL_Event * event){
			state.push_integer(event->motion.xrel);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousemotion_xrel, SDL_Event * event){
			event->motion.xrel = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousemotion_yrel, SDL_Event * event){
			state.push_integer(event->motion.yrel);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousemotion_yrel, SDL_Event * event){
			event->motion.yrel = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousebutton_windowID, SDL_Event * event){
			state.push_integer(event->button.windowID);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousebutton_windowID, SDL_Event * event){
			event->button.windowID = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousebutton_which, SDL_Event * event){
			state.push_integer(event->button.which);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousebutton_which, SDL_Event * event){
			event->button.which = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousebutton_button, SDL_Event * event){
			state.push_integer(event->button.button);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousebutton_button, SDL_Event * event){
			event->button.button = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousebutton_state, SDL_Event * event){
			state.push_integer(event->button.state);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousebutton_state, SDL_Event * event){
			event->button.state = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousebutton_x, SDL_Event * event){
			state.push_integer(event->button.x);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousebutton_x, SDL_Event * event){
			event->button.x = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousebutton_y, SDL_Event * event){
			state.push_integer(event->button.y);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousebutton_y, SDL_Event * event){
			event->button.y = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousewheel_windowID, SDL_Event * event){
			state.push_integer(event->wheel.windowID);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousewheel_windowID, SDL_Event * event){
			event->wheel.windowID = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousewheel_which, SDL_Event * event){
			state.push_integer(event->wheel.which);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousewheel_which, SDL_Event * event){
			event->wheel.which = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousewheel_x, SDL_Event * event){
			state.push_integer(event->wheel.x);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousewheel_x, SDL_Event * event){
			event->wheel.x = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMousewheel_y, SDL_Event * event){
			state.push_integer(event->wheel.y);
			return 1;
		}
		int inline LOBJECT_METHOD(setMousewheel_y, SDL_Event * event){
			event->wheel.y = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoyaxis_which, SDL_Event * event){
			state.push_integer(event->jaxis.which);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoyaxis_which, SDL_Event * event){
			event->jaxis.which = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoyaxis_axis, SDL_Event * event){
			state.push_integer(event->jaxis.axis);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoyaxis_axis, SDL_Event * event){
			event->jaxis.axis = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoyaxis_value, SDL_Event * event){
			state.push_integer(event->jaxis.value);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoyaxis_value, SDL_Event * event){
			event->jaxis.value = (Sint16)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoyball_which, SDL_Event * event){
			state.push_integer(event->jball.which);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoyball_which, SDL_Event * event){
			event->jball.which = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoyball_ball, SDL_Event * event){
			state.push_integer(event->jball.ball);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoyball_ball, SDL_Event * event){
			event->jball.ball = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoyball_xrel, SDL_Event * event){
			state.push_integer(event->jball.xrel);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoyball_xrel, SDL_Event * event){
			event->jball.xrel = (Sint16)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoyball_yrel, SDL_Event * event){
			state.push_integer(event->jball.yrel);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoyball_yrel, SDL_Event * event){
			event->jball.yrel = (Sint16)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoyhat_which, SDL_Event * event){
			state.push_integer(event->jhat.which);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoyhat_which, SDL_Event * event){
			event->jhat.which = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoyhat_hat, SDL_Event * event){
			state.push_integer(event->jhat.hat);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoyhat_hat, SDL_Event * event){
			event->jhat.hat = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoyhat_value, SDL_Event * event){
			state.push_integer(event->jhat.value);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoyhat_value, SDL_Event * event){
			event->jhat.value = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoybutton_which, SDL_Event * event){
			state.push_integer(event->jbutton.which);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoybutton_which, SDL_Event * event){
			event->jbutton.which = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoybutton_button, SDL_Event * event){
			state.push_integer(event->jbutton.button);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoybutton_button, SDL_Event * event){
			event->jbutton.button = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoybutton_state, SDL_Event * event){
			state.push_integer(event->jbutton.state);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoybutton_state, SDL_Event * event){
			event->jbutton.state = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getJoydevice_which, SDL_Event * event){
			state.push_integer(event->jdevice.which);
			return 1;
		}
		int inline LOBJECT_METHOD(setJoydevice_which, SDL_Event * event){
			event->jdevice.which = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getControlleraxis_which, SDL_Event * event){
			state.push_integer(event->caxis.which);
			return 1;
		}
		int inline LOBJECT_METHOD(setControlleraxis_which, SDL_Event * event){
			event->caxis.which = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getControlleraxis_axis, SDL_Event * event){
			state.push_integer(event->caxis.axis);
			return 1;
		}
		int inline LOBJECT_METHOD(setControlleraxis_axis, SDL_Event * event){
			event->caxis.axis = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getControlleraxis_value, SDL_Event * event){
			state.push_integer(event->caxis.value);
			return 1;
		}
		int inline LOBJECT_METHOD(setControlleraxis_value, SDL_Event * event){
			event->caxis.value = (Sint16)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getControllerbutton_which, SDL_Event * event){
			state.push_integer(event->cbutton.which);
			return 1;
		}
		int inline LOBJECT_METHOD(setControllerbutton_which, SDL_Event * event){
			event->cbutton.which = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getControllerbutton_button, SDL_Event * event){
			state.push_integer(event->cbutton.button);
			return 1;
		}
		int inline LOBJECT_METHOD(setControllerbutton_button, SDL_Event * event){
			event->cbutton.button = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getControllerbutton_state, SDL_Event * event){
			state.push_integer(event->cbutton.state);
			return 1;
		}
		int inline LOBJECT_METHOD(setControllerbutton_state, SDL_Event * event){
			event->cbutton.state = (Uint8)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getControllerdevice_which, SDL_Event * event){
			state.push_integer(event->cdevice.which);
			return 1;
		}
		int inline LOBJECT_METHOD(setControllerdevice_which, SDL_Event * event){
			event->cdevice.which = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getTouchfinger_touchId, SDL_Event * event){
			state.push_integer((const int)event->tfinger.touchId);
			return 1;
		}
		int inline LOBJECT_METHOD(setTouchfinger_touchId, SDL_Event * event){
			event->tfinger.touchId = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getTouchfinger_fingerId, SDL_Event * event){
			state.push_integer((const int)event->tfinger.fingerId);
			return 1;
		}
		int inline LOBJECT_METHOD(setTouchfinger_fingerId, SDL_Event * event){
			event->tfinger.fingerId = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getTouchfinger_x, SDL_Event * event){
			state.push_number(event->tfinger.x);
			return 1;
		}
		int inline LOBJECT_METHOD(setTouchfinger_x, SDL_Event * event){
			event->tfinger.x = (float)state.to_number(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getTouchfinger_y, SDL_Event * event){
			state.push_number(event->tfinger.y);
			return 1;
		}
		int inline LOBJECT_METHOD(setTouchfinger_y, SDL_Event * event){
			event->tfinger.y = (float)state.to_number(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getTouchfinger_dx, SDL_Event * event){
			state.push_number(event->tfinger.dx);
			return 1;
		}
		int inline LOBJECT_METHOD(setTouchfinger_dx, SDL_Event * event){
			event->tfinger.dx = (float)state.to_number(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getTouchfinger_dy, SDL_Event * event){
			state.push_number(event->tfinger.dy);
			return 1;
		}
		int inline LOBJECT_METHOD(setTouchfinger_dy, SDL_Event * event){
			event->tfinger.dy = (float)state.to_number(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMultigesture_touchId, SDL_Event * event){
			state.push_integer((const int)event->mgesture.touchId);
			return 1;
		}
		int inline LOBJECT_METHOD(setMultigesture_touchId, SDL_Event * event){
			event->mgesture.touchId = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMultigesture_dTheta, SDL_Event * event){
			state.push_number(event->mgesture.dTheta);
			return 1;
		}
		int inline LOBJECT_METHOD(setMultigesture_dTheta, SDL_Event * event){
			event->mgesture.dTheta = (float)state.to_number(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMultigesture_dDist, SDL_Event * event){
			state.push_number(event->mgesture.dDist);
			return 1;
		}
		int inline LOBJECT_METHOD(setMultigesture_dDist, SDL_Event * event){
			event->mgesture.dDist = (float)state.to_number(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMultigesture_x, SDL_Event * event){
			state.push_number(event->mgesture.x);
			return 1;
		}
		int inline LOBJECT_METHOD(setMultigesture_x, SDL_Event * event){
			event->mgesture.x = (float)state.to_number(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMultigesture_y, SDL_Event * event){
			state.push_number(event->mgesture.y);
			return 1;
		}
		int inline LOBJECT_METHOD(setMultigesture_y, SDL_Event * event){
			event->mgesture.y = (float)state.to_number(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getMultigesture_numFingers, SDL_Event * event){
			state.push_integer(event->mgesture.numFingers);
			return 1;
		}
		int inline LOBJECT_METHOD(setMultigesture_numFingers, SDL_Event * event){
			event->mgesture.numFingers = (Uint16)state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getDollargesture_touchId, SDL_Event * event){
			state.push_integer((const int)event->dgesture.touchId);
			return 1;
		}
		int inline LOBJECT_METHOD(setDollargesture_touchId, SDL_Event * event){
			event->dgesture.touchId = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getDollargesture_gestureId, SDL_Event * event){
			state.push_integer((const int)event->dgesture.gestureId);
			return 1;
		}
		int inline LOBJECT_METHOD(setDollargesture_gestureId, SDL_Event * event){
			event->dgesture.gestureId = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getDollargesture_numFingers, SDL_Event * event){
			state.push_integer(event->dgesture.numFingers);
			return 1;
		}
		int inline LOBJECT_METHOD(setDollargesture_numFingers, SDL_Event * event){
			event->dgesture.numFingers = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getDollargesture_error, SDL_Event * event){
			state.push_number(event->dgesture.error);
			return 1;
		}
		int inline LOBJECT_METHOD(setDollargesture_error, SDL_Event * event){
			event->dgesture.error = (float)state.to_number(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getDollargesture_x, SDL_Event * event){
			state.push_number(event->dgesture.x);
			return 1;
		}
		int inline LOBJECT_METHOD(setDollargesture_x, SDL_Event * event){
			event->dgesture.x = (float)state.to_number(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getDollargesture_y, SDL_Event * event){
			state.push_number(event->dgesture.y);
			return 1;
		}
		int inline LOBJECT_METHOD(setDollargesture_y, SDL_Event * event){
			event->dgesture.y = (float)state.to_number(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getDrop_file, SDL_Event * event){
			state.push_string(event->drop.file);
			return 1;
		}
		int LOBJECT_METHOD(setDrop_file, SDL_Event * event){
			std::string & text = state.to_string(1) ;
			size_t text_len = text.length();
			size_t len = (text_len < FILENAME_MAX-1) ? text_len : FILENAME_MAX-1;
			
			if (event->drop.file)
				event->drop.file = (char*)SDL_realloc(event->drop.file, len+1);

			strncpy(event->drop.file, text.c_str(),len);
			return 0;
		}

		int inline LOBJECT_METHOD(getUser_windowID, SDL_Event * event){
			state.push_integer(event->user.windowID);
			return 1;
		}
		int inline LOBJECT_METHOD(setUser_windowID, SDL_Event * event){
			event->user.windowID = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getUser_code, SDL_Event * event){
			state.push_integer(event->user.code);
			return 1;
		}
		int inline LOBJECT_METHOD(setUser_code, SDL_Event * event){
			event->user.code = state.to_integer(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getUser_data1, SDL_Event * event){
			if (event->user.code == LUA_SDL_TIMER_CODE){
				int ref = reinterpret_cast<int>(event->user.data1);
				state.raw_geti(LUA_REGISTRYINDEX, ref);
			}else{
				state.push_lightuserdata(event->user.data1);
			}
			return 1;
		}
		int inline LOBJECT_METHOD(setUser_data1, SDL_Event * event){
			event->user.data1 = (void*)state.to_lightuserdata(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getUser_data2, SDL_Event * event){
			state.push_lightuserdata(event->user.data2);
			return 1;
		}
		int inline LOBJECT_METHOD(setUser_data2, SDL_Event * event){
			event->user.data2 = (void*)state.to_lightuserdata(1);
			return 0;
		}

		int inline LOBJECT_METHOD(getSyswm_msg, SDL_Event * event){
			//state.push_lightuserdata(event->syswm.msg);
			return 0;
		}
		int inline LOBJECT_METHOD(setSyswm_msg, SDL_Event * event){
			//event->syswm.msg = (void*)state.to_lightuserdata(1);
			return 0;
		}



	};
}

#endif
