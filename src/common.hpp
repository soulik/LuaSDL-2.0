#ifndef LUA_SDL_COMMON_H
#define LUA_SDL_COMMON_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <string>

#include <lutok2/lutok2.hpp>

#include "utils.hpp"

/* libSDL 2.0 */
#include <SDL.h>
#include <SDL_main.h>

/* SDL Mixer 2.0 */
#include <SDL_mixer.h>
/* SDL Image 2.0 */
#include <SDL_image.h>
/* SDL TTF 2.0 */
#include <SDL_ttf.h>

using namespace lutok2;

#if (BUILDING_LIBLUASDL2 || LUASDL2_EXPORTS) && HAVE_VISIBILITY
#define LIBLUASDL2_DLL_EXPORTED __attribute__((visibility("default")))
#elif (BUILDING_LIBLUASDL2 || LUASDL2_EXPORTS) && defined _MSC_VER
#define LIBLUASDL2_DLL_EXPORTED __declspec(dllexport)
#elif defined _MSC_VER
#define LIBLUASDL2_DLL_EXPORTED __declspec(dllimport)
#else
#define LIBLUASDL2_DLL_EXPORTED
#endif


#define getObject(n) *(static_cast<void**>(stack->to<void*>((n))))
#define INIT_OBJECT(OBJ_NAME) state->registerInterface<OBJ_NAME>("LuaSDL_" #OBJ_NAME); state->stack->setField(#OBJ_NAME)

namespace LuaSDL{
	void initBasic(Module & module);
	void initVideo(Module & module);
	void initInput(Module & module);
	void initTimers(Module & module);
	void initAudio(Module & module);
	void initConstants(State &);
	void initPower(Module & module);
	void initPlatform(Module & module);

	//objects
	void initWindow(State *, Module &);
	void initGLContext(State *, Module &);
	void initDisplayMode(State *, Module &);
	void initRect(State *, Module &);
	void initSurface(State *, Module &);
	void initPixelFormat(State *, Module &);
	void initEvent(State *, Module &);
	void initInput(State *, Module &);
	void initCursor(State *, Module &);
	void initJoystick(State *, Module &);
	void initGameController(State *, Module &);
	void initTimer(State *, Module &);
	void initAudioDevice(State *, Module &);
	void initAudioSpec(State *, Module &);
	void initAudioBuffer(State *, Module &);
	void initThread(State *, Module &);
	void initRenderer(State *, Module &);
	void initTexture(State *, Module &);
	void initHaptic(State * state, Module & module);
	void initHapticEffect(State * state, Module & module);

	//SDL_mixer
	void initSDLmixer(Module & module);
	void initMixChunk(State *, Module &);
	void initMixMusic(State *, Module &);

	//SDL_image
	void initSDLimage(Module & module);

	//SDL_ttf
	void initSDLttf(Module & module);
	void initTTFFont(State *, Module &);

	//SDL iconv
	void initIconv(State *, Module &);

}

#endif