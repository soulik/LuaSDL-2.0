#include "common.hpp"

using namespace LuaSDL;
extern "C" LIBLUASDL2_DLL_EXPORTED int luaopen_LuaSDL2(lua_State * L){
	State * state = new State(L);
	Stack * stack = state->stack;

    Module module;
	stack->newTable();

    initBasic(module);
	initVideo(module);
	initInput(module);
	initTimers(module);
	initAudio(module);
	initPower(module);
	initPlatform(module);
	
	//objects
	initGLContext(state, module);
	initRect(state, module);
	initDisplayMode(state, module);
	initSurface(state, module);
	initWindow(state, module);
	initPixelFormat(state, module);
	initEvent(state, module);
	initCursor(state, module);
	initJoystick(state, module);
	initGameController(state, module);
	initTimer(state, module);
	initAudioDevice(state, module);
	initAudioSpec(state, module);
	initAudioBuffer(state, module);
	initThread(state, module);

	//SDL Mixer
	initSDLmixer(module);
	initMixChunk(state, module);
	initMixMusic(state, module);

	//SDL Image
	initSDLimage(module);

	//SDL TTF
	initSDLttf(module);
	initTTFFont(state, module);

	//SDL iconv
	initIconv(state, module);

	state->registerLib(module);
	initConstants(*state);
	SDL_SetMainReady();
	return 1;
 }
