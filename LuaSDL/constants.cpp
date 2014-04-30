#include "common.hpp"
namespace LuaSDL{
	void init_constants(lutok::state & state){
		//SDL_Init
		state.set_field("INIT_TIMER",					SDL_INIT_TIMER);
		state.set_field("INIT_AUDIO",					SDL_INIT_AUDIO);
		state.set_field("INIT_VIDEO",					SDL_INIT_VIDEO);
		state.set_field("INIT_JOYSTICK",				SDL_INIT_JOYSTICK);
		state.set_field("INIT_HAPTIC",					SDL_INIT_HAPTIC);
		state.set_field("INIT_EVENTS",					SDL_INIT_EVENTS);
		state.set_field("INIT_GAMECONTROLLER",			SDL_INIT_GAMECONTROLLER);
		state.set_field("INIT_NOPARACHUTE",				SDL_INIT_NOPARACHUTE);
		state.set_field("INIT_EVERYTHING",				SDL_INIT_EVERYTHING);

		//SDL_PowerState
		state.set_field("POWERSTATE_UNKNOWN",			SDL_POWERSTATE_UNKNOWN);
		state.set_field("POWERSTATE_ON_BATTERY",		SDL_POWERSTATE_ON_BATTERY);
		state.set_field("POWERSTATE_NO_BATTERY",		SDL_POWERSTATE_NO_BATTERY);
		state.set_field("POWERSTATE_CHARGING",			SDL_POWERSTATE_CHARGING);
		state.set_field("POWERSTATE_CHARGED",			SDL_POWERSTATE_CHARGED);

		//SDL_MessageBox
		state.set_field("MESSAGEBOX_ERROR",				SDL_MESSAGEBOX_ERROR);
		state.set_field("MESSAGEBOX_WARNING",			SDL_MESSAGEBOX_WARNING);
		state.set_field("MESSAGEBOX_INFORMATION",		SDL_MESSAGEBOX_INFORMATION);

		//SDL_MessageBox_Color
		state.set_field("MESSAGEBOX_COLOR_BACKGROUND",	SDL_MESSAGEBOX_COLOR_BACKGROUND);
		state.set_field("MESSAGEBOX_COLOR_TEXT",		SDL_MESSAGEBOX_COLOR_TEXT);
		state.set_field("MESSAGEBOX_COLOR_BUTTON_BORDER",		SDL_MESSAGEBOX_COLOR_BUTTON_BORDER);
		state.set_field("MESSAGEBOX_COLOR_BUTTON_BACKGROUND",	SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
		state.set_field("MESSAGEBOX_COLOR_BUTTON_SELECTED",		SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED);
		state.set_field("MESSAGEBOX_COLOR_MAX",			SDL_MESSAGEBOX_COLOR_MAX);

		//SDL_WindowFlags
		state.set_field("WINDOW_FULLSCREEN",			SDL_WINDOW_FULLSCREEN);
		state.set_field("WINDOW_OPENGL",				SDL_WINDOW_OPENGL);
		state.set_field("WINDOW_SHOWN",					SDL_WINDOW_SHOWN);
		state.set_field("WINDOW_HIDDEN",				SDL_WINDOW_HIDDEN);
		state.set_field("WINDOW_BORDERLESS",			SDL_WINDOW_BORDERLESS);
		state.set_field("WINDOW_RESIZABLE",				SDL_WINDOW_RESIZABLE);
		state.set_field("WINDOW_MINIMIZED",				SDL_WINDOW_MINIMIZED);
		state.set_field("WINDOW_MAXIMIZED",				SDL_WINDOW_MAXIMIZED);
		state.set_field("WINDOW_INPUT_GRABBED",			SDL_WINDOW_INPUT_GRABBED);
		state.set_field("WINDOW_INPUT_FOCUS",			SDL_WINDOW_INPUT_FOCUS);
		state.set_field("WINDOW_MOUSE_FOCUS",			SDL_WINDOW_MOUSE_FOCUS);
		state.set_field("WINDOW_FULLSCREEN_DESKTOP",	SDL_WINDOW_FULLSCREEN_DESKTOP);
		state.set_field("WINDOW_FOREIGN",				SDL_WINDOW_FOREIGN);

		state.set_field("WINDOWPOS_UNDEFINED_MASK",		SDL_WINDOWPOS_UNDEFINED_MASK);
		state.set_field("WINDOWPOS_CENTERED_MASK",		SDL_WINDOWPOS_CENTERED_MASK);

		//SDL_WindowEventID
		state.set_field("WINDOWEVENT_NONE",				SDL_WINDOWEVENT_NONE);
		state.set_field("WINDOWEVENT_SHOWN",			SDL_WINDOWEVENT_SHOWN);
		state.set_field("WINDOWEVENT_HIDDEN",			SDL_WINDOWEVENT_HIDDEN);
		state.set_field("WINDOWEVENT_EXPOSED",			SDL_WINDOWEVENT_EXPOSED);
		state.set_field("WINDOWEVENT_MOVED",			SDL_WINDOWEVENT_MOVED);
		state.set_field("WINDOWEVENT_RESIZED",			SDL_WINDOWEVENT_RESIZED);
		state.set_field("WINDOWEVENT_SIZE_CHANGED",		SDL_WINDOWEVENT_SIZE_CHANGED);
		state.set_field("WINDOWEVENT_MINIMIZED",		SDL_WINDOWEVENT_MINIMIZED);
		state.set_field("WINDOWEVENT_MAXIMIZED",		SDL_WINDOWEVENT_MAXIMIZED);
		state.set_field("WINDOWEVENT_RESTORED",			SDL_WINDOWEVENT_RESTORED);
		state.set_field("WINDOWEVENT_ENTER",			SDL_WINDOWEVENT_ENTER);
		state.set_field("WINDOWEVENT_LEAVE",			SDL_WINDOWEVENT_LEAVE);
		state.set_field("WINDOWEVENT_FOCUS_GAINED",		SDL_WINDOWEVENT_FOCUS_GAINED);
		state.set_field("WINDOWEVENT_FOCUS_LOST",		SDL_WINDOWEVENT_FOCUS_LOST);
		state.set_field("WINDOWEVENT_CLOSE",			SDL_WINDOWEVENT_CLOSE);

		//Pixel formats
		state.set_field("PIXELFORMAT_UNKNOWN",			SDL_PIXELFORMAT_UNKNOWN);
		state.set_field("PIXELFORMAT_INDEX1LSB",		SDL_PIXELFORMAT_INDEX1LSB);
		state.set_field("PIXELFORMAT_INDEX1MSB",		SDL_PIXELFORMAT_INDEX1MSB);
		state.set_field("PIXELFORMAT_INDEX4LSB",		SDL_PIXELFORMAT_INDEX4LSB);
		state.set_field("PIXELFORMAT_INDEX4MSB",		SDL_PIXELFORMAT_INDEX4MSB);
		state.set_field("PIXELFORMAT_INDEX8",			SDL_PIXELFORMAT_INDEX8);
		state.set_field("PIXELFORMAT_RGB332",			SDL_PIXELFORMAT_RGB332);
		state.set_field("PIXELFORMAT_RGB444",			SDL_PIXELFORMAT_RGB444);
		state.set_field("PIXELFORMAT_RGB555",			SDL_PIXELFORMAT_RGB555);
		state.set_field("PIXELFORMAT_BGR555",			SDL_PIXELFORMAT_BGR555);
		state.set_field("PIXELFORMAT_ARGB4444",			SDL_PIXELFORMAT_ARGB4444);
		state.set_field("PIXELFORMAT_RGBA4444",			SDL_PIXELFORMAT_RGBA4444);
		state.set_field("PIXELFORMAT_ABGR4444",			SDL_PIXELFORMAT_ABGR4444);
		state.set_field("PIXELFORMAT_BGRA4444",			SDL_PIXELFORMAT_BGRA4444);
		state.set_field("PIXELFORMAT_ARGB1555",			SDL_PIXELFORMAT_ARGB1555);
		state.set_field("PIXELFORMAT_RGBA5551",			SDL_PIXELFORMAT_RGBA5551);
		state.set_field("PIXELFORMAT_ABGR1555",			SDL_PIXELFORMAT_ABGR1555);
		state.set_field("PIXELFORMAT_BGRA5551",			SDL_PIXELFORMAT_BGRA5551);
		state.set_field("PIXELFORMAT_RGB565",			SDL_PIXELFORMAT_RGB565);
		state.set_field("PIXELFORMAT_BGR565",			SDL_PIXELFORMAT_BGR565);
		state.set_field("PIXELFORMAT_RGB24",			SDL_PIXELFORMAT_RGB24);
		state.set_field("PIXELFORMAT_BGR24",			SDL_PIXELFORMAT_BGR24);
		state.set_field("PIXELFORMAT_RGB888",			SDL_PIXELFORMAT_RGB888);
		state.set_field("PIXELFORMAT_RGBX8888",			SDL_PIXELFORMAT_RGBX8888);
		state.set_field("PIXELFORMAT_BGR888",			SDL_PIXELFORMAT_BGR888);
		state.set_field("PIXELFORMAT_BGRX8888",			SDL_PIXELFORMAT_BGRX8888);
		state.set_field("PIXELFORMAT_ARGB8888",			SDL_PIXELFORMAT_ARGB8888);
		state.set_field("PIXELFORMAT_RGBA8888",			SDL_PIXELFORMAT_RGBA8888);
		state.set_field("PIXELFORMAT_ABGR8888",			SDL_PIXELFORMAT_ABGR8888);
		state.set_field("PIXELFORMAT_BGRA8888",			SDL_PIXELFORMAT_BGRA8888);
		state.set_field("PIXELFORMAT_ARGB2101010",		SDL_PIXELFORMAT_ARGB2101010);
		state.set_field("PIXELFORMAT_YV12",				SDL_PIXELFORMAT_YV12);
		state.set_field("PIXELFORMAT_IYUV",				SDL_PIXELFORMAT_IYUV);
		state.set_field("PIXELFORMAT_YUY2",				SDL_PIXELFORMAT_YUY2);
		state.set_field("PIXELFORMAT_UYVY",				SDL_PIXELFORMAT_UYVY);
		state.set_field("PIXELFORMAT_YVYU",				SDL_PIXELFORMAT_YVYU);

		//SDL_RendererFlags
		state.set_field("RENDERER_SOFTWARE",			SDL_RENDERER_SOFTWARE);
		state.set_field("RENDERER_ACCELERATED",			SDL_RENDERER_ACCELERATED);
		state.set_field("RENDERER_PRESENTVSYNC",		SDL_RENDERER_PRESENTVSYNC);
		state.set_field("RENDERER_TARGETTEXTURE",		SDL_RENDERER_TARGETTEXTURE);

		//SDL_TextureAccess
		state.set_field("TEXTUREACCESS_STATIC",			SDL_TEXTUREACCESS_STATIC);
		state.set_field("TEXTUREACCESS_STREAMING",		SDL_TEXTUREACCESS_STREAMING);

		//SDL_TextureModulate
		state.set_field("TEXTUREMODULATE_NONE",			SDL_TEXTUREMODULATE_NONE);
		state.set_field("TEXTUREMODULATE_COLOR",		SDL_TEXTUREMODULATE_COLOR);
		state.set_field("TEXTUREMODULATE_ALPHA",		SDL_TEXTUREMODULATE_ALPHA);

		//SDL_BlendMode
		state.set_field("BLENDMODE_NONE",				SDL_BLENDMODE_NONE);
		state.set_field("BLENDMODE_BLEND",				SDL_BLENDMODE_BLEND);
		state.set_field("BLENDMODE_ADD",				SDL_BLENDMODE_ADD);
		state.set_field("BLENDMODE_MOD",				SDL_BLENDMODE_MOD);

		//SDL_RendererFlip
		state.set_field("FLIP_NONE",					SDL_FLIP_NONE);
		state.set_field("FLIP_HORIZONTAL",				SDL_FLIP_HORIZONTAL);
		state.set_field("FLIP_VERTICAL",				SDL_FLIP_VERTICAL);

		//SDL_GLattr
		state.set_field("GL_RED_SIZE",					SDL_GL_RED_SIZE);
		state.set_field("GL_GREEN_SIZE",				SDL_GL_GREEN_SIZE);
		state.set_field("GL_BLUE_SIZE",					SDL_GL_BLUE_SIZE);
		state.set_field("GL_ALPHA_SIZE",				SDL_GL_ALPHA_SIZE);
		state.set_field("GL_BUFFER_SIZE",				SDL_GL_BUFFER_SIZE);
		state.set_field("GL_DOUBLEBUFFER",				SDL_GL_DOUBLEBUFFER);
		state.set_field("GL_DEPTH_SIZE",				SDL_GL_DEPTH_SIZE);
		state.set_field("GL_STENCIL_SIZE",				SDL_GL_STENCIL_SIZE);
		state.set_field("GL_ACCUM_RED_SIZE",			SDL_GL_ACCUM_RED_SIZE);
		state.set_field("GL_ACCUM_GREEN_SIZE",			SDL_GL_ACCUM_GREEN_SIZE);
		state.set_field("GL_ACCUM_BLUE_SIZE",			SDL_GL_ACCUM_BLUE_SIZE);
		state.set_field("GL_ACCUM_ALPHA_SIZE",			SDL_GL_ACCUM_ALPHA_SIZE);
		state.set_field("GL_STEREO",					SDL_GL_STEREO);
		state.set_field("GL_MULTISAMPLEBUFFERS",		SDL_GL_MULTISAMPLEBUFFERS);
		state.set_field("GL_MULTISAMPLESAMPLES",		SDL_GL_MULTISAMPLESAMPLES);
		state.set_field("GL_ACCELERATED_VISUAL",		SDL_GL_ACCELERATED_VISUAL);
		state.set_field("GL_RETAINED_BACKING",			SDL_GL_RETAINED_BACKING);
		state.set_field("GL_CONTEXT_MAJOR_VERSION",		SDL_GL_CONTEXT_MAJOR_VERSION);
		state.set_field("GL_CONTEXT_MINOR_VERSION",		SDL_GL_CONTEXT_MINOR_VERSION);
		state.set_field("GL_CONTEXT_EGL",				SDL_GL_CONTEXT_EGL);
		state.set_field("GL_CONTEXT_FLAGS",				SDL_GL_CONTEXT_FLAGS);
		state.set_field("GL_CONTEXT_PROFILE_MASK",		SDL_GL_CONTEXT_PROFILE_MASK);
		state.set_field("GL_SHARE_WITH_CURRENT_CONTEXT", SDL_GL_SHARE_WITH_CURRENT_CONTEXT);

		//SDL_GLprofile
		state.set_field("GL_CONTEXT_PROFILE_CORE",		SDL_GL_CONTEXT_PROFILE_CORE);
		state.set_field("GL_CONTEXT_PROFILE_COMPATIBILITY", SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		state.set_field("GL_CONTEXT_PROFILE_ES",		SDL_GL_CONTEXT_PROFILE_ES);

		//SDL_GLcontextFlag
		state.set_field("GL_CONTEXT_DEBUG_FLAG",		SDL_GL_CONTEXT_DEBUG_FLAG);
		state.set_field("GL_CONTEXT_FORWARD_COMPATIBLE_FLAG", SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
		state.set_field("GL_CONTEXT_ROBUST_ACCESS_FLAG", SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG);
		state.set_field("GL_CONTEXT_RESET_ISOLATION_FLAG", SDL_GL_CONTEXT_RESET_ISOLATION_FLAG);

		//SDL_EventType
		state.set_field("QUIT", SDL_QUIT);
		state.set_field("WINDOWEVENT", SDL_WINDOWEVENT);
		state.set_field("SYSWMEVENT", SDL_SYSWMEVENT);
		state.set_field("KEYDOWN", SDL_KEYDOWN);
		state.set_field("KEYUP", SDL_KEYUP);
		state.set_field("TEXTEDITING", SDL_TEXTEDITING);
		state.set_field("TEXTINPUT", SDL_TEXTINPUT);
		state.set_field("MOUSEMOTION", SDL_MOUSEMOTION);
		state.set_field("MOUSEBUTTONDOWN", SDL_MOUSEBUTTONDOWN);
		state.set_field("MOUSEBUTTONUP", SDL_MOUSEBUTTONUP);
		state.set_field("MOUSEWHEEL", SDL_MOUSEWHEEL);
		state.set_field("JOYAXISMOTION", SDL_JOYAXISMOTION);
		state.set_field("JOYBALLMOTION", SDL_JOYBALLMOTION);
		state.set_field("JOYHATMOTION", SDL_JOYHATMOTION);
		state.set_field("JOYBUTTONDOWN", SDL_JOYBUTTONDOWN);
		state.set_field("JOYBUTTONUP", SDL_JOYBUTTONUP);
		state.set_field("JOYDEVICEADDED", SDL_JOYDEVICEADDED);
		state.set_field("JOYDEVICEREMOVED", SDL_JOYDEVICEREMOVED);
		state.set_field("CONTROLLERAXISMOTION", SDL_CONTROLLERAXISMOTION);
		state.set_field("CONTROLLERBUTTONDOWN", SDL_CONTROLLERBUTTONDOWN);
		state.set_field("CONTROLLERBUTTONUP", SDL_CONTROLLERBUTTONUP);
		state.set_field("CONTROLLERDEVICEADDED", SDL_CONTROLLERDEVICEADDED);
		state.set_field("CONTROLLERDEVICEREMOVED", SDL_CONTROLLERDEVICEREMOVED);
		state.set_field("CONTROLLERDEVICEREMAPPED", SDL_CONTROLLERDEVICEREMAPPED);
		state.set_field("FINGERMOTION", SDL_FINGERMOTION);
		state.set_field("FINGERMOTION", SDL_FINGERMOTION);
		state.set_field("FINGERMOTION", SDL_FINGERMOTION);
		state.set_field("DOLLARGESTURE", SDL_DOLLARGESTURE);
		state.set_field("DOLLARRECORD", SDL_DOLLARRECORD);
		state.set_field("MULTIGESTURE", SDL_MULTIGESTURE);
		state.set_field("CLIPBOARDUPDATE", SDL_CLIPBOARDUPDATE);
		state.set_field("DROPFILE", SDL_DROPFILE);
		state.set_field("USEREVENT", SDL_USEREVENT);

		//SDL_Keycode
		state.set_field("K_RETURN", SDLK_RETURN);
		state.set_field("K_ESCAPE", SDLK_ESCAPE);
		state.set_field("K_BACKSPACE", SDLK_BACKSPACE);
		state.set_field("K_TAB", SDLK_TAB);
		state.set_field("K_SPACE", SDLK_SPACE);
		state.set_field("K_EXCLAIM", SDLK_EXCLAIM);
		state.set_field("K_QUOTEDBL", SDLK_QUOTEDBL);
		state.set_field("K_HASH", SDLK_HASH);
		state.set_field("K_PERCENT", SDLK_PERCENT);
		state.set_field("K_DOLLAR", SDLK_DOLLAR);
		state.set_field("K_AMPERSAND", SDLK_AMPERSAND);
		state.set_field("K_QUOTE", SDLK_QUOTE);
		state.set_field("K_LEFTPAREN", SDLK_LEFTPAREN);
		state.set_field("K_RIGHTPAREN", SDLK_RIGHTPAREN);
		state.set_field("K_ASTERISK", SDLK_ASTERISK);
		state.set_field("K_PLUS", SDLK_PLUS);
		state.set_field("K_COMMA", SDLK_COMMA);
		state.set_field("K_MINUS", SDLK_MINUS);
		state.set_field("K_PERIOD", SDLK_PERIOD);
		state.set_field("K_SLASH", SDLK_SLASH);
		state.set_field("K_0", SDLK_0);
		state.set_field("K_1", SDLK_1);
		state.set_field("K_2", SDLK_2);
		state.set_field("K_3", SDLK_3);
		state.set_field("K_4", SDLK_4);
		state.set_field("K_5", SDLK_5);
		state.set_field("K_6", SDLK_6);
		state.set_field("K_7", SDLK_7);
		state.set_field("K_8", SDLK_8);
		state.set_field("K_9", SDLK_9);
		state.set_field("K_COLON", SDLK_COLON);
		state.set_field("K_SEMICOLON", SDLK_SEMICOLON);
		state.set_field("K_LESS", SDLK_LESS);
		state.set_field("K_EQUALS", SDLK_EQUALS);
		state.set_field("K_GREATER", SDLK_GREATER);
		state.set_field("K_QUESTION", SDLK_QUESTION);
		state.set_field("K_AT", SDLK_AT);
		/* 
		   Skip uppercase letters
		 */
		state.set_field("K_LEFTBRACKET", SDLK_LEFTBRACKET);
		state.set_field("K_BACKSLASH", SDLK_BACKSLASH);
		state.set_field("K_RIGHTBRACKET", SDLK_RIGHTBRACKET);
		state.set_field("K_CARET", SDLK_CARET);
		state.set_field("K_UNDERSCORE", SDLK_UNDERSCORE);
		state.set_field("K_BACKQUOTE", SDLK_BACKQUOTE);
		state.set_field("K_a", SDLK_a);
		state.set_field("K_b", SDLK_b);
		state.set_field("K_c", SDLK_c);
		state.set_field("K_d", SDLK_d);
		state.set_field("K_e", SDLK_e);
		state.set_field("K_f", SDLK_f);
		state.set_field("K_g", SDLK_g);
		state.set_field("K_h", SDLK_h);
		state.set_field("K_i", SDLK_i);
		state.set_field("K_j", SDLK_j);
		state.set_field("K_k", SDLK_k);
		state.set_field("K_l", SDLK_l);
		state.set_field("K_m", SDLK_m);
		state.set_field("K_n", SDLK_n);
		state.set_field("K_o", SDLK_o);
		state.set_field("K_p", SDLK_p);
		state.set_field("K_q", SDLK_q);
		state.set_field("K_r", SDLK_r);
		state.set_field("K_s", SDLK_s);
		state.set_field("K_t", SDLK_t);
		state.set_field("K_u", SDLK_u);
		state.set_field("K_v", SDLK_v);
		state.set_field("K_w", SDLK_w);
		state.set_field("K_x", SDLK_x);
		state.set_field("K_y", SDLK_y);
		state.set_field("K_z", SDLK_z);

		state.set_field("K_CAPSLOCK", SDLK_CAPSLOCK);

		state.set_field("K_F1", SDLK_F1);
		state.set_field("K_F2", SDLK_F2);
		state.set_field("K_F3", SDLK_F3);
		state.set_field("K_F4", SDLK_F4);
		state.set_field("K_F5", SDLK_F5);
		state.set_field("K_F6", SDLK_F6);
		state.set_field("K_F7", SDLK_F7);
		state.set_field("K_F8", SDLK_F8);
		state.set_field("K_F9", SDLK_F9);
		state.set_field("K_F10", SDLK_F10);
		state.set_field("K_F11", SDLK_F11);
		state.set_field("K_F12", SDLK_F12);

		state.set_field("K_PRINTSCREEN", SDLK_PRINTSCREEN);
		state.set_field("K_SCROLLLOCK", SDLK_SCROLLLOCK);
		state.set_field("K_PAUSE", SDLK_PAUSE);
		state.set_field("K_INSERT", SDLK_INSERT);
		state.set_field("K_HOME", SDLK_HOME);
		state.set_field("K_PAGEUP", SDLK_PAGEUP);
		state.set_field("K_DELETE", SDLK_DELETE);
		state.set_field("K_END", SDLK_END);
		state.set_field("K_PAGEDOWN", SDLK_PAGEDOWN);
		state.set_field("K_RIGHT", SDLK_RIGHT);
		state.set_field("K_LEFT", SDLK_LEFT);
		state.set_field("K_DOWN", SDLK_DOWN);
		state.set_field("K_UP", SDLK_UP);

		state.set_field("K_NUMLOCKCLEAR", SDLK_NUMLOCKCLEAR);
		state.set_field("K_KP_DIVIDE", SDLK_KP_DIVIDE);
		state.set_field("K_KP_MULTIPLY", SDLK_KP_MULTIPLY);
		state.set_field("K_KP_MINUS", SDLK_KP_MINUS);
		state.set_field("K_KP_PLUS", SDLK_KP_PLUS);
		state.set_field("K_KP_ENTER", SDLK_KP_ENTER);
		state.set_field("K_KP_1", SDLK_KP_1);
		state.set_field("K_KP_2", SDLK_KP_2);
		state.set_field("K_KP_3", SDLK_KP_3);
		state.set_field("K_KP_4", SDLK_KP_4);
		state.set_field("K_KP_5", SDLK_KP_5);
		state.set_field("K_KP_6", SDLK_KP_6);
		state.set_field("K_KP_7", SDLK_KP_7);
		state.set_field("K_KP_8", SDLK_KP_8);
		state.set_field("K_KP_9", SDLK_KP_9);
		state.set_field("K_KP_0", SDLK_KP_0);
		state.set_field("K_KP_PERIOD", SDLK_KP_PERIOD);

		state.set_field("K_APPLICATION", SDLK_APPLICATION);
		state.set_field("K_POWER", SDLK_POWER);
		state.set_field("K_KP_EQUALS", SDLK_KP_EQUALS);
		state.set_field("K_F13", SDLK_F13);
		state.set_field("K_F14", SDLK_F14);
		state.set_field("K_F15", SDLK_F15);
		state.set_field("K_F16", SDLK_F16);
		state.set_field("K_F17", SDLK_F17);
		state.set_field("K_F18", SDLK_F18);
		state.set_field("K_F19", SDLK_F19);
		state.set_field("K_F20", SDLK_F20);
		state.set_field("K_F21", SDLK_F21);
		state.set_field("K_F22", SDLK_F22);
		state.set_field("K_F23", SDLK_F23);
		state.set_field("K_F24", SDLK_F24);
		state.set_field("K_EXECUTE", SDLK_EXECUTE);
		state.set_field("K_HELP", SDLK_HELP);
		state.set_field("K_MENU", SDLK_MENU);
		state.set_field("K_SELECT", SDLK_SELECT);
		state.set_field("K_STOP", SDLK_STOP);
		state.set_field("K_AGAIN", SDLK_AGAIN);
		state.set_field("K_UNDO", SDLK_UNDO);
		state.set_field("K_CUT", SDLK_CUT);
		state.set_field("K_COPY", SDLK_COPY);
		state.set_field("K_PASTE", SDLK_PASTE);
		state.set_field("K_FIND", SDLK_FIND);
		state.set_field("K_MUTE", SDLK_MUTE);
		state.set_field("K_VOLUMEUP", SDLK_VOLUMEUP);
		state.set_field("K_VOLUMEDOWN", SDLK_VOLUMEDOWN);
		state.set_field("K_KP_COMMA", SDLK_KP_COMMA);
		state.set_field("K_KP_EQUALSAS400", SDLK_KP_EQUALSAS400);

		state.set_field("K_ALTERASE", SDLK_ALTERASE);
		state.set_field("K_SYSREQ", SDLK_SYSREQ);
		state.set_field("K_CANCEL", SDLK_CANCEL);
		state.set_field("K_CLEAR", SDLK_CLEAR);
		state.set_field("K_PRIOR", SDLK_PRIOR);
		state.set_field("K_RETURN2", SDLK_RETURN2);
		state.set_field("K_SEPARATOR", SDLK_SEPARATOR);
		state.set_field("K_OUT", SDLK_OUT);
		state.set_field("K_OPER", SDLK_OPER);
		state.set_field("K_CLEARAGAIN", SDLK_CLEARAGAIN);
		state.set_field("K_CRSEL", SDLK_CRSEL);
		state.set_field("K_EXSEL", SDLK_EXSEL);

		state.set_field("K_KP_00", SDLK_KP_00);
		state.set_field("K_KP_000", SDLK_KP_000);
		state.set_field("K_THOUSANDSSEPARATOR", SDLK_THOUSANDSSEPARATOR);
		state.set_field("K_DECIMALSEPARATOR", SDLK_DECIMALSEPARATOR);
		state.set_field("K_CURRENCYUNIT", SDLK_CURRENCYUNIT);
		state.set_field("K_CURRENCYSUBUNIT", SDLK_CURRENCYSUBUNIT);
		state.set_field("K_KP_LEFTPAREN", SDLK_KP_LEFTPAREN);
		state.set_field("K_KP_RIGHTPAREN", SDLK_KP_RIGHTPAREN);
		state.set_field("K_KP_LEFTBRACE", SDLK_KP_LEFTBRACE);
		state.set_field("K_KP_RIGHTBRACE", SDLK_KP_RIGHTBRACE);
		state.set_field("K_KP_TAB", SDLK_KP_TAB);
		state.set_field("K_KP_BACKSPACE", SDLK_KP_BACKSPACE);
		state.set_field("K_KP_A", SDLK_KP_A);
		state.set_field("K_KP_B", SDLK_KP_B);
		state.set_field("K_KP_C", SDLK_KP_C);
		state.set_field("K_KP_D", SDLK_KP_D);
		state.set_field("K_KP_E", SDLK_KP_E);
		state.set_field("K_KP_F", SDLK_KP_F);
		state.set_field("K_KP_XOR", SDLK_KP_XOR);
		state.set_field("K_KP_POWER", SDLK_KP_POWER);
		state.set_field("K_KP_PERCENT", SDLK_KP_PERCENT);
		state.set_field("K_KP_LESS", SDLK_KP_LESS);
		state.set_field("K_KP_GREATER", SDLK_KP_GREATER);
		state.set_field("K_KP_AMPERSAND", SDLK_KP_AMPERSAND);
		state.set_field("K_KP_DBLAMPERSAND", SDLK_KP_DBLAMPERSAND);
		state.set_field("K_KP_VERTICALBAR", SDLK_KP_VERTICALBAR);
		state.set_field("K_KP_DBLVERTICALBAR", SDLK_KP_DBLVERTICALBAR);
		state.set_field("K_KP_COLON", SDLK_KP_COLON);
		state.set_field("K_KP_HASH", SDLK_KP_HASH);
		state.set_field("K_KP_SPACE", SDLK_KP_SPACE);
		state.set_field("K_KP_AT", SDLK_KP_AT);
		state.set_field("K_KP_EXCLAM", SDLK_KP_EXCLAM);
		state.set_field("K_KP_MEMSTORE", SDLK_KP_MEMSTORE);
		state.set_field("K_KP_MEMRECALL", SDLK_KP_MEMRECALL);
		state.set_field("K_KP_MEMCLEAR", SDLK_KP_MEMCLEAR);
		state.set_field("K_KP_MEMADD", SDLK_KP_MEMADD);
		state.set_field("K_KP_MEMSUBTRACT", SDLK_KP_MEMSUBTRACT);
		state.set_field("K_KP_MEMMULTIPLY", SDLK_KP_MEMMULTIPLY);
		state.set_field("K_KP_MEMDIVIDE", SDLK_KP_MEMDIVIDE);
		state.set_field("K_KP_PLUSMINUS", SDLK_KP_PLUSMINUS);
		state.set_field("K_KP_CLEAR", SDLK_KP_CLEAR);
		state.set_field("K_KP_CLEARENTRY", SDLK_KP_CLEARENTRY);
		state.set_field("K_KP_BINARY", SDLK_KP_BINARY);
		state.set_field("K_KP_OCTAL", SDLK_KP_OCTAL);
		state.set_field("K_KP_DECIMAL", SDLK_KP_DECIMAL);
		state.set_field("K_KP_HEXADECIMAL", SDLK_KP_HEXADECIMAL);

		state.set_field("K_LCTRL", SDLK_LCTRL);
		state.set_field("K_LSHIFT", SDLK_LSHIFT);
		state.set_field("K_LALT", SDLK_LALT);
		state.set_field("K_LGUI", SDLK_LGUI);
		state.set_field("K_RCTRL", SDLK_RCTRL);
		state.set_field("K_RSHIFT", SDLK_RSHIFT);
		state.set_field("K_RALT", SDLK_RALT);
		state.set_field("K_RGUI", SDLK_RGUI);

		state.set_field("K_MODE", SDLK_MODE);

		state.set_field("K_AUDIONEXT", SDLK_AUDIONEXT);
		state.set_field("K_AUDIOPREV", SDLK_AUDIOPREV);
		state.set_field("K_AUDIOSTOP", SDLK_AUDIOSTOP);
		state.set_field("K_AUDIOPLAY", SDLK_AUDIOPLAY);
		state.set_field("K_AUDIOMUTE", SDLK_AUDIOMUTE);
		state.set_field("K_MEDIASELECT", SDLK_MEDIASELECT);
		state.set_field("K_WWW", SDLK_WWW);
		state.set_field("K_MAIL", SDLK_MAIL);
		state.set_field("K_CALCULATOR", SDLK_CALCULATOR);
		state.set_field("K_COMPUTER", SDLK_COMPUTER);
		state.set_field("K_AC_SEARCH", SDLK_AC_SEARCH);
		state.set_field("K_AC_HOME", SDLK_AC_HOME);
		state.set_field("K_AC_BACK", SDLK_AC_BACK);
		state.set_field("K_AC_FORWARD", SDLK_AC_FORWARD);
		state.set_field("K_AC_STOP", SDLK_AC_STOP);
		state.set_field("K_AC_REFRESH", SDLK_AC_REFRESH);
		state.set_field("K_AC_BOOKMARKS", SDLK_AC_BOOKMARKS);

		state.set_field("K_BRIGHTNESSDOWN", SDLK_BRIGHTNESSDOWN);
		state.set_field("K_BRIGHTNESSUP", SDLK_BRIGHTNESSUP);
		state.set_field("K_DISPLAYSWITCH", SDLK_DISPLAYSWITCH);
		state.set_field("K_KBDILLUMTOGGLE", SDLK_KBDILLUMTOGGLE);
		state.set_field("K_KBDILLUMDOWN", SDLK_KBDILLUMDOWN);
		state.set_field("K_KBDILLUMUP", SDLK_KBDILLUMUP);
		state.set_field("K_EJECT", SDLK_EJECT);
		state.set_field("K_SLEEP", SDLK_SLEEP);

		//SDL_Scancode
		state.set_field("SC_A", SDL_SCANCODE_A);
		state.set_field("SC_B", SDL_SCANCODE_B);
		state.set_field("SC_C", SDL_SCANCODE_C);
		state.set_field("SC_D", SDL_SCANCODE_D);
		state.set_field("SC_E", SDL_SCANCODE_E);
		state.set_field("SC_F", SDL_SCANCODE_F);
		state.set_field("SC_G", SDL_SCANCODE_G);
		state.set_field("SC_H", SDL_SCANCODE_H);
		state.set_field("SC_I", SDL_SCANCODE_I);
		state.set_field("SC_J", SDL_SCANCODE_J);
		state.set_field("SC_K", SDL_SCANCODE_K);
		state.set_field("SC_L", SDL_SCANCODE_L);
		state.set_field("SC_M", SDL_SCANCODE_M);
		state.set_field("SC_N", SDL_SCANCODE_N);
		state.set_field("SC_O", SDL_SCANCODE_O);
		state.set_field("SC_P", SDL_SCANCODE_P);
		state.set_field("SC_Q", SDL_SCANCODE_Q);
		state.set_field("SC_R", SDL_SCANCODE_R);
		state.set_field("SC_S", SDL_SCANCODE_S);
		state.set_field("SC_T", SDL_SCANCODE_T);
		state.set_field("SC_U", SDL_SCANCODE_U);
		state.set_field("SC_V", SDL_SCANCODE_V);
		state.set_field("SC_W", SDL_SCANCODE_W);
		state.set_field("SC_X", SDL_SCANCODE_X);
		state.set_field("SC_Y", SDL_SCANCODE_Y);
		state.set_field("SC_Z", SDL_SCANCODE_Z);

		state.set_field("SC_1", SDL_SCANCODE_1);
		state.set_field("SC_2", SDL_SCANCODE_2);
		state.set_field("SC_3", SDL_SCANCODE_3);
		state.set_field("SC_4", SDL_SCANCODE_4);
		state.set_field("SC_5", SDL_SCANCODE_5);
		state.set_field("SC_6", SDL_SCANCODE_6);
		state.set_field("SC_7", SDL_SCANCODE_7);
		state.set_field("SC_8", SDL_SCANCODE_8);
		state.set_field("SC_9", SDL_SCANCODE_9);
		state.set_field("SC_0", SDL_SCANCODE_0);

		state.set_field("SC_RETURN", SDL_SCANCODE_RETURN);
		state.set_field("SC_ESCAPE", SDL_SCANCODE_ESCAPE);
		state.set_field("SC_BACKSPACE", SDL_SCANCODE_BACKSPACE);
		state.set_field("SC_TAB", SDL_SCANCODE_TAB);
		state.set_field("SC_SPACE", SDL_SCANCODE_SPACE);

		state.set_field("SC_MINUS", SDL_SCANCODE_MINUS);
		state.set_field("SC_EQUALS", SDL_SCANCODE_EQUALS);
		state.set_field("SC_LEFTBRACKET", SDL_SCANCODE_LEFTBRACKET);
		state.set_field("SC_RIGHTBRACKET", SDL_SCANCODE_RIGHTBRACKET);
		state.set_field("SC_BACKSLASH", SDL_SCANCODE_BACKSLASH);
		state.set_field("SC_NONUSHASH", SDL_SCANCODE_NONUSHASH);
		state.set_field("SC_SEMICOLON", SDL_SCANCODE_SEMICOLON);
		state.set_field("SC_APOSTROPHE", SDL_SCANCODE_APOSTROPHE);
		state.set_field("SC_GRAVE", SDL_SCANCODE_GRAVE);
		state.set_field("SC_COMMA", SDL_SCANCODE_COMMA);
		state.set_field("SC_PERIOD", SDL_SCANCODE_PERIOD);
		state.set_field("SC_SLASH", SDL_SCANCODE_SLASH);

		state.set_field("SC_CAPSLOCK", SDL_SCANCODE_CAPSLOCK);

		state.set_field("SC_F1", SDL_SCANCODE_F1);
		state.set_field("SC_F2", SDL_SCANCODE_F2);
		state.set_field("SC_F3", SDL_SCANCODE_F3);
		state.set_field("SC_F4", SDL_SCANCODE_F4);
		state.set_field("SC_F5", SDL_SCANCODE_F5);
		state.set_field("SC_F6", SDL_SCANCODE_F6);
		state.set_field("SC_F7", SDL_SCANCODE_F7);
		state.set_field("SC_F8", SDL_SCANCODE_F8);
		state.set_field("SC_F9", SDL_SCANCODE_F9);
		state.set_field("SC_F10", SDL_SCANCODE_F10);
		state.set_field("SC_F11", SDL_SCANCODE_F11);
		state.set_field("SC_F12", SDL_SCANCODE_F12);

		state.set_field("SC_PRINTSCREEN", SDL_SCANCODE_PRINTSCREEN);
		state.set_field("SC_SCROLLLOCK", SDL_SCANCODE_SCROLLLOCK);
		state.set_field("SC_PAUSE", SDL_SCANCODE_PAUSE);
		state.set_field("SC_INSERT", SDL_SCANCODE_INSERT);
		state.set_field("SC_HOME", SDL_SCANCODE_HOME);
		state.set_field("SC_PAGEUP", SDL_SCANCODE_PAGEUP);
		state.set_field("SC_DELETE", SDL_SCANCODE_DELETE);
		state.set_field("SC_END", SDL_SCANCODE_END);
		state.set_field("SC_PAGEDOWN", SDL_SCANCODE_PAGEDOWN);
		state.set_field("SC_RIGHT", SDL_SCANCODE_RIGHT);
		state.set_field("SC_LEFT", SDL_SCANCODE_LEFT);
		state.set_field("SC_DOWN", SDL_SCANCODE_DOWN);
		state.set_field("SC_UP", SDL_SCANCODE_UP);

		state.set_field("SC_NUMLOCKCLEAR", SDL_SCANCODE_NUMLOCKCLEAR);
		state.set_field("SC_KP_DIVIDE", SDL_SCANCODE_KP_DIVIDE);
		state.set_field("SC_KP_MULTIPLY", SDL_SCANCODE_KP_MULTIPLY);
		state.set_field("SC_KP_MINUS", SDL_SCANCODE_KP_MINUS);
		state.set_field("SC_KP_PLUS", SDL_SCANCODE_KP_PLUS);
		state.set_field("SC_KP_ENTER", SDL_SCANCODE_KP_ENTER);
		state.set_field("SC_KP_1", SDL_SCANCODE_KP_1);
		state.set_field("SC_KP_2", SDL_SCANCODE_KP_2);
		state.set_field("SC_KP_3", SDL_SCANCODE_KP_3);
		state.set_field("SC_KP_4", SDL_SCANCODE_KP_4);
		state.set_field("SC_KP_5", SDL_SCANCODE_KP_5);
		state.set_field("SC_KP_6", SDL_SCANCODE_KP_6);
		state.set_field("SC_KP_7", SDL_SCANCODE_KP_7);
		state.set_field("SC_KP_8", SDL_SCANCODE_KP_8);
		state.set_field("SC_KP_9", SDL_SCANCODE_KP_9);
		state.set_field("SC_KP_0", SDL_SCANCODE_KP_0);
		state.set_field("SC_KP_PERIOD", SDL_SCANCODE_KP_PERIOD);

		state.set_field("SC_NONUSBACKSLASH", SDL_SCANCODE_NONUSBACKSLASH);
		state.set_field("SC_APPLICATION", SDL_SCANCODE_APPLICATION);
		state.set_field("SC_POWER", SDL_SCANCODE_POWER);
		state.set_field("SC_KP_EQUALS", SDL_SCANCODE_KP_EQUALS);
		state.set_field("SC_F13", SDL_SCANCODE_F13);
		state.set_field("SC_F14", SDL_SCANCODE_F14);
		state.set_field("SC_F15", SDL_SCANCODE_F15);
		state.set_field("SC_F16", SDL_SCANCODE_F16);
		state.set_field("SC_F17", SDL_SCANCODE_F17);
		state.set_field("SC_F18", SDL_SCANCODE_F18);
		state.set_field("SC_F19", SDL_SCANCODE_F19);
		state.set_field("SC_F20", SDL_SCANCODE_F20);
		state.set_field("SC_F21", SDL_SCANCODE_F21);
		state.set_field("SC_F22", SDL_SCANCODE_F22);
		state.set_field("SC_F23", SDL_SCANCODE_F23);
		state.set_field("SC_F24", SDL_SCANCODE_F24);
		state.set_field("SC_EXECUTE", SDL_SCANCODE_EXECUTE);
		state.set_field("SC_HELP", SDL_SCANCODE_HELP);
		state.set_field("SC_MENU", SDL_SCANCODE_MENU);
		state.set_field("SC_SELECT", SDL_SCANCODE_SELECT);
		state.set_field("SC_STOP", SDL_SCANCODE_STOP);
		state.set_field("SC_AGAIN", SDL_SCANCODE_AGAIN);
		state.set_field("SC_UNDO", SDL_SCANCODE_UNDO);
		state.set_field("SC_CUT", SDL_SCANCODE_CUT);
		state.set_field("SC_COPY", SDL_SCANCODE_COPY);
		state.set_field("SC_PASTE", SDL_SCANCODE_PASTE);
		state.set_field("SC_FIND", SDL_SCANCODE_FIND);
		state.set_field("SC_MUTE", SDL_SCANCODE_MUTE);
		state.set_field("SC_VOLUMEUP", SDL_SCANCODE_VOLUMEUP);
		state.set_field("SC_VOLUMEDOWN", SDL_SCANCODE_VOLUMEDOWN);

		state.set_field("SC_KP_COMMA", SDL_SCANCODE_KP_COMMA);
		state.set_field("SC_KP_EQUALSAS400", SDL_SCANCODE_KP_EQUALSAS400);

		state.set_field("SC_INTERNATIONAL1", SDL_SCANCODE_INTERNATIONAL1);
                                           
		state.set_field("SC_INTERNATIONAL2", SDL_SCANCODE_INTERNATIONAL2);
		state.set_field("SC_INTERNATIONAL3", SDL_SCANCODE_INTERNATIONAL3);
		state.set_field("SC_INTERNATIONAL4", SDL_SCANCODE_INTERNATIONAL4);
		state.set_field("SC_INTERNATIONAL5", SDL_SCANCODE_INTERNATIONAL5);
		state.set_field("SC_INTERNATIONAL6", SDL_SCANCODE_INTERNATIONAL6);
		state.set_field("SC_INTERNATIONAL7", SDL_SCANCODE_INTERNATIONAL7);
		state.set_field("SC_INTERNATIONAL8", SDL_SCANCODE_INTERNATIONAL8);
		state.set_field("SC_INTERNATIONAL9", SDL_SCANCODE_INTERNATIONAL9);
		state.set_field("SC_LANG1", SDL_SCANCODE_LANG1);
		state.set_field("SC_LANG2", SDL_SCANCODE_LANG2);
		state.set_field("SC_LANG3", SDL_SCANCODE_LANG3);
		state.set_field("SC_LANG4", SDL_SCANCODE_LANG4);
		state.set_field("SC_LANG5", SDL_SCANCODE_LANG5);
		state.set_field("SC_LANG6", SDL_SCANCODE_LANG6);
		state.set_field("SC_LANG7", SDL_SCANCODE_LANG7);
		state.set_field("SC_LANG8", SDL_SCANCODE_LANG8);
		state.set_field("SC_LANG9", SDL_SCANCODE_LANG9);

		state.set_field("SC_ALTERASE", SDL_SCANCODE_ALTERASE);
		state.set_field("SC_SYSREQ", SDL_SCANCODE_SYSREQ);
		state.set_field("SC_CANCEL", SDL_SCANCODE_CANCEL);
		state.set_field("SC_CLEAR", SDL_SCANCODE_CLEAR);
		state.set_field("SC_PRIOR", SDL_SCANCODE_PRIOR);
		state.set_field("SC_RETURN2", SDL_SCANCODE_RETURN2);
		state.set_field("SC_SEPARATOR", SDL_SCANCODE_SEPARATOR);
		state.set_field("SC_OUT", SDL_SCANCODE_OUT);
		state.set_field("SC_OPER", SDL_SCANCODE_OPER);
		state.set_field("SC_CLEARAGAIN", SDL_SCANCODE_CLEARAGAIN);
		state.set_field("SC_CRSEL", SDL_SCANCODE_CRSEL);
		state.set_field("SC_EXSEL", SDL_SCANCODE_EXSEL);

		state.set_field("SC_KP_00", SDL_SCANCODE_KP_00);
		state.set_field("SC_KP_000", SDL_SCANCODE_KP_000);
		state.set_field("SC_THOUSANDSSEPARATOR", SDL_SCANCODE_THOUSANDSSEPARATOR);
		state.set_field("SC_DECIMALSEPARATOR", SDL_SCANCODE_DECIMALSEPARATOR);
		state.set_field("SC_CURRENCYUNIT", SDL_SCANCODE_CURRENCYUNIT);
		state.set_field("SC_CURRENCYSUBUNIT", SDL_SCANCODE_CURRENCYSUBUNIT);
		state.set_field("SC_KP_LEFTPAREN", SDL_SCANCODE_KP_LEFTPAREN);
		state.set_field("SC_KP_RIGHTPAREN", SDL_SCANCODE_KP_RIGHTPAREN);
		state.set_field("SC_KP_LEFTBRACE", SDL_SCANCODE_KP_LEFTBRACE);
		state.set_field("SC_KP_RIGHTBRACE", SDL_SCANCODE_KP_RIGHTBRACE);
		state.set_field("SC_KP_TAB", SDL_SCANCODE_KP_TAB);
		state.set_field("SC_KP_BACKSPACE", SDL_SCANCODE_KP_BACKSPACE);
		state.set_field("SC_KP_A", SDL_SCANCODE_KP_A);
		state.set_field("SC_KP_B", SDL_SCANCODE_KP_B);
		state.set_field("SC_KP_C", SDL_SCANCODE_KP_C);
		state.set_field("SC_KP_D", SDL_SCANCODE_KP_D);
		state.set_field("SC_KP_E", SDL_SCANCODE_KP_E);
		state.set_field("SC_KP_F", SDL_SCANCODE_KP_F);
		state.set_field("SC_KP_XOR", SDL_SCANCODE_KP_XOR);
		state.set_field("SC_KP_POWER", SDL_SCANCODE_KP_POWER);
		state.set_field("SC_KP_PERCENT", SDL_SCANCODE_KP_PERCENT);
		state.set_field("SC_KP_LESS", SDL_SCANCODE_KP_LESS);
		state.set_field("SC_KP_GREATER", SDL_SCANCODE_KP_GREATER);
		state.set_field("SC_KP_AMPERSAND", SDL_SCANCODE_KP_AMPERSAND);
		state.set_field("SC_KP_DBLAMPERSAND", SDL_SCANCODE_KP_DBLAMPERSAND);
		state.set_field("SC_KP_VERTICALBAR", SDL_SCANCODE_KP_VERTICALBAR);
		state.set_field("SC_KP_DBLVERTICALBAR", SDL_SCANCODE_KP_DBLVERTICALBAR);
		state.set_field("SC_KP_COLON", SDL_SCANCODE_KP_COLON);
		state.set_field("SC_KP_HASH", SDL_SCANCODE_KP_HASH);
		state.set_field("SC_KP_SPACE", SDL_SCANCODE_KP_SPACE);
		state.set_field("SC_KP_AT", SDL_SCANCODE_KP_AT);
		state.set_field("SC_KP_EXCLAM", SDL_SCANCODE_KP_EXCLAM);
		state.set_field("SC_KP_MEMSTORE", SDL_SCANCODE_KP_MEMSTORE);
		state.set_field("SC_KP_MEMRECALL", SDL_SCANCODE_KP_MEMRECALL);
		state.set_field("SC_KP_MEMCLEAR", SDL_SCANCODE_KP_MEMCLEAR);
		state.set_field("SC_KP_MEMADD", SDL_SCANCODE_KP_MEMADD);
		state.set_field("SC_KP_MEMSUBTRACT", SDL_SCANCODE_KP_MEMSUBTRACT);
		state.set_field("SC_KP_MEMMULTIPLY", SDL_SCANCODE_KP_MEMMULTIPLY);
		state.set_field("SC_KP_MEMDIVIDE", SDL_SCANCODE_KP_MEMDIVIDE);
		state.set_field("SC_KP_PLUSMINUS", SDL_SCANCODE_KP_PLUSMINUS);
		state.set_field("SC_KP_CLEAR", SDL_SCANCODE_KP_CLEAR);
		state.set_field("SC_KP_CLEARENTRY", SDL_SCANCODE_KP_CLEARENTRY);
		state.set_field("SC_KP_BINARY", SDL_SCANCODE_KP_BINARY);
		state.set_field("SC_KP_OCTAL", SDL_SCANCODE_KP_OCTAL);
		state.set_field("SC_KP_DECIMAL", SDL_SCANCODE_KP_DECIMAL);
		state.set_field("SC_KP_HEXADECIMAL", SDL_SCANCODE_KP_HEXADECIMAL);

		state.set_field("SC_LCTRL", SDL_SCANCODE_LCTRL);
		state.set_field("SC_LSHIFT", SDL_SCANCODE_LSHIFT);
		state.set_field("SC_LALT", SDL_SCANCODE_LALT);
		state.set_field("SC_LGUI", SDL_SCANCODE_LGUI);
		state.set_field("SC_RCTRL", SDL_SCANCODE_RCTRL);
		state.set_field("SC_RSHIFT", SDL_SCANCODE_RSHIFT);
		state.set_field("SC_RALT", SDL_SCANCODE_RALT);
		state.set_field("SC_RGUI", SDL_SCANCODE_RGUI);

		state.set_field("SC_MODE", SDL_SCANCODE_MODE);

		state.set_field("SC_AUDIONEXT", SDL_SCANCODE_AUDIONEXT);
		state.set_field("SC_AUDIOPREV", SDL_SCANCODE_AUDIOPREV);
		state.set_field("SC_AUDIOSTOP", SDL_SCANCODE_AUDIOSTOP);
		state.set_field("SC_AUDIOPLAY", SDL_SCANCODE_AUDIOPLAY);
		state.set_field("SC_AUDIOMUTE", SDL_SCANCODE_AUDIOMUTE);
		state.set_field("SC_MEDIASELECT", SDL_SCANCODE_MEDIASELECT);
		state.set_field("SC_WWW", SDL_SCANCODE_WWW);
		state.set_field("SC_MAIL", SDL_SCANCODE_MAIL);
		state.set_field("SC_CALCULATOR", SDL_SCANCODE_CALCULATOR);
		state.set_field("SC_COMPUTER", SDL_SCANCODE_COMPUTER);
		state.set_field("SC_AC_SEARCH", SDL_SCANCODE_AC_SEARCH);
		state.set_field("SC_AC_HOME", SDL_SCANCODE_AC_HOME);
		state.set_field("SC_AC_BACK", SDL_SCANCODE_AC_BACK);
		state.set_field("SC_AC_FORWARD", SDL_SCANCODE_AC_FORWARD);
		state.set_field("SC_AC_STOP", SDL_SCANCODE_AC_STOP);
		state.set_field("SC_AC_REFRESH", SDL_SCANCODE_AC_REFRESH);
		state.set_field("SC_AC_BOOKMARKS", SDL_SCANCODE_AC_BOOKMARKS);
    
		state.set_field("SC_BRIGHTNESSDOWN", SDL_SCANCODE_BRIGHTNESSDOWN);
		state.set_field("SC_BRIGHTNESSUP", SDL_SCANCODE_BRIGHTNESSUP);
		state.set_field("SC_DISPLAYSWITCH", SDL_SCANCODE_DISPLAYSWITCH);
                                          
		state.set_field("SC_KBDILLUMTOGGLE", SDL_SCANCODE_KBDILLUMTOGGLE);
		state.set_field("SC_KBDILLUMDOWN", SDL_SCANCODE_KBDILLUMDOWN);
		state.set_field("SC_KBDILLUMUP", SDL_SCANCODE_KBDILLUMUP);
		state.set_field("SC_EJECT", SDL_SCANCODE_EJECT);
		state.set_field("SC_SLEEP", SDL_SCANCODE_SLEEP);
    
		state.set_field("SC_APP1", SDL_SCANCODE_APP1);
		state.set_field("SC_APP2", SDL_SCANCODE_APP2);

		//SDL_Keymod
		state.set_field("KMOD_NONE", KMOD_NONE);
		state.set_field("KMOD_LSHIFT", KMOD_LSHIFT);
		state.set_field("KMOD_RSHIFT", KMOD_RSHIFT);
		state.set_field("KMOD_LCTRL", KMOD_LCTRL);
		state.set_field("KMOD_RCTRL", KMOD_RCTRL);
		state.set_field("KMOD_LALT", KMOD_LALT);
		state.set_field("KMOD_RALT", KMOD_RALT);
		state.set_field("KMOD_LGUI", KMOD_LGUI);
		state.set_field("KMOD_RGUI", KMOD_RGUI);
		state.set_field("KMOD_NUM", KMOD_NUM);
		state.set_field("KMOD_CAPS", KMOD_CAPS);
		state.set_field("KMOD_MODE", KMOD_MODE);
		state.set_field("KMOD_RESERVED", KMOD_RESERVED);
		state.set_field("KMOD_CTRL", KMOD_LCTRL|KMOD_RCTRL);
		state.set_field("KMOD_SHIFT", KMOD_LSHIFT|KMOD_RSHIFT);
		state.set_field("KMOD_ALT", KMOD_LALT|KMOD_RALT);
		state.set_field("KMOD_GUI", KMOD_LGUI|KMOD_RGUI);

		//SDL_AudioSpec allowed changes
		state.set_field("AUDIO_ALLOW_FREQUENCY_CHANGE", SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
		state.set_field("AUDIO_ALLOW_FORMAT_CHANGE", SDL_AUDIO_ALLOW_FORMAT_CHANGE);
		state.set_field("AUDIO_ALLOW_CHANNELS_CHANGE", SDL_AUDIO_ALLOW_CHANNELS_CHANGE);
		state.set_field("AUDIO_ALLOW_ANY_CHANGE", SDL_AUDIO_ALLOW_ANY_CHANGE);

		//SDL_AudioFormat
		state.set_field("AUDIO_U8", AUDIO_U8);
		state.set_field("AUDIO_S8", AUDIO_S8);
		state.set_field("AUDIO_U16LSB", AUDIO_U16LSB);
		state.set_field("AUDIO_S16LSB", AUDIO_S16LSB);
		state.set_field("AUDIO_U16MSB", AUDIO_U16MSB);
		state.set_field("AUDIO_S16MSB", AUDIO_S16MSB);
		state.set_field("AUDIO_U16", AUDIO_U16);
		state.set_field("AUDIO_S16", AUDIO_S16);
		state.set_field("AUDIO_S32LSB", AUDIO_S32LSB);
		state.set_field("AUDIO_S32MSB", AUDIO_S32MSB);
		state.set_field("AUDIO_S32", AUDIO_S32);
		state.set_field("AUDIO_F32LSB", AUDIO_F32LSB);
		state.set_field("AUDIO_F32MSB", AUDIO_F32MSB);
		state.set_field("AUDIO_F32", AUDIO_F32);
		state.set_field("AUDIO_U16SYS", AUDIO_U16SYS);
		state.set_field("AUDIO_S16SYS", AUDIO_S16SYS);
		state.set_field("AUDIO_S32SYS", AUDIO_S32SYS);
		state.set_field("AUDIO_F32SYS", AUDIO_F32SYS);

		//SDL_AudioStatus
		state.set_field("AUDIO_STOPPED", SDL_AUDIO_STOPPED);
		state.set_field("AUDIO_PLAYING", SDL_AUDIO_PLAYING);
		state.set_field("AUDIO_PAUSED", SDL_AUDIO_PAUSED);

		//SDL_mixer INIT
		state.set_field("MIX_INIT_FLAC", MIX_INIT_FLAC);
		state.set_field("MIX_INIT_MOD", MIX_INIT_MOD);
		state.set_field("MIX_INIT_MP3", MIX_INIT_MP3);
		state.set_field("MIX_INIT_OGG", MIX_INIT_OGG);
		state.set_field("MIX_INIT_FLUIDSYNTH", MIX_INIT_FLUIDSYNTH);
		state.set_field("MIX_INIT_MODPLUG", MIX_INIT_MODPLUG);

		//SDL_image INIT
		state.set_field("IMG_INIT_JPG", IMG_INIT_JPG);
		state.set_field("IMG_INIT_PNG", IMG_INIT_PNG);
		state.set_field("IMG_INIT_TIF", IMG_INIT_TIF);
		state.set_field("IMG_INIT_WEBP", IMG_INIT_WEBP);

		//SDL_ttf
		state.set_field("TTF_STYLE_BOLD", TTF_STYLE_BOLD);
		state.set_field("TTF_STYLE_ITALIC", TTF_STYLE_ITALIC);
		state.set_field("TTF_STYLE_UNDERLINE", TTF_STYLE_UNDERLINE);
		state.set_field("TTF_STYLE_STRIKETHROUGH", TTF_STYLE_STRIKETHROUGH);
		state.set_field("TTF_STYLE_NORMAL", TTF_STYLE_NORMAL);

		state.set_field("TTF_HINTING_NORMAL", TTF_HINTING_NORMAL);
		state.set_field("TTF_HINTING_LIGHT", TTF_HINTING_LIGHT);
		state.set_field("TTF_HINTING_MONO", TTF_HINTING_MONO);
		state.set_field("TTF_HINTING_NONE", TTF_HINTING_NONE);

		
	}
}