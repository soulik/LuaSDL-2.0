#include "common.hpp"
namespace LuaSDL{
	void initConstants(State & state){
		Stack * stack = state.stack;
		//SDL_Init
		stack->setField<int>("INIT_TIMER",					SDL_INIT_TIMER);
		stack->setField<int>("INIT_AUDIO",					SDL_INIT_AUDIO);
		stack->setField<int>("INIT_VIDEO",					SDL_INIT_VIDEO);
		stack->setField<int>("INIT_JOYSTICK",				SDL_INIT_JOYSTICK);
		stack->setField<int>("INIT_HAPTIC",					SDL_INIT_HAPTIC);
		stack->setField<int>("INIT_EVENTS",					SDL_INIT_EVENTS);
		stack->setField<int>("INIT_GAMECONTROLLER",			SDL_INIT_GAMECONTROLLER);
		stack->setField<int>("INIT_NOPARACHUTE",				SDL_INIT_NOPARACHUTE);
		stack->setField<int>("INIT_EVERYTHING",				SDL_INIT_EVERYTHING);

		//SDL_PowerState
		stack->setField<int>("POWERSTATE_UNKNOWN",			SDL_POWERSTATE_UNKNOWN);
		stack->setField<int>("POWERSTATE_ON_BATTERY",		SDL_POWERSTATE_ON_BATTERY);
		stack->setField<int>("POWERSTATE_NO_BATTERY",		SDL_POWERSTATE_NO_BATTERY);
		stack->setField<int>("POWERSTATE_CHARGING",			SDL_POWERSTATE_CHARGING);
		stack->setField<int>("POWERSTATE_CHARGED",			SDL_POWERSTATE_CHARGED);

		//SDL_MessageBox
		stack->setField<int>("MESSAGEBOX_ERROR",				SDL_MESSAGEBOX_ERROR);
		stack->setField<int>("MESSAGEBOX_WARNING",			SDL_MESSAGEBOX_WARNING);
		stack->setField<int>("MESSAGEBOX_INFORMATION",		SDL_MESSAGEBOX_INFORMATION);

		//SDL_MessageBox button data
		stack->setField<int>("MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT", SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
		stack->setField<int>("MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT", SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);

		//SDL_MessageBox_Color
		stack->setField<int>("MESSAGEBOX_COLOR_BACKGROUND",	SDL_MESSAGEBOX_COLOR_BACKGROUND);
		stack->setField<int>("MESSAGEBOX_COLOR_TEXT",		SDL_MESSAGEBOX_COLOR_TEXT);
		stack->setField<int>("MESSAGEBOX_COLOR_BUTTON_BORDER",		SDL_MESSAGEBOX_COLOR_BUTTON_BORDER);
		stack->setField<int>("MESSAGEBOX_COLOR_BUTTON_BACKGROUND",	SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
		stack->setField<int>("MESSAGEBOX_COLOR_BUTTON_SELECTED",		SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED);
		stack->setField<int>("MESSAGEBOX_COLOR_MAX",			SDL_MESSAGEBOX_COLOR_MAX);

		//SDL_WindowFlags
		stack->setField<int>("WINDOW_FULLSCREEN",			SDL_WINDOW_FULLSCREEN);
		stack->setField<int>("WINDOW_OPENGL",				SDL_WINDOW_OPENGL);
		stack->setField<int>("WINDOW_SHOWN",					SDL_WINDOW_SHOWN);
		stack->setField<int>("WINDOW_HIDDEN",				SDL_WINDOW_HIDDEN);
		stack->setField<int>("WINDOW_BORDERLESS",			SDL_WINDOW_BORDERLESS);
		stack->setField<int>("WINDOW_RESIZABLE",				SDL_WINDOW_RESIZABLE);
		stack->setField<int>("WINDOW_MINIMIZED",				SDL_WINDOW_MINIMIZED);
		stack->setField<int>("WINDOW_MAXIMIZED",				SDL_WINDOW_MAXIMIZED);
		stack->setField<int>("WINDOW_INPUT_GRABBED",			SDL_WINDOW_INPUT_GRABBED);
		stack->setField<int>("WINDOW_INPUT_FOCUS",			SDL_WINDOW_INPUT_FOCUS);
		stack->setField<int>("WINDOW_MOUSE_FOCUS",			SDL_WINDOW_MOUSE_FOCUS);
		stack->setField<int>("WINDOW_FULLSCREEN_DESKTOP",	SDL_WINDOW_FULLSCREEN_DESKTOP);
		stack->setField<int>("WINDOW_FOREIGN", SDL_WINDOW_FOREIGN);
		stack->setField<int>("WINDOW_ALLOW_HIGHDPI", SDL_WINDOW_ALLOW_HIGHDPI);
		stack->setField<int>("WINDOW_MOUSE_CAPTURE", SDL_WINDOW_MOUSE_CAPTURE);

		stack->setField<int>("WINDOWPOS_UNDEFINED_MASK",		SDL_WINDOWPOS_UNDEFINED_MASK);
		stack->setField<int>("WINDOWPOS_CENTERED_MASK",		SDL_WINDOWPOS_CENTERED_MASK);

		//SDL_WindowEventID
		stack->setField<int>("WINDOWEVENT_NONE",				SDL_WINDOWEVENT_NONE);
		stack->setField<int>("WINDOWEVENT_SHOWN",			SDL_WINDOWEVENT_SHOWN);
		stack->setField<int>("WINDOWEVENT_HIDDEN",			SDL_WINDOWEVENT_HIDDEN);
		stack->setField<int>("WINDOWEVENT_EXPOSED",			SDL_WINDOWEVENT_EXPOSED);
		stack->setField<int>("WINDOWEVENT_MOVED",			SDL_WINDOWEVENT_MOVED);
		stack->setField<int>("WINDOWEVENT_RESIZED",			SDL_WINDOWEVENT_RESIZED);
		stack->setField<int>("WINDOWEVENT_SIZE_CHANGED",		SDL_WINDOWEVENT_SIZE_CHANGED);
		stack->setField<int>("WINDOWEVENT_MINIMIZED",		SDL_WINDOWEVENT_MINIMIZED);
		stack->setField<int>("WINDOWEVENT_MAXIMIZED",		SDL_WINDOWEVENT_MAXIMIZED);
		stack->setField<int>("WINDOWEVENT_RESTORED",			SDL_WINDOWEVENT_RESTORED);
		stack->setField<int>("WINDOWEVENT_ENTER",			SDL_WINDOWEVENT_ENTER);
		stack->setField<int>("WINDOWEVENT_LEAVE",			SDL_WINDOWEVENT_LEAVE);
		stack->setField<int>("WINDOWEVENT_FOCUS_GAINED",		SDL_WINDOWEVENT_FOCUS_GAINED);
		stack->setField<int>("WINDOWEVENT_FOCUS_LOST",		SDL_WINDOWEVENT_FOCUS_LOST);
		stack->setField<int>("WINDOWEVENT_CLOSE",			SDL_WINDOWEVENT_CLOSE);

		//Pixel formats
		stack->setField<int>("PIXELFORMAT_UNKNOWN",			SDL_PIXELFORMAT_UNKNOWN);
		stack->setField<int>("PIXELFORMAT_INDEX1LSB",		SDL_PIXELFORMAT_INDEX1LSB);
		stack->setField<int>("PIXELFORMAT_INDEX1MSB",		SDL_PIXELFORMAT_INDEX1MSB);
		stack->setField<int>("PIXELFORMAT_INDEX4LSB",		SDL_PIXELFORMAT_INDEX4LSB);
		stack->setField<int>("PIXELFORMAT_INDEX4MSB",		SDL_PIXELFORMAT_INDEX4MSB);
		stack->setField<int>("PIXELFORMAT_INDEX8",			SDL_PIXELFORMAT_INDEX8);
		stack->setField<int>("PIXELFORMAT_RGB332",			SDL_PIXELFORMAT_RGB332);
		stack->setField<int>("PIXELFORMAT_RGB444",			SDL_PIXELFORMAT_RGB444);
		stack->setField<int>("PIXELFORMAT_RGB555",			SDL_PIXELFORMAT_RGB555);
		stack->setField<int>("PIXELFORMAT_BGR555",			SDL_PIXELFORMAT_BGR555);
		stack->setField<int>("PIXELFORMAT_ARGB4444",			SDL_PIXELFORMAT_ARGB4444);
		stack->setField<int>("PIXELFORMAT_RGBA4444",			SDL_PIXELFORMAT_RGBA4444);
		stack->setField<int>("PIXELFORMAT_ABGR4444",			SDL_PIXELFORMAT_ABGR4444);
		stack->setField<int>("PIXELFORMAT_BGRA4444",			SDL_PIXELFORMAT_BGRA4444);
		stack->setField<int>("PIXELFORMAT_ARGB1555",			SDL_PIXELFORMAT_ARGB1555);
		stack->setField<int>("PIXELFORMAT_RGBA5551",			SDL_PIXELFORMAT_RGBA5551);
		stack->setField<int>("PIXELFORMAT_ABGR1555",			SDL_PIXELFORMAT_ABGR1555);
		stack->setField<int>("PIXELFORMAT_BGRA5551",			SDL_PIXELFORMAT_BGRA5551);
		stack->setField<int>("PIXELFORMAT_RGB565",			SDL_PIXELFORMAT_RGB565);
		stack->setField<int>("PIXELFORMAT_BGR565",			SDL_PIXELFORMAT_BGR565);
		stack->setField<int>("PIXELFORMAT_RGB24",			SDL_PIXELFORMAT_RGB24);
		stack->setField<int>("PIXELFORMAT_BGR24",			SDL_PIXELFORMAT_BGR24);
		stack->setField<int>("PIXELFORMAT_RGB888",			SDL_PIXELFORMAT_RGB888);
		stack->setField<int>("PIXELFORMAT_RGBX8888",			SDL_PIXELFORMAT_RGBX8888);
		stack->setField<int>("PIXELFORMAT_BGR888",			SDL_PIXELFORMAT_BGR888);
		stack->setField<int>("PIXELFORMAT_BGRX8888",			SDL_PIXELFORMAT_BGRX8888);
		stack->setField<int>("PIXELFORMAT_ARGB8888",			SDL_PIXELFORMAT_ARGB8888);
		stack->setField<int>("PIXELFORMAT_RGBA8888",			SDL_PIXELFORMAT_RGBA8888);
		stack->setField<int>("PIXELFORMAT_ABGR8888",			SDL_PIXELFORMAT_ABGR8888);
		stack->setField<int>("PIXELFORMAT_BGRA8888",			SDL_PIXELFORMAT_BGRA8888);
		stack->setField<int>("PIXELFORMAT_ARGB2101010",		SDL_PIXELFORMAT_ARGB2101010);
		stack->setField<int>("PIXELFORMAT_YV12",				SDL_PIXELFORMAT_YV12);
		stack->setField<int>("PIXELFORMAT_IYUV",				SDL_PIXELFORMAT_IYUV);
		stack->setField<int>("PIXELFORMAT_YUY2",				SDL_PIXELFORMAT_YUY2);
		stack->setField<int>("PIXELFORMAT_UYVY",				SDL_PIXELFORMAT_UYVY);
		stack->setField<int>("PIXELFORMAT_YVYU",				SDL_PIXELFORMAT_YVYU);

		//SDL_RendererFlags
		stack->setField<int>("RENDERER_SOFTWARE",			SDL_RENDERER_SOFTWARE);
		stack->setField<int>("RENDERER_ACCELERATED",			SDL_RENDERER_ACCELERATED);
		stack->setField<int>("RENDERER_PRESENTVSYNC",		SDL_RENDERER_PRESENTVSYNC);
		stack->setField<int>("RENDERER_TARGETTEXTURE",		SDL_RENDERER_TARGETTEXTURE);

		//SDL_TextureAccess
		stack->setField<int>("TEXTUREACCESS_STATIC",			SDL_TEXTUREACCESS_STATIC);
		stack->setField<int>("TEXTUREACCESS_STREAMING", SDL_TEXTUREACCESS_STREAMING);
		stack->setField<int>("TEXTUREACCESS_TARGET", SDL_TEXTUREACCESS_TARGET);

		//SDL_TextureModulate
		stack->setField<int>("TEXTUREMODULATE_NONE",			SDL_TEXTUREMODULATE_NONE);
		stack->setField<int>("TEXTUREMODULATE_COLOR",		SDL_TEXTUREMODULATE_COLOR);
		stack->setField<int>("TEXTUREMODULATE_ALPHA",		SDL_TEXTUREMODULATE_ALPHA);

		//SDL_BlendMode
		stack->setField<int>("BLENDMODE_NONE",				SDL_BLENDMODE_NONE);
		stack->setField<int>("BLENDMODE_BLEND",				SDL_BLENDMODE_BLEND);
		stack->setField<int>("BLENDMODE_ADD",				SDL_BLENDMODE_ADD);
		stack->setField<int>("BLENDMODE_MOD",				SDL_BLENDMODE_MOD);

		//SDL_RendererFlip
		stack->setField<int>("FLIP_NONE", SDL_FLIP_NONE);
		stack->setField<int>("FLIP_HORIZONTAL", SDL_FLIP_HORIZONTAL);
		stack->setField<int>("FLIP_VERTICAL", SDL_FLIP_VERTICAL);

		//Hit tests
		stack->setField<int>("HITTEST_NORMAL", SDL_HITTEST_NORMAL);
		stack->setField<int>("HITTEST_DRAGGABLE", SDL_HITTEST_DRAGGABLE);
		stack->setField<int>("HITTEST_RESIZE_TOPLEFT", SDL_HITTEST_RESIZE_TOPLEFT);
		stack->setField<int>("HITTEST_RESIZE_TOP", SDL_HITTEST_RESIZE_TOP);
		stack->setField<int>("HITTEST_RESIZE_TOPRIGHT", SDL_HITTEST_RESIZE_TOPRIGHT);
		stack->setField<int>("HITTEST_RESIZE_RIGHT", SDL_HITTEST_RESIZE_RIGHT);
		stack->setField<int>("HITTEST_RESIZE_BOTTOMRIGHT", SDL_HITTEST_RESIZE_BOTTOMRIGHT);
		stack->setField<int>("HITTEST_RESIZE_BOTTOM", SDL_HITTEST_RESIZE_BOTTOM);
		stack->setField<int>("HITTEST_RESIZE_BOTTOMLEFT", SDL_HITTEST_RESIZE_BOTTOMLEFT);
		stack->setField<int>("HITTEST_RESIZE_LEFT", SDL_HITTEST_RESIZE_LEFT);

		//SDL_GLattr
		stack->setField<int>("GL_RED_SIZE",					SDL_GL_RED_SIZE);
		stack->setField<int>("GL_GREEN_SIZE",				SDL_GL_GREEN_SIZE);
		stack->setField<int>("GL_BLUE_SIZE",					SDL_GL_BLUE_SIZE);
		stack->setField<int>("GL_ALPHA_SIZE",				SDL_GL_ALPHA_SIZE);
		stack->setField<int>("GL_BUFFER_SIZE",				SDL_GL_BUFFER_SIZE);
		stack->setField<int>("GL_DOUBLEBUFFER",				SDL_GL_DOUBLEBUFFER);
		stack->setField<int>("GL_DEPTH_SIZE",				SDL_GL_DEPTH_SIZE);
		stack->setField<int>("GL_STENCIL_SIZE",				SDL_GL_STENCIL_SIZE);
		stack->setField<int>("GL_ACCUM_RED_SIZE",			SDL_GL_ACCUM_RED_SIZE);
		stack->setField<int>("GL_ACCUM_GREEN_SIZE",			SDL_GL_ACCUM_GREEN_SIZE);
		stack->setField<int>("GL_ACCUM_BLUE_SIZE",			SDL_GL_ACCUM_BLUE_SIZE);
		stack->setField<int>("GL_ACCUM_ALPHA_SIZE",			SDL_GL_ACCUM_ALPHA_SIZE);
		stack->setField<int>("GL_STEREO",					SDL_GL_STEREO);
		stack->setField<int>("GL_MULTISAMPLEBUFFERS",		SDL_GL_MULTISAMPLEBUFFERS);
		stack->setField<int>("GL_MULTISAMPLESAMPLES",		SDL_GL_MULTISAMPLESAMPLES);
		stack->setField<int>("GL_ACCELERATED_VISUAL",		SDL_GL_ACCELERATED_VISUAL);
		stack->setField<int>("GL_RETAINED_BACKING",			SDL_GL_RETAINED_BACKING);
		stack->setField<int>("GL_CONTEXT_MAJOR_VERSION",		SDL_GL_CONTEXT_MAJOR_VERSION);
		stack->setField<int>("GL_CONTEXT_MINOR_VERSION",		SDL_GL_CONTEXT_MINOR_VERSION);
		stack->setField<int>("GL_CONTEXT_EGL",				SDL_GL_CONTEXT_EGL);
		stack->setField<int>("GL_CONTEXT_FLAGS",				SDL_GL_CONTEXT_FLAGS);
		stack->setField<int>("GL_CONTEXT_PROFILE_MASK",		SDL_GL_CONTEXT_PROFILE_MASK);
		stack->setField<int>("GL_SHARE_WITH_CURRENT_CONTEXT", SDL_GL_SHARE_WITH_CURRENT_CONTEXT);
		stack->setField<int>("GL_FRAMEBUFFER_SRGB_CAPABLE", SDL_GL_FRAMEBUFFER_SRGB_CAPABLE);
		stack->setField<int>("GL_CONTEXT_RELEASE_BEHAVIOR", SDL_GL_CONTEXT_RELEASE_BEHAVIOR);

		//SDL_GLprofile
		stack->setField<int>("GL_CONTEXT_PROFILE_CORE",		SDL_GL_CONTEXT_PROFILE_CORE);
		stack->setField<int>("GL_CONTEXT_PROFILE_COMPATIBILITY", SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		stack->setField<int>("GL_CONTEXT_PROFILE_ES",		SDL_GL_CONTEXT_PROFILE_ES);

		//SDL_GLcontextFlag
		stack->setField<int>("GL_CONTEXT_DEBUG_FLAG",		SDL_GL_CONTEXT_DEBUG_FLAG);
		stack->setField<int>("GL_CONTEXT_FORWARD_COMPATIBLE_FLAG", SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
		stack->setField<int>("GL_CONTEXT_ROBUST_ACCESS_FLAG", SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG);
		stack->setField<int>("GL_CONTEXT_RESET_ISOLATION_FLAG", SDL_GL_CONTEXT_RESET_ISOLATION_FLAG);

		//SDL_EventType
		stack->setField<int>("QUIT", SDL_QUIT);
		stack->setField<int>("WINDOWEVENT", SDL_WINDOWEVENT);
		stack->setField<int>("SYSWMEVENT", SDL_SYSWMEVENT);
		stack->setField<int>("KEYDOWN", SDL_KEYDOWN);
		stack->setField<int>("KEYUP", SDL_KEYUP);
		stack->setField<int>("TEXTEDITING", SDL_TEXTEDITING);
		stack->setField<int>("TEXTINPUT", SDL_TEXTINPUT);
		stack->setField<int>("MOUSEMOTION", SDL_MOUSEMOTION);
		stack->setField<int>("MOUSEBUTTONDOWN", SDL_MOUSEBUTTONDOWN);
		stack->setField<int>("MOUSEBUTTONUP", SDL_MOUSEBUTTONUP);
		stack->setField<int>("MOUSEWHEEL", SDL_MOUSEWHEEL);
		stack->setField<int>("JOYAXISMOTION", SDL_JOYAXISMOTION);
		stack->setField<int>("JOYBALLMOTION", SDL_JOYBALLMOTION);
		stack->setField<int>("JOYHATMOTION", SDL_JOYHATMOTION);
		stack->setField<int>("JOYBUTTONDOWN", SDL_JOYBUTTONDOWN);
		stack->setField<int>("JOYBUTTONUP", SDL_JOYBUTTONUP);
		stack->setField<int>("JOYDEVICEADDED", SDL_JOYDEVICEADDED);
		stack->setField<int>("JOYDEVICEREMOVED", SDL_JOYDEVICEREMOVED);
		stack->setField<int>("CONTROLLERAXISMOTION", SDL_CONTROLLERAXISMOTION);
		stack->setField<int>("CONTROLLERBUTTONDOWN", SDL_CONTROLLERBUTTONDOWN);
		stack->setField<int>("CONTROLLERBUTTONUP", SDL_CONTROLLERBUTTONUP);
		stack->setField<int>("CONTROLLERDEVICEADDED", SDL_CONTROLLERDEVICEADDED);
		stack->setField<int>("CONTROLLERDEVICEREMOVED", SDL_CONTROLLERDEVICEREMOVED);
		stack->setField<int>("CONTROLLERDEVICEREMAPPED", SDL_CONTROLLERDEVICEREMAPPED);
		
		stack->setField<int>("AUDIODEVICEADDED", SDL_AUDIODEVICEADDED);
		stack->setField<int>("AUDIODEVICEREMOVED", SDL_AUDIODEVICEREMOVED);
		stack->setField<int>("DROPFILE", SDL_DROPFILE);
		stack->setField<int>("CLIPBOARDUPDATE", SDL_CLIPBOARDUPDATE);
		stack->setField<int>("MULTIGESTURE", SDL_MULTIGESTURE);
		stack->setField<int>("DOLLARRECORD", SDL_DOLLARRECORD);
		stack->setField<int>("DOLLARGESTURE", SDL_DOLLARGESTURE);
		stack->setField<int>("FINGERMOTION", SDL_FINGERMOTION);
		stack->setField<int>("FINGERUP", SDL_FINGERUP);
		stack->setField<int>("FINGERDOWN", SDL_FINGERDOWN);
		
		stack->setField<int>("APP_TERMINATING", SDL_APP_TERMINATING);
		stack->setField<int>("APP_LOWMEMORY", SDL_APP_LOWMEMORY);
		stack->setField<int>("APP_WILLENTERBACKGROUND", SDL_APP_WILLENTERBACKGROUND);
		stack->setField<int>("APP_DIDENTERBACKGROUND", SDL_APP_DIDENTERBACKGROUND);
		stack->setField<int>("APP_WILLENTERFOREGROUND", SDL_APP_WILLENTERFOREGROUND);
		stack->setField<int>("APP_DIDENTERFOREGROUND", SDL_APP_DIDENTERFOREGROUND);

		stack->setField<int>("RENDER_TARGETS_RESET", SDL_RENDER_TARGETS_RESET);
		stack->setField<int>("RENDER_DEVICE_RESET", SDL_RENDER_DEVICE_RESET);

		stack->setField<int>("CONTROLLER_AXIS_LEFTX", SDL_CONTROLLER_AXIS_LEFTX);
		stack->setField<int>("CONTROLLER_AXIS_LEFTY", SDL_CONTROLLER_AXIS_LEFTY);
		stack->setField<int>("CONTROLLER_AXIS_RIGHTX", SDL_CONTROLLER_AXIS_RIGHTX);
		stack->setField<int>("CONTROLLER_AXIS_RIGHTY", SDL_CONTROLLER_AXIS_RIGHTY);
		stack->setField<int>("CONTROLLER_AXIS_TRIGGERLEFT", SDL_CONTROLLER_AXIS_TRIGGERLEFT);
		stack->setField<int>("CONTROLLER_AXIS_TRIGGERRIGHT", SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

		stack->setField<int>("CONTROLLER_BUTTON_A", SDL_CONTROLLER_BUTTON_A);
		stack->setField<int>("CONTROLLER_BUTTON_B", SDL_CONTROLLER_BUTTON_B);
		stack->setField<int>("CONTROLLER_BUTTON_X", SDL_CONTROLLER_BUTTON_X);
		stack->setField<int>("CONTROLLER_BUTTON_Y", SDL_CONTROLLER_BUTTON_Y);
		stack->setField<int>("CONTROLLER_BUTTON_BACK", SDL_CONTROLLER_BUTTON_BACK);
		stack->setField<int>("CONTROLLER_BUTTON_GUIDE", SDL_CONTROLLER_BUTTON_GUIDE);
		stack->setField<int>("CONTROLLER_BUTTON_START", SDL_CONTROLLER_BUTTON_START);
		stack->setField<int>("CONTROLLER_BUTTON_LEFTSTICK", SDL_CONTROLLER_BUTTON_LEFTSTICK);
		stack->setField<int>("CONTROLLER_BUTTON_RIGHTSTICK", SDL_CONTROLLER_BUTTON_RIGHTSTICK);
		stack->setField<int>("CONTROLLER_BUTTON_LEFTSHOULDER", SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
		stack->setField<int>("CONTROLLER_BUTTON_RIGHTSHOULDER", SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
		stack->setField<int>("CONTROLLER_BUTTON_DPAD_UP", SDL_CONTROLLER_BUTTON_DPAD_UP);
		stack->setField<int>("CONTROLLER_BUTTON_DPAD_DOWN", SDL_CONTROLLER_BUTTON_DPAD_DOWN);
		stack->setField<int>("CONTROLLER_BUTTON_DPAD_LEFT", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
		stack->setField<int>("CONTROLLER_BUTTON_DPAD_RIGHT", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

		stack->setField<int>("CONTROLLER_BINDTYPE_BUTTON", SDL_CONTROLLER_BINDTYPE_BUTTON);
		stack->setField<int>("CONTROLLER_BINDTYPE_AXIS", SDL_CONTROLLER_BINDTYPE_AXIS);
		stack->setField<int>("CONTROLLER_BINDTYPE_HAT", SDL_CONTROLLER_BINDTYPE_HAT);

		stack->setField<int>("HAPTIC_INFINITY", SDL_HAPTIC_INFINITY);	

		stack->setField<int>("HAPTIC_CONSTANT", SDL_HAPTIC_CONSTANT);
		stack->setField<int>("HAPTIC_SINE", SDL_HAPTIC_SINE);
#ifdef SDL_HAPTIC_SQUARE
		stack->setField<int>("HAPTIC_SQUARE", SDL_HAPTIC_SQUARE);
#endif
		stack->setField<int>("HAPTIC_TRIANGLE", SDL_HAPTIC_TRIANGLE);
		stack->setField<int>("HAPTIC_SAWTOOTHUP", SDL_HAPTIC_SAWTOOTHUP);
		stack->setField<int>("HAPTIC_SAWTOOTHDOWN", SDL_HAPTIC_SAWTOOTHDOWN);
		stack->setField<int>("HAPTIC_SPRING", SDL_HAPTIC_SPRING);
		stack->setField<int>("HAPTIC_DAMPER", SDL_HAPTIC_DAMPER);
		stack->setField<int>("HAPTIC_INERTIA", SDL_HAPTIC_INERTIA);
		stack->setField<int>("HAPTIC_FRICTION", SDL_HAPTIC_FRICTION);
		stack->setField<int>("HAPTIC_RAMP", SDL_HAPTIC_RAMP);
		stack->setField<int>("HAPTIC_LEFTRIGHT", SDL_HAPTIC_LEFTRIGHT);
		stack->setField<int>("HAPTIC_CUSTOM", SDL_HAPTIC_CUSTOM);

		stack->setField<int>("HAPTIC_POLAR", SDL_HAPTIC_POLAR);
		stack->setField<int>("HAPTIC_CARTESIAN", SDL_HAPTIC_CARTESIAN);
		stack->setField<int>("HAPTIC_SPHERICAL", SDL_HAPTIC_SPHERICAL);

		stack->setField<int>("FINGERMOTION", SDL_FINGERMOTION);
		stack->setField<int>("FINGERMOTION", SDL_FINGERMOTION);
		stack->setField<int>("FINGERMOTION", SDL_FINGERMOTION);
		stack->setField<int>("DOLLARGESTURE", SDL_DOLLARGESTURE);
		stack->setField<int>("DOLLARRECORD", SDL_DOLLARRECORD);
		stack->setField<int>("MULTIGESTURE", SDL_MULTIGESTURE);
		stack->setField<int>("CLIPBOARDUPDATE", SDL_CLIPBOARDUPDATE);
		stack->setField<int>("DROPFILE", SDL_DROPFILE);
		stack->setField<int>("USEREVENT", SDL_USEREVENT);

		//Hints
		stack->setField<const std::string &>("HINT_ACCELEROMETER_AS_JOYSTICK", SDL_HINT_ACCELEROMETER_AS_JOYSTICK);
		stack->setField<const std::string &>("HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION", SDL_HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION);
		stack->setField<const std::string &>("HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION", SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION);
		stack->setField<const std::string &>("HINT_EMSCRIPTEN_KEYBOARD_ELEMENT", SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT);
		stack->setField<const std::string &>("HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH", SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH);
		stack->setField<const std::string &>("HINT_FRAMEBUFFER_ACCELERATION", SDL_HINT_FRAMEBUFFER_ACCELERATION);
		stack->setField<const std::string &>("HINT_GAMECONTROLLERCONFIG", SDL_HINT_GAMECONTROLLERCONFIG);
		stack->setField<const std::string &>("HINT_GRAB_KEYBOARD", SDL_HINT_GRAB_KEYBOARD);
		stack->setField<const std::string &>("HINT_IDLE_TIMER_DISABLED", SDL_HINT_IDLE_TIMER_DISABLED);
		stack->setField<const std::string &>("HINT_IME_INTERNAL_EDITING", SDL_HINT_IME_INTERNAL_EDITING);
		stack->setField<const std::string &>("HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS", SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS);
		stack->setField<const std::string &>("HINT_MAC_BACKGROUND_APP", SDL_HINT_MAC_BACKGROUND_APP);
		stack->setField<const std::string &>("HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK", SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK);
		stack->setField<const std::string &>("HINT_MOUSE_RELATIVE_MODE_WARP", SDL_HINT_MOUSE_RELATIVE_MODE_WARP);
		stack->setField<const std::string &>("HINT_NO_SIGNAL_HANDLERS", SDL_HINT_NO_SIGNAL_HANDLERS);
		stack->setField<const std::string &>("HINT_ORIENTATIONS", SDL_HINT_ORIENTATIONS);
		stack->setField<const std::string &>("HINT_RENDER_DIRECT3D11_DEBUG", SDL_HINT_RENDER_DIRECT3D11_DEBUG);
		stack->setField<const std::string &>("HINT_RENDER_DIRECT3D_THREADSAFE", SDL_HINT_RENDER_DIRECT3D_THREADSAFE);
		stack->setField<const std::string &>("HINT_RENDER_DRIVER", SDL_HINT_RENDER_DRIVER);
		stack->setField<const std::string &>("HINT_RENDER_OPENGL_SHADERS", SDL_HINT_RENDER_OPENGL_SHADERS);
		stack->setField<const std::string &>("HINT_RENDER_SCALE_QUALITY", SDL_HINT_RENDER_SCALE_QUALITY);
		stack->setField<const std::string &>("HINT_RENDER_VSYNC", SDL_HINT_RENDER_VSYNC);
		stack->setField<const std::string &>("HINT_THREAD_STACK_SIZE", SDL_HINT_THREAD_STACK_SIZE);
		stack->setField<const std::string &>("HINT_TIMER_RESOLUTION", SDL_HINT_TIMER_RESOLUTION);
		stack->setField<const std::string &>("HINT_VIDEO_ALLOW_SCREENSAVER", SDL_HINT_VIDEO_ALLOW_SCREENSAVER);
		stack->setField<const std::string &>("HINT_VIDEO_HIGHDPI_DISABLED", SDL_HINT_VIDEO_HIGHDPI_DISABLED);
		stack->setField<const std::string &>("HINT_VIDEO_MAC_FULLSCREEN_SPACES", SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES);
		stack->setField<const std::string &>("HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS", SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
		stack->setField<const std::string &>("HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT", SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT);
		stack->setField<const std::string &>("HINT_VIDEO_WIN_D3DCOMPILER", SDL_HINT_VIDEO_WIN_D3DCOMPILER);
		stack->setField<const std::string &>("HINT_VIDEO_X11_XINERAMA", SDL_HINT_VIDEO_X11_XINERAMA);
		stack->setField<const std::string &>("HINT_VIDEO_X11_XRANDR", SDL_HINT_VIDEO_X11_XRANDR);
		stack->setField<const std::string &>("HINT_VIDEO_X11_XVIDMODE", SDL_HINT_VIDEO_X11_XVIDMODE);
		stack->setField<const std::string &>("HINT_WINDOWS_ENABLE_MESSAGELOOP", SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP);
		stack->setField<const std::string &>("HINT_WINDOWS_NO_CLOSE_ON_ALT_F4", SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4);
		stack->setField<const std::string &>("HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN", SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN);
		stack->setField<const std::string &>("HINT_WINRT_HANDLE_BACK_BUTTON", SDL_HINT_WINRT_HANDLE_BACK_BUTTON);
		stack->setField<const std::string &>("HINT_WINRT_PRIVACY_POLICY_LABEL", SDL_HINT_WINRT_PRIVACY_POLICY_LABEL);
		stack->setField<const std::string &>("HINT_WINRT_PRIVACY_POLICY_URL", SDL_HINT_WINRT_PRIVACY_POLICY_URL);
		stack->setField<const std::string &>("HINT_XINPUT_ENABLED", SDL_HINT_XINPUT_ENABLED);
		stack->setField<const std::string &>("HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING", SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING);

		//Log priority
		stack->setField<int>("LOG_CATEGORY_APPLICATION", SDL_LOG_CATEGORY_APPLICATION);
		stack->setField<int>("LOG_CATEGORY_ASSERT", SDL_LOG_CATEGORY_ASSERT);
		stack->setField<int>("LOG_CATEGORY_TEST", SDL_LOG_CATEGORY_TEST);
		stack->setField<int>("LOG_CATEGORY_ERROR", SDL_LOG_CATEGORY_ERROR);
		stack->setField<int>("LOG_CATEGORY_SYSTEM", SDL_LOG_CATEGORY_SYSTEM);
		stack->setField<int>("LOG_CATEGORY_AUDIO", SDL_LOG_CATEGORY_AUDIO);
		stack->setField<int>("LOG_CATEGORY_VIDEO", SDL_LOG_CATEGORY_VIDEO);
		stack->setField<int>("LOG_CATEGORY_RENDER", SDL_LOG_CATEGORY_RENDER);
		stack->setField<int>("LOG_CATEGORY_INPUT", SDL_LOG_CATEGORY_INPUT);
		stack->setField<int>("LOG_CATEGORY_CUSTOM", SDL_LOG_CATEGORY_CUSTOM);

		stack->setField<int>("LOG_PRIORITY_INFO", SDL_LOG_PRIORITY_INFO);
		stack->setField<int>("LOG_PRIORITY_WARN", SDL_LOG_PRIORITY_WARN);
		stack->setField<int>("LOG_PRIORITY_VERBOSE", SDL_LOG_PRIORITY_VERBOSE);
		stack->setField<int>("LOG_PRIORITY_CRITICAL", SDL_LOG_PRIORITY_CRITICAL);

		//SDL_Keycode
		stack->setField<int>("K_RETURN", SDLK_RETURN);
		stack->setField<int>("K_ESCAPE", SDLK_ESCAPE);
		stack->setField<int>("K_BACKSPACE", SDLK_BACKSPACE);
		stack->setField<int>("K_TAB", SDLK_TAB);
		stack->setField<int>("K_SPACE", SDLK_SPACE);
		stack->setField<int>("K_EXCLAIM", SDLK_EXCLAIM);
		stack->setField<int>("K_QUOTEDBL", SDLK_QUOTEDBL);
		stack->setField<int>("K_HASH", SDLK_HASH);
		stack->setField<int>("K_PERCENT", SDLK_PERCENT);
		stack->setField<int>("K_DOLLAR", SDLK_DOLLAR);
		stack->setField<int>("K_AMPERSAND", SDLK_AMPERSAND);
		stack->setField<int>("K_QUOTE", SDLK_QUOTE);
		stack->setField<int>("K_LEFTPAREN", SDLK_LEFTPAREN);
		stack->setField<int>("K_RIGHTPAREN", SDLK_RIGHTPAREN);
		stack->setField<int>("K_ASTERISK", SDLK_ASTERISK);
		stack->setField<int>("K_PLUS", SDLK_PLUS);
		stack->setField<int>("K_COMMA", SDLK_COMMA);
		stack->setField<int>("K_MINUS", SDLK_MINUS);
		stack->setField<int>("K_PERIOD", SDLK_PERIOD);
		stack->setField<int>("K_SLASH", SDLK_SLASH);
		stack->setField<int>("K_0", SDLK_0);
		stack->setField<int>("K_1", SDLK_1);
		stack->setField<int>("K_2", SDLK_2);
		stack->setField<int>("K_3", SDLK_3);
		stack->setField<int>("K_4", SDLK_4);
		stack->setField<int>("K_5", SDLK_5);
		stack->setField<int>("K_6", SDLK_6);
		stack->setField<int>("K_7", SDLK_7);
		stack->setField<int>("K_8", SDLK_8);
		stack->setField<int>("K_9", SDLK_9);
		stack->setField<int>("K_COLON", SDLK_COLON);
		stack->setField<int>("K_SEMICOLON", SDLK_SEMICOLON);
		stack->setField<int>("K_LESS", SDLK_LESS);
		stack->setField<int>("K_EQUALS", SDLK_EQUALS);
		stack->setField<int>("K_GREATER", SDLK_GREATER);
		stack->setField<int>("K_QUESTION", SDLK_QUESTION);
		stack->setField<int>("K_AT", SDLK_AT);
		/* 
		   Skip uppercase letters
		 */
		stack->setField<int>("K_LEFTBRACKET", SDLK_LEFTBRACKET);
		stack->setField<int>("K_BACKSLASH", SDLK_BACKSLASH);
		stack->setField<int>("K_RIGHTBRACKET", SDLK_RIGHTBRACKET);
		stack->setField<int>("K_CARET", SDLK_CARET);
		stack->setField<int>("K_UNDERSCORE", SDLK_UNDERSCORE);
		stack->setField<int>("K_BACKQUOTE", SDLK_BACKQUOTE);
		stack->setField<int>("K_a", SDLK_a);
		stack->setField<int>("K_b", SDLK_b);
		stack->setField<int>("K_c", SDLK_c);
		stack->setField<int>("K_d", SDLK_d);
		stack->setField<int>("K_e", SDLK_e);
		stack->setField<int>("K_f", SDLK_f);
		stack->setField<int>("K_g", SDLK_g);
		stack->setField<int>("K_h", SDLK_h);
		stack->setField<int>("K_i", SDLK_i);
		stack->setField<int>("K_j", SDLK_j);
		stack->setField<int>("K_k", SDLK_k);
		stack->setField<int>("K_l", SDLK_l);
		stack->setField<int>("K_m", SDLK_m);
		stack->setField<int>("K_n", SDLK_n);
		stack->setField<int>("K_o", SDLK_o);
		stack->setField<int>("K_p", SDLK_p);
		stack->setField<int>("K_q", SDLK_q);
		stack->setField<int>("K_r", SDLK_r);
		stack->setField<int>("K_s", SDLK_s);
		stack->setField<int>("K_t", SDLK_t);
		stack->setField<int>("K_u", SDLK_u);
		stack->setField<int>("K_v", SDLK_v);
		stack->setField<int>("K_w", SDLK_w);
		stack->setField<int>("K_x", SDLK_x);
		stack->setField<int>("K_y", SDLK_y);
		stack->setField<int>("K_z", SDLK_z);

		stack->setField<int>("K_CAPSLOCK", SDLK_CAPSLOCK);

		stack->setField<int>("K_F1", SDLK_F1);
		stack->setField<int>("K_F2", SDLK_F2);
		stack->setField<int>("K_F3", SDLK_F3);
		stack->setField<int>("K_F4", SDLK_F4);
		stack->setField<int>("K_F5", SDLK_F5);
		stack->setField<int>("K_F6", SDLK_F6);
		stack->setField<int>("K_F7", SDLK_F7);
		stack->setField<int>("K_F8", SDLK_F8);
		stack->setField<int>("K_F9", SDLK_F9);
		stack->setField<int>("K_F10", SDLK_F10);
		stack->setField<int>("K_F11", SDLK_F11);
		stack->setField<int>("K_F12", SDLK_F12);

		stack->setField<int>("K_PRINTSCREEN", SDLK_PRINTSCREEN);
		stack->setField<int>("K_SCROLLLOCK", SDLK_SCROLLLOCK);
		stack->setField<int>("K_PAUSE", SDLK_PAUSE);
		stack->setField<int>("K_INSERT", SDLK_INSERT);
		stack->setField<int>("K_HOME", SDLK_HOME);
		stack->setField<int>("K_PAGEUP", SDLK_PAGEUP);
		stack->setField<int>("K_DELETE", SDLK_DELETE);
		stack->setField<int>("K_END", SDLK_END);
		stack->setField<int>("K_PAGEDOWN", SDLK_PAGEDOWN);
		stack->setField<int>("K_RIGHT", SDLK_RIGHT);
		stack->setField<int>("K_LEFT", SDLK_LEFT);
		stack->setField<int>("K_DOWN", SDLK_DOWN);
		stack->setField<int>("K_UP", SDLK_UP);

		stack->setField<int>("K_NUMLOCKCLEAR", SDLK_NUMLOCKCLEAR);
		stack->setField<int>("K_KP_DIVIDE", SDLK_KP_DIVIDE);
		stack->setField<int>("K_KP_MULTIPLY", SDLK_KP_MULTIPLY);
		stack->setField<int>("K_KP_MINUS", SDLK_KP_MINUS);
		stack->setField<int>("K_KP_PLUS", SDLK_KP_PLUS);
		stack->setField<int>("K_KP_ENTER", SDLK_KP_ENTER);
		stack->setField<int>("K_KP_1", SDLK_KP_1);
		stack->setField<int>("K_KP_2", SDLK_KP_2);
		stack->setField<int>("K_KP_3", SDLK_KP_3);
		stack->setField<int>("K_KP_4", SDLK_KP_4);
		stack->setField<int>("K_KP_5", SDLK_KP_5);
		stack->setField<int>("K_KP_6", SDLK_KP_6);
		stack->setField<int>("K_KP_7", SDLK_KP_7);
		stack->setField<int>("K_KP_8", SDLK_KP_8);
		stack->setField<int>("K_KP_9", SDLK_KP_9);
		stack->setField<int>("K_KP_0", SDLK_KP_0);
		stack->setField<int>("K_KP_PERIOD", SDLK_KP_PERIOD);

		stack->setField<int>("K_APPLICATION", SDLK_APPLICATION);
		stack->setField<int>("K_POWER", SDLK_POWER);
		stack->setField<int>("K_KP_EQUALS", SDLK_KP_EQUALS);
		stack->setField<int>("K_F13", SDLK_F13);
		stack->setField<int>("K_F14", SDLK_F14);
		stack->setField<int>("K_F15", SDLK_F15);
		stack->setField<int>("K_F16", SDLK_F16);
		stack->setField<int>("K_F17", SDLK_F17);
		stack->setField<int>("K_F18", SDLK_F18);
		stack->setField<int>("K_F19", SDLK_F19);
		stack->setField<int>("K_F20", SDLK_F20);
		stack->setField<int>("K_F21", SDLK_F21);
		stack->setField<int>("K_F22", SDLK_F22);
		stack->setField<int>("K_F23", SDLK_F23);
		stack->setField<int>("K_F24", SDLK_F24);
		stack->setField<int>("K_EXECUTE", SDLK_EXECUTE);
		stack->setField<int>("K_HELP", SDLK_HELP);
		stack->setField<int>("K_MENU", SDLK_MENU);
		stack->setField<int>("K_SELECT", SDLK_SELECT);
		stack->setField<int>("K_STOP", SDLK_STOP);
		stack->setField<int>("K_AGAIN", SDLK_AGAIN);
		stack->setField<int>("K_UNDO", SDLK_UNDO);
		stack->setField<int>("K_CUT", SDLK_CUT);
		stack->setField<int>("K_COPY", SDLK_COPY);
		stack->setField<int>("K_PASTE", SDLK_PASTE);
		stack->setField<int>("K_FIND", SDLK_FIND);
		stack->setField<int>("K_MUTE", SDLK_MUTE);
		stack->setField<int>("K_VOLUMEUP", SDLK_VOLUMEUP);
		stack->setField<int>("K_VOLUMEDOWN", SDLK_VOLUMEDOWN);
		stack->setField<int>("K_KP_COMMA", SDLK_KP_COMMA);
		stack->setField<int>("K_KP_EQUALSAS400", SDLK_KP_EQUALSAS400);

		stack->setField<int>("K_ALTERASE", SDLK_ALTERASE);
		stack->setField<int>("K_SYSREQ", SDLK_SYSREQ);
		stack->setField<int>("K_CANCEL", SDLK_CANCEL);
		stack->setField<int>("K_CLEAR", SDLK_CLEAR);
		stack->setField<int>("K_PRIOR", SDLK_PRIOR);
		stack->setField<int>("K_RETURN2", SDLK_RETURN2);
		stack->setField<int>("K_SEPARATOR", SDLK_SEPARATOR);
		stack->setField<int>("K_OUT", SDLK_OUT);
		stack->setField<int>("K_OPER", SDLK_OPER);
		stack->setField<int>("K_CLEARAGAIN", SDLK_CLEARAGAIN);
		stack->setField<int>("K_CRSEL", SDLK_CRSEL);
		stack->setField<int>("K_EXSEL", SDLK_EXSEL);

		stack->setField<int>("K_KP_00", SDLK_KP_00);
		stack->setField<int>("K_KP_000", SDLK_KP_000);
		stack->setField<int>("K_THOUSANDSSEPARATOR", SDLK_THOUSANDSSEPARATOR);
		stack->setField<int>("K_DECIMALSEPARATOR", SDLK_DECIMALSEPARATOR);
		stack->setField<int>("K_CURRENCYUNIT", SDLK_CURRENCYUNIT);
		stack->setField<int>("K_CURRENCYSUBUNIT", SDLK_CURRENCYSUBUNIT);
		stack->setField<int>("K_KP_LEFTPAREN", SDLK_KP_LEFTPAREN);
		stack->setField<int>("K_KP_RIGHTPAREN", SDLK_KP_RIGHTPAREN);
		stack->setField<int>("K_KP_LEFTBRACE", SDLK_KP_LEFTBRACE);
		stack->setField<int>("K_KP_RIGHTBRACE", SDLK_KP_RIGHTBRACE);
		stack->setField<int>("K_KP_TAB", SDLK_KP_TAB);
		stack->setField<int>("K_KP_BACKSPACE", SDLK_KP_BACKSPACE);
		stack->setField<int>("K_KP_A", SDLK_KP_A);
		stack->setField<int>("K_KP_B", SDLK_KP_B);
		stack->setField<int>("K_KP_C", SDLK_KP_C);
		stack->setField<int>("K_KP_D", SDLK_KP_D);
		stack->setField<int>("K_KP_E", SDLK_KP_E);
		stack->setField<int>("K_KP_F", SDLK_KP_F);
		stack->setField<int>("K_KP_XOR", SDLK_KP_XOR);
		stack->setField<int>("K_KP_POWER", SDLK_KP_POWER);
		stack->setField<int>("K_KP_PERCENT", SDLK_KP_PERCENT);
		stack->setField<int>("K_KP_LESS", SDLK_KP_LESS);
		stack->setField<int>("K_KP_GREATER", SDLK_KP_GREATER);
		stack->setField<int>("K_KP_AMPERSAND", SDLK_KP_AMPERSAND);
		stack->setField<int>("K_KP_DBLAMPERSAND", SDLK_KP_DBLAMPERSAND);
		stack->setField<int>("K_KP_VERTICALBAR", SDLK_KP_VERTICALBAR);
		stack->setField<int>("K_KP_DBLVERTICALBAR", SDLK_KP_DBLVERTICALBAR);
		stack->setField<int>("K_KP_COLON", SDLK_KP_COLON);
		stack->setField<int>("K_KP_HASH", SDLK_KP_HASH);
		stack->setField<int>("K_KP_SPACE", SDLK_KP_SPACE);
		stack->setField<int>("K_KP_AT", SDLK_KP_AT);
		stack->setField<int>("K_KP_EXCLAM", SDLK_KP_EXCLAM);
		stack->setField<int>("K_KP_MEMSTORE", SDLK_KP_MEMSTORE);
		stack->setField<int>("K_KP_MEMRECALL", SDLK_KP_MEMRECALL);
		stack->setField<int>("K_KP_MEMCLEAR", SDLK_KP_MEMCLEAR);
		stack->setField<int>("K_KP_MEMADD", SDLK_KP_MEMADD);
		stack->setField<int>("K_KP_MEMSUBTRACT", SDLK_KP_MEMSUBTRACT);
		stack->setField<int>("K_KP_MEMMULTIPLY", SDLK_KP_MEMMULTIPLY);
		stack->setField<int>("K_KP_MEMDIVIDE", SDLK_KP_MEMDIVIDE);
		stack->setField<int>("K_KP_PLUSMINUS", SDLK_KP_PLUSMINUS);
		stack->setField<int>("K_KP_CLEAR", SDLK_KP_CLEAR);
		stack->setField<int>("K_KP_CLEARENTRY", SDLK_KP_CLEARENTRY);
		stack->setField<int>("K_KP_BINARY", SDLK_KP_BINARY);
		stack->setField<int>("K_KP_OCTAL", SDLK_KP_OCTAL);
		stack->setField<int>("K_KP_DECIMAL", SDLK_KP_DECIMAL);
		stack->setField<int>("K_KP_HEXADECIMAL", SDLK_KP_HEXADECIMAL);

		stack->setField<int>("K_LCTRL", SDLK_LCTRL);
		stack->setField<int>("K_LSHIFT", SDLK_LSHIFT);
		stack->setField<int>("K_LALT", SDLK_LALT);
		stack->setField<int>("K_LGUI", SDLK_LGUI);
		stack->setField<int>("K_RCTRL", SDLK_RCTRL);
		stack->setField<int>("K_RSHIFT", SDLK_RSHIFT);
		stack->setField<int>("K_RALT", SDLK_RALT);
		stack->setField<int>("K_RGUI", SDLK_RGUI);

		stack->setField<int>("K_MODE", SDLK_MODE);

		stack->setField<int>("K_AUDIONEXT", SDLK_AUDIONEXT);
		stack->setField<int>("K_AUDIOPREV", SDLK_AUDIOPREV);
		stack->setField<int>("K_AUDIOSTOP", SDLK_AUDIOSTOP);
		stack->setField<int>("K_AUDIOPLAY", SDLK_AUDIOPLAY);
		stack->setField<int>("K_AUDIOMUTE", SDLK_AUDIOMUTE);
		stack->setField<int>("K_MEDIASELECT", SDLK_MEDIASELECT);
		stack->setField<int>("K_WWW", SDLK_WWW);
		stack->setField<int>("K_MAIL", SDLK_MAIL);
		stack->setField<int>("K_CALCULATOR", SDLK_CALCULATOR);
		stack->setField<int>("K_COMPUTER", SDLK_COMPUTER);
		stack->setField<int>("K_AC_SEARCH", SDLK_AC_SEARCH);
		stack->setField<int>("K_AC_HOME", SDLK_AC_HOME);
		stack->setField<int>("K_AC_BACK", SDLK_AC_BACK);
		stack->setField<int>("K_AC_FORWARD", SDLK_AC_FORWARD);
		stack->setField<int>("K_AC_STOP", SDLK_AC_STOP);
		stack->setField<int>("K_AC_REFRESH", SDLK_AC_REFRESH);
		stack->setField<int>("K_AC_BOOKMARKS", SDLK_AC_BOOKMARKS);

		stack->setField<int>("K_BRIGHTNESSDOWN", SDLK_BRIGHTNESSDOWN);
		stack->setField<int>("K_BRIGHTNESSUP", SDLK_BRIGHTNESSUP);
		stack->setField<int>("K_DISPLAYSWITCH", SDLK_DISPLAYSWITCH);
		stack->setField<int>("K_KBDILLUMTOGGLE", SDLK_KBDILLUMTOGGLE);
		stack->setField<int>("K_KBDILLUMDOWN", SDLK_KBDILLUMDOWN);
		stack->setField<int>("K_KBDILLUMUP", SDLK_KBDILLUMUP);
		stack->setField<int>("K_EJECT", SDLK_EJECT);
		stack->setField<int>("K_SLEEP", SDLK_SLEEP);

		//SDL_Scancode
		stack->setField<int>("SC_A", SDL_SCANCODE_A);
		stack->setField<int>("SC_B", SDL_SCANCODE_B);
		stack->setField<int>("SC_C", SDL_SCANCODE_C);
		stack->setField<int>("SC_D", SDL_SCANCODE_D);
		stack->setField<int>("SC_E", SDL_SCANCODE_E);
		stack->setField<int>("SC_F", SDL_SCANCODE_F);
		stack->setField<int>("SC_G", SDL_SCANCODE_G);
		stack->setField<int>("SC_H", SDL_SCANCODE_H);
		stack->setField<int>("SC_I", SDL_SCANCODE_I);
		stack->setField<int>("SC_J", SDL_SCANCODE_J);
		stack->setField<int>("SC_K", SDL_SCANCODE_K);
		stack->setField<int>("SC_L", SDL_SCANCODE_L);
		stack->setField<int>("SC_M", SDL_SCANCODE_M);
		stack->setField<int>("SC_N", SDL_SCANCODE_N);
		stack->setField<int>("SC_O", SDL_SCANCODE_O);
		stack->setField<int>("SC_P", SDL_SCANCODE_P);
		stack->setField<int>("SC_Q", SDL_SCANCODE_Q);
		stack->setField<int>("SC_R", SDL_SCANCODE_R);
		stack->setField<int>("SC_S", SDL_SCANCODE_S);
		stack->setField<int>("SC_T", SDL_SCANCODE_T);
		stack->setField<int>("SC_U", SDL_SCANCODE_U);
		stack->setField<int>("SC_V", SDL_SCANCODE_V);
		stack->setField<int>("SC_W", SDL_SCANCODE_W);
		stack->setField<int>("SC_X", SDL_SCANCODE_X);
		stack->setField<int>("SC_Y", SDL_SCANCODE_Y);
		stack->setField<int>("SC_Z", SDL_SCANCODE_Z);

		stack->setField<int>("SC_1", SDL_SCANCODE_1);
		stack->setField<int>("SC_2", SDL_SCANCODE_2);
		stack->setField<int>("SC_3", SDL_SCANCODE_3);
		stack->setField<int>("SC_4", SDL_SCANCODE_4);
		stack->setField<int>("SC_5", SDL_SCANCODE_5);
		stack->setField<int>("SC_6", SDL_SCANCODE_6);
		stack->setField<int>("SC_7", SDL_SCANCODE_7);
		stack->setField<int>("SC_8", SDL_SCANCODE_8);
		stack->setField<int>("SC_9", SDL_SCANCODE_9);
		stack->setField<int>("SC_0", SDL_SCANCODE_0);

		stack->setField<int>("SC_RETURN", SDL_SCANCODE_RETURN);
		stack->setField<int>("SC_ESCAPE", SDL_SCANCODE_ESCAPE);
		stack->setField<int>("SC_BACKSPACE", SDL_SCANCODE_BACKSPACE);
		stack->setField<int>("SC_TAB", SDL_SCANCODE_TAB);
		stack->setField<int>("SC_SPACE", SDL_SCANCODE_SPACE);

		stack->setField<int>("SC_MINUS", SDL_SCANCODE_MINUS);
		stack->setField<int>("SC_EQUALS", SDL_SCANCODE_EQUALS);
		stack->setField<int>("SC_LEFTBRACKET", SDL_SCANCODE_LEFTBRACKET);
		stack->setField<int>("SC_RIGHTBRACKET", SDL_SCANCODE_RIGHTBRACKET);
		stack->setField<int>("SC_BACKSLASH", SDL_SCANCODE_BACKSLASH);
		stack->setField<int>("SC_NONUSHASH", SDL_SCANCODE_NONUSHASH);
		stack->setField<int>("SC_SEMICOLON", SDL_SCANCODE_SEMICOLON);
		stack->setField<int>("SC_APOSTROPHE", SDL_SCANCODE_APOSTROPHE);
		stack->setField<int>("SC_GRAVE", SDL_SCANCODE_GRAVE);
		stack->setField<int>("SC_COMMA", SDL_SCANCODE_COMMA);
		stack->setField<int>("SC_PERIOD", SDL_SCANCODE_PERIOD);
		stack->setField<int>("SC_SLASH", SDL_SCANCODE_SLASH);

		stack->setField<int>("SC_CAPSLOCK", SDL_SCANCODE_CAPSLOCK);

		stack->setField<int>("SC_F1", SDL_SCANCODE_F1);
		stack->setField<int>("SC_F2", SDL_SCANCODE_F2);
		stack->setField<int>("SC_F3", SDL_SCANCODE_F3);
		stack->setField<int>("SC_F4", SDL_SCANCODE_F4);
		stack->setField<int>("SC_F5", SDL_SCANCODE_F5);
		stack->setField<int>("SC_F6", SDL_SCANCODE_F6);
		stack->setField<int>("SC_F7", SDL_SCANCODE_F7);
		stack->setField<int>("SC_F8", SDL_SCANCODE_F8);
		stack->setField<int>("SC_F9", SDL_SCANCODE_F9);
		stack->setField<int>("SC_F10", SDL_SCANCODE_F10);
		stack->setField<int>("SC_F11", SDL_SCANCODE_F11);
		stack->setField<int>("SC_F12", SDL_SCANCODE_F12);

		stack->setField<int>("SC_PRINTSCREEN", SDL_SCANCODE_PRINTSCREEN);
		stack->setField<int>("SC_SCROLLLOCK", SDL_SCANCODE_SCROLLLOCK);
		stack->setField<int>("SC_PAUSE", SDL_SCANCODE_PAUSE);
		stack->setField<int>("SC_INSERT", SDL_SCANCODE_INSERT);
		stack->setField<int>("SC_HOME", SDL_SCANCODE_HOME);
		stack->setField<int>("SC_PAGEUP", SDL_SCANCODE_PAGEUP);
		stack->setField<int>("SC_DELETE", SDL_SCANCODE_DELETE);
		stack->setField<int>("SC_END", SDL_SCANCODE_END);
		stack->setField<int>("SC_PAGEDOWN", SDL_SCANCODE_PAGEDOWN);
		stack->setField<int>("SC_RIGHT", SDL_SCANCODE_RIGHT);
		stack->setField<int>("SC_LEFT", SDL_SCANCODE_LEFT);
		stack->setField<int>("SC_DOWN", SDL_SCANCODE_DOWN);
		stack->setField<int>("SC_UP", SDL_SCANCODE_UP);

		stack->setField<int>("SC_NUMLOCKCLEAR", SDL_SCANCODE_NUMLOCKCLEAR);
		stack->setField<int>("SC_KP_DIVIDE", SDL_SCANCODE_KP_DIVIDE);
		stack->setField<int>("SC_KP_MULTIPLY", SDL_SCANCODE_KP_MULTIPLY);
		stack->setField<int>("SC_KP_MINUS", SDL_SCANCODE_KP_MINUS);
		stack->setField<int>("SC_KP_PLUS", SDL_SCANCODE_KP_PLUS);
		stack->setField<int>("SC_KP_ENTER", SDL_SCANCODE_KP_ENTER);
		stack->setField<int>("SC_KP_1", SDL_SCANCODE_KP_1);
		stack->setField<int>("SC_KP_2", SDL_SCANCODE_KP_2);
		stack->setField<int>("SC_KP_3", SDL_SCANCODE_KP_3);
		stack->setField<int>("SC_KP_4", SDL_SCANCODE_KP_4);
		stack->setField<int>("SC_KP_5", SDL_SCANCODE_KP_5);
		stack->setField<int>("SC_KP_6", SDL_SCANCODE_KP_6);
		stack->setField<int>("SC_KP_7", SDL_SCANCODE_KP_7);
		stack->setField<int>("SC_KP_8", SDL_SCANCODE_KP_8);
		stack->setField<int>("SC_KP_9", SDL_SCANCODE_KP_9);
		stack->setField<int>("SC_KP_0", SDL_SCANCODE_KP_0);
		stack->setField<int>("SC_KP_PERIOD", SDL_SCANCODE_KP_PERIOD);

		stack->setField<int>("SC_NONUSBACKSLASH", SDL_SCANCODE_NONUSBACKSLASH);
		stack->setField<int>("SC_APPLICATION", SDL_SCANCODE_APPLICATION);
		stack->setField<int>("SC_POWER", SDL_SCANCODE_POWER);
		stack->setField<int>("SC_KP_EQUALS", SDL_SCANCODE_KP_EQUALS);
		stack->setField<int>("SC_F13", SDL_SCANCODE_F13);
		stack->setField<int>("SC_F14", SDL_SCANCODE_F14);
		stack->setField<int>("SC_F15", SDL_SCANCODE_F15);
		stack->setField<int>("SC_F16", SDL_SCANCODE_F16);
		stack->setField<int>("SC_F17", SDL_SCANCODE_F17);
		stack->setField<int>("SC_F18", SDL_SCANCODE_F18);
		stack->setField<int>("SC_F19", SDL_SCANCODE_F19);
		stack->setField<int>("SC_F20", SDL_SCANCODE_F20);
		stack->setField<int>("SC_F21", SDL_SCANCODE_F21);
		stack->setField<int>("SC_F22", SDL_SCANCODE_F22);
		stack->setField<int>("SC_F23", SDL_SCANCODE_F23);
		stack->setField<int>("SC_F24", SDL_SCANCODE_F24);
		stack->setField<int>("SC_EXECUTE", SDL_SCANCODE_EXECUTE);
		stack->setField<int>("SC_HELP", SDL_SCANCODE_HELP);
		stack->setField<int>("SC_MENU", SDL_SCANCODE_MENU);
		stack->setField<int>("SC_SELECT", SDL_SCANCODE_SELECT);
		stack->setField<int>("SC_STOP", SDL_SCANCODE_STOP);
		stack->setField<int>("SC_AGAIN", SDL_SCANCODE_AGAIN);
		stack->setField<int>("SC_UNDO", SDL_SCANCODE_UNDO);
		stack->setField<int>("SC_CUT", SDL_SCANCODE_CUT);
		stack->setField<int>("SC_COPY", SDL_SCANCODE_COPY);
		stack->setField<int>("SC_PASTE", SDL_SCANCODE_PASTE);
		stack->setField<int>("SC_FIND", SDL_SCANCODE_FIND);
		stack->setField<int>("SC_MUTE", SDL_SCANCODE_MUTE);
		stack->setField<int>("SC_VOLUMEUP", SDL_SCANCODE_VOLUMEUP);
		stack->setField<int>("SC_VOLUMEDOWN", SDL_SCANCODE_VOLUMEDOWN);

		stack->setField<int>("SC_KP_COMMA", SDL_SCANCODE_KP_COMMA);
		stack->setField<int>("SC_KP_EQUALSAS400", SDL_SCANCODE_KP_EQUALSAS400);

		stack->setField<int>("SC_INTERNATIONAL1", SDL_SCANCODE_INTERNATIONAL1);
                                           
		stack->setField<int>("SC_INTERNATIONAL2", SDL_SCANCODE_INTERNATIONAL2);
		stack->setField<int>("SC_INTERNATIONAL3", SDL_SCANCODE_INTERNATIONAL3);
		stack->setField<int>("SC_INTERNATIONAL4", SDL_SCANCODE_INTERNATIONAL4);
		stack->setField<int>("SC_INTERNATIONAL5", SDL_SCANCODE_INTERNATIONAL5);
		stack->setField<int>("SC_INTERNATIONAL6", SDL_SCANCODE_INTERNATIONAL6);
		stack->setField<int>("SC_INTERNATIONAL7", SDL_SCANCODE_INTERNATIONAL7);
		stack->setField<int>("SC_INTERNATIONAL8", SDL_SCANCODE_INTERNATIONAL8);
		stack->setField<int>("SC_INTERNATIONAL9", SDL_SCANCODE_INTERNATIONAL9);
		stack->setField<int>("SC_LANG1", SDL_SCANCODE_LANG1);
		stack->setField<int>("SC_LANG2", SDL_SCANCODE_LANG2);
		stack->setField<int>("SC_LANG3", SDL_SCANCODE_LANG3);
		stack->setField<int>("SC_LANG4", SDL_SCANCODE_LANG4);
		stack->setField<int>("SC_LANG5", SDL_SCANCODE_LANG5);
		stack->setField<int>("SC_LANG6", SDL_SCANCODE_LANG6);
		stack->setField<int>("SC_LANG7", SDL_SCANCODE_LANG7);
		stack->setField<int>("SC_LANG8", SDL_SCANCODE_LANG8);
		stack->setField<int>("SC_LANG9", SDL_SCANCODE_LANG9);

		stack->setField<int>("SC_ALTERASE", SDL_SCANCODE_ALTERASE);
		stack->setField<int>("SC_SYSREQ", SDL_SCANCODE_SYSREQ);
		stack->setField<int>("SC_CANCEL", SDL_SCANCODE_CANCEL);
		stack->setField<int>("SC_CLEAR", SDL_SCANCODE_CLEAR);
		stack->setField<int>("SC_PRIOR", SDL_SCANCODE_PRIOR);
		stack->setField<int>("SC_RETURN2", SDL_SCANCODE_RETURN2);
		stack->setField<int>("SC_SEPARATOR", SDL_SCANCODE_SEPARATOR);
		stack->setField<int>("SC_OUT", SDL_SCANCODE_OUT);
		stack->setField<int>("SC_OPER", SDL_SCANCODE_OPER);
		stack->setField<int>("SC_CLEARAGAIN", SDL_SCANCODE_CLEARAGAIN);
		stack->setField<int>("SC_CRSEL", SDL_SCANCODE_CRSEL);
		stack->setField<int>("SC_EXSEL", SDL_SCANCODE_EXSEL);

		stack->setField<int>("SC_KP_00", SDL_SCANCODE_KP_00);
		stack->setField<int>("SC_KP_000", SDL_SCANCODE_KP_000);
		stack->setField<int>("SC_THOUSANDSSEPARATOR", SDL_SCANCODE_THOUSANDSSEPARATOR);
		stack->setField<int>("SC_DECIMALSEPARATOR", SDL_SCANCODE_DECIMALSEPARATOR);
		stack->setField<int>("SC_CURRENCYUNIT", SDL_SCANCODE_CURRENCYUNIT);
		stack->setField<int>("SC_CURRENCYSUBUNIT", SDL_SCANCODE_CURRENCYSUBUNIT);
		stack->setField<int>("SC_KP_LEFTPAREN", SDL_SCANCODE_KP_LEFTPAREN);
		stack->setField<int>("SC_KP_RIGHTPAREN", SDL_SCANCODE_KP_RIGHTPAREN);
		stack->setField<int>("SC_KP_LEFTBRACE", SDL_SCANCODE_KP_LEFTBRACE);
		stack->setField<int>("SC_KP_RIGHTBRACE", SDL_SCANCODE_KP_RIGHTBRACE);
		stack->setField<int>("SC_KP_TAB", SDL_SCANCODE_KP_TAB);
		stack->setField<int>("SC_KP_BACKSPACE", SDL_SCANCODE_KP_BACKSPACE);
		stack->setField<int>("SC_KP_A", SDL_SCANCODE_KP_A);
		stack->setField<int>("SC_KP_B", SDL_SCANCODE_KP_B);
		stack->setField<int>("SC_KP_C", SDL_SCANCODE_KP_C);
		stack->setField<int>("SC_KP_D", SDL_SCANCODE_KP_D);
		stack->setField<int>("SC_KP_E", SDL_SCANCODE_KP_E);
		stack->setField<int>("SC_KP_F", SDL_SCANCODE_KP_F);
		stack->setField<int>("SC_KP_XOR", SDL_SCANCODE_KP_XOR);
		stack->setField<int>("SC_KP_POWER", SDL_SCANCODE_KP_POWER);
		stack->setField<int>("SC_KP_PERCENT", SDL_SCANCODE_KP_PERCENT);
		stack->setField<int>("SC_KP_LESS", SDL_SCANCODE_KP_LESS);
		stack->setField<int>("SC_KP_GREATER", SDL_SCANCODE_KP_GREATER);
		stack->setField<int>("SC_KP_AMPERSAND", SDL_SCANCODE_KP_AMPERSAND);
		stack->setField<int>("SC_KP_DBLAMPERSAND", SDL_SCANCODE_KP_DBLAMPERSAND);
		stack->setField<int>("SC_KP_VERTICALBAR", SDL_SCANCODE_KP_VERTICALBAR);
		stack->setField<int>("SC_KP_DBLVERTICALBAR", SDL_SCANCODE_KP_DBLVERTICALBAR);
		stack->setField<int>("SC_KP_COLON", SDL_SCANCODE_KP_COLON);
		stack->setField<int>("SC_KP_HASH", SDL_SCANCODE_KP_HASH);
		stack->setField<int>("SC_KP_SPACE", SDL_SCANCODE_KP_SPACE);
		stack->setField<int>("SC_KP_AT", SDL_SCANCODE_KP_AT);
		stack->setField<int>("SC_KP_EXCLAM", SDL_SCANCODE_KP_EXCLAM);
		stack->setField<int>("SC_KP_MEMSTORE", SDL_SCANCODE_KP_MEMSTORE);
		stack->setField<int>("SC_KP_MEMRECALL", SDL_SCANCODE_KP_MEMRECALL);
		stack->setField<int>("SC_KP_MEMCLEAR", SDL_SCANCODE_KP_MEMCLEAR);
		stack->setField<int>("SC_KP_MEMADD", SDL_SCANCODE_KP_MEMADD);
		stack->setField<int>("SC_KP_MEMSUBTRACT", SDL_SCANCODE_KP_MEMSUBTRACT);
		stack->setField<int>("SC_KP_MEMMULTIPLY", SDL_SCANCODE_KP_MEMMULTIPLY);
		stack->setField<int>("SC_KP_MEMDIVIDE", SDL_SCANCODE_KP_MEMDIVIDE);
		stack->setField<int>("SC_KP_PLUSMINUS", SDL_SCANCODE_KP_PLUSMINUS);
		stack->setField<int>("SC_KP_CLEAR", SDL_SCANCODE_KP_CLEAR);
		stack->setField<int>("SC_KP_CLEARENTRY", SDL_SCANCODE_KP_CLEARENTRY);
		stack->setField<int>("SC_KP_BINARY", SDL_SCANCODE_KP_BINARY);
		stack->setField<int>("SC_KP_OCTAL", SDL_SCANCODE_KP_OCTAL);
		stack->setField<int>("SC_KP_DECIMAL", SDL_SCANCODE_KP_DECIMAL);
		stack->setField<int>("SC_KP_HEXADECIMAL", SDL_SCANCODE_KP_HEXADECIMAL);

		stack->setField<int>("SC_LCTRL", SDL_SCANCODE_LCTRL);
		stack->setField<int>("SC_LSHIFT", SDL_SCANCODE_LSHIFT);
		stack->setField<int>("SC_LALT", SDL_SCANCODE_LALT);
		stack->setField<int>("SC_LGUI", SDL_SCANCODE_LGUI);
		stack->setField<int>("SC_RCTRL", SDL_SCANCODE_RCTRL);
		stack->setField<int>("SC_RSHIFT", SDL_SCANCODE_RSHIFT);
		stack->setField<int>("SC_RALT", SDL_SCANCODE_RALT);
		stack->setField<int>("SC_RGUI", SDL_SCANCODE_RGUI);

		stack->setField<int>("SC_MODE", SDL_SCANCODE_MODE);

		stack->setField<int>("SC_AUDIONEXT", SDL_SCANCODE_AUDIONEXT);
		stack->setField<int>("SC_AUDIOPREV", SDL_SCANCODE_AUDIOPREV);
		stack->setField<int>("SC_AUDIOSTOP", SDL_SCANCODE_AUDIOSTOP);
		stack->setField<int>("SC_AUDIOPLAY", SDL_SCANCODE_AUDIOPLAY);
		stack->setField<int>("SC_AUDIOMUTE", SDL_SCANCODE_AUDIOMUTE);
		stack->setField<int>("SC_MEDIASELECT", SDL_SCANCODE_MEDIASELECT);
		stack->setField<int>("SC_WWW", SDL_SCANCODE_WWW);
		stack->setField<int>("SC_MAIL", SDL_SCANCODE_MAIL);
		stack->setField<int>("SC_CALCULATOR", SDL_SCANCODE_CALCULATOR);
		stack->setField<int>("SC_COMPUTER", SDL_SCANCODE_COMPUTER);
		stack->setField<int>("SC_AC_SEARCH", SDL_SCANCODE_AC_SEARCH);
		stack->setField<int>("SC_AC_HOME", SDL_SCANCODE_AC_HOME);
		stack->setField<int>("SC_AC_BACK", SDL_SCANCODE_AC_BACK);
		stack->setField<int>("SC_AC_FORWARD", SDL_SCANCODE_AC_FORWARD);
		stack->setField<int>("SC_AC_STOP", SDL_SCANCODE_AC_STOP);
		stack->setField<int>("SC_AC_REFRESH", SDL_SCANCODE_AC_REFRESH);
		stack->setField<int>("SC_AC_BOOKMARKS", SDL_SCANCODE_AC_BOOKMARKS);
    
		stack->setField<int>("SC_BRIGHTNESSDOWN", SDL_SCANCODE_BRIGHTNESSDOWN);
		stack->setField<int>("SC_BRIGHTNESSUP", SDL_SCANCODE_BRIGHTNESSUP);
		stack->setField<int>("SC_DISPLAYSWITCH", SDL_SCANCODE_DISPLAYSWITCH);
                                          
		stack->setField<int>("SC_KBDILLUMTOGGLE", SDL_SCANCODE_KBDILLUMTOGGLE);
		stack->setField<int>("SC_KBDILLUMDOWN", SDL_SCANCODE_KBDILLUMDOWN);
		stack->setField<int>("SC_KBDILLUMUP", SDL_SCANCODE_KBDILLUMUP);
		stack->setField<int>("SC_EJECT", SDL_SCANCODE_EJECT);
		stack->setField<int>("SC_SLEEP", SDL_SCANCODE_SLEEP);
    
		stack->setField<int>("SC_APP1", SDL_SCANCODE_APP1);
		stack->setField<int>("SC_APP2", SDL_SCANCODE_APP2);

		//SDL_Keymod
		stack->setField<int>("KMOD_NONE", KMOD_NONE);
		stack->setField<int>("KMOD_LSHIFT", KMOD_LSHIFT);
		stack->setField<int>("KMOD_RSHIFT", KMOD_RSHIFT);
		stack->setField<int>("KMOD_LCTRL", KMOD_LCTRL);
		stack->setField<int>("KMOD_RCTRL", KMOD_RCTRL);
		stack->setField<int>("KMOD_LALT", KMOD_LALT);
		stack->setField<int>("KMOD_RALT", KMOD_RALT);
		stack->setField<int>("KMOD_LGUI", KMOD_LGUI);
		stack->setField<int>("KMOD_RGUI", KMOD_RGUI);
		stack->setField<int>("KMOD_NUM", KMOD_NUM);
		stack->setField<int>("KMOD_CAPS", KMOD_CAPS);
		stack->setField<int>("KMOD_MODE", KMOD_MODE);
		stack->setField<int>("KMOD_RESERVED", KMOD_RESERVED);
		stack->setField<int>("KMOD_CTRL", KMOD_LCTRL|KMOD_RCTRL);
		stack->setField<int>("KMOD_SHIFT", KMOD_LSHIFT|KMOD_RSHIFT);
		stack->setField<int>("KMOD_ALT", KMOD_LALT|KMOD_RALT);
		stack->setField<int>("KMOD_GUI", KMOD_LGUI|KMOD_RGUI);

		//SDL_AudioSpec allowed changes
		stack->setField<int>("AUDIO_ALLOW_FREQUENCY_CHANGE", SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
		stack->setField<int>("AUDIO_ALLOW_FORMAT_CHANGE", SDL_AUDIO_ALLOW_FORMAT_CHANGE);
		stack->setField<int>("AUDIO_ALLOW_CHANNELS_CHANGE", SDL_AUDIO_ALLOW_CHANNELS_CHANGE);
		stack->setField<int>("AUDIO_ALLOW_ANY_CHANGE", SDL_AUDIO_ALLOW_ANY_CHANGE);

		//SDL_AudioFormat
		stack->setField<int>("AUDIO_U8", AUDIO_U8);
		stack->setField<int>("AUDIO_S8", AUDIO_S8);
		stack->setField<int>("AUDIO_U16LSB", AUDIO_U16LSB);
		stack->setField<int>("AUDIO_S16LSB", AUDIO_S16LSB);
		stack->setField<int>("AUDIO_U16MSB", AUDIO_U16MSB);
		stack->setField<int>("AUDIO_S16MSB", AUDIO_S16MSB);
		stack->setField<int>("AUDIO_U16", AUDIO_U16);
		stack->setField<int>("AUDIO_S16", AUDIO_S16);
		stack->setField<int>("AUDIO_S32LSB", AUDIO_S32LSB);
		stack->setField<int>("AUDIO_S32MSB", AUDIO_S32MSB);
		stack->setField<int>("AUDIO_S32", AUDIO_S32);
		stack->setField<int>("AUDIO_F32LSB", AUDIO_F32LSB);
		stack->setField<int>("AUDIO_F32MSB", AUDIO_F32MSB);
		stack->setField<int>("AUDIO_F32", AUDIO_F32);
		stack->setField<int>("AUDIO_U16SYS", AUDIO_U16SYS);
		stack->setField<int>("AUDIO_S16SYS", AUDIO_S16SYS);
		stack->setField<int>("AUDIO_S32SYS", AUDIO_S32SYS);
		stack->setField<int>("AUDIO_F32SYS", AUDIO_F32SYS);

		//SDL_AudioStatus
		stack->setField<int>("AUDIO_STOPPED", SDL_AUDIO_STOPPED);
		stack->setField<int>("AUDIO_PLAYING", SDL_AUDIO_PLAYING);
		stack->setField<int>("AUDIO_PAUSED", SDL_AUDIO_PAUSED);

		//SDL_mixer INIT
		stack->setField<int>("MIX_INIT_FLAC", MIX_INIT_FLAC);
		stack->setField<int>("MIX_INIT_MOD", MIX_INIT_MOD);
		stack->setField<int>("MIX_INIT_MP3", MIX_INIT_MP3);
		stack->setField<int>("MIX_INIT_OGG", MIX_INIT_OGG);
		stack->setField<int>("MIX_INIT_FLUIDSYNTH", MIX_INIT_FLUIDSYNTH);
		stack->setField<int>("MIX_INIT_MODPLUG", MIX_INIT_MODPLUG);

		//SDL_image INIT
		stack->setField<int>("IMG_INIT_JPG", IMG_INIT_JPG);
		stack->setField<int>("IMG_INIT_PNG", IMG_INIT_PNG);
		stack->setField<int>("IMG_INIT_TIF", IMG_INIT_TIF);
		stack->setField<int>("IMG_INIT_WEBP", IMG_INIT_WEBP);

		//SDL_ttf
		stack->setField<int>("TTF_STYLE_BOLD", TTF_STYLE_BOLD);
		stack->setField<int>("TTF_STYLE_ITALIC", TTF_STYLE_ITALIC);
		stack->setField<int>("TTF_STYLE_UNDERLINE", TTF_STYLE_UNDERLINE);
		stack->setField<int>("TTF_STYLE_STRIKETHROUGH", TTF_STYLE_STRIKETHROUGH);
		stack->setField<int>("TTF_STYLE_NORMAL", TTF_STYLE_NORMAL);

		stack->setField<int>("TTF_HINTING_NORMAL", TTF_HINTING_NORMAL);
		stack->setField<int>("TTF_HINTING_LIGHT", TTF_HINTING_LIGHT);
		stack->setField<int>("TTF_HINTING_MONO", TTF_HINTING_MONO);
		stack->setField<int>("TTF_HINTING_NONE", TTF_HINTING_NONE);

		
	}
}