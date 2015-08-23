#ifndef LUA_SDL_OBJECTS_RENDERER_H
#define LUA_SDL_OBJECTS_RENDERER_H

#include "common.hpp"

namespace LuaSDL {

	class Renderer : public Object<SDL_Renderer> {
	public:
		explicit Renderer(State * state) : Object<SDL_Renderer>(state) {
			LUTOK_METHOD("createTexture", &Renderer::createTexture);
			LUTOK_METHOD("createTextureFromSurface", &Renderer::createTextureFromSurface);
			LUTOK_METHOD("renderCopy", &Renderer::renderCopy);
			LUTOK_METHOD("renderCopyEx", &Renderer::renderCopyEx);
			LUTOK_METHOD("readPixels", &Renderer::readPixels);

			LUTOK_METHOD("clear", &Renderer::clear);
			LUTOK_METHOD("drawLine", &Renderer::drawLine);
			LUTOK_METHOD("drawLines", &Renderer::drawLines);
			LUTOK_METHOD("drawPoint", &Renderer::drawPoint);
			LUTOK_METHOD("drawPoints", &Renderer::drawPoints);
			LUTOK_METHOD("drawRect", &Renderer::drawRect);
			LUTOK_METHOD("drawRects", &Renderer::drawRects);
			LUTOK_METHOD("drawFillRect", &Renderer::drawFillRect);
			LUTOK_METHOD("drawFillRects", &Renderer::drawFillRects);
			LUTOK_METHOD("render", &Renderer::renderPresent);

			LUTOK_PROPERTY("drawColor", &Renderer::getRenderDrawColor, &Renderer::setRenderDrawColor);	
			LUTOK_PROPERTY("blendMode", &Renderer::getRenderBlendMode, &Renderer::setRenderBlendMode);	
			LUTOK_PROPERTY("info", &Renderer::getRendererInfo, &Renderer::nullMethod);	
			LUTOK_PROPERTY("clipRect", &Renderer::getClipRect, &Renderer::setClipRect);	
			LUTOK_PROPERTY("viewport", &Renderer::getViewport, &Renderer::setViewport);	
			LUTOK_PROPERTY("renderTarget", &Renderer::nullMethod, &Renderer::setRenderTarget);
		}

		SDL_Renderer * constructor(State & state, bool & managed);

		void destructor(State & state, SDL_Renderer * renderer){
			SDL_DestroyRenderer(renderer);
		}

		int createTexture(State & state, SDL_Renderer * renderer);
		int createTextureFromSurface(State & state, SDL_Renderer * renderer);
		int renderCopy(State & state, SDL_Renderer * renderer);
		int renderCopyEx(State & state, SDL_Renderer * renderer);
		int readPixels(State & state, SDL_Renderer * renderer);
		int setRenderTarget(State & state, SDL_Renderer * renderer);

		int clear(State & state, SDL_Renderer * renderer);
		int renderPresent(State & state, SDL_Renderer * renderer);
		int drawLine(State & state, SDL_Renderer * renderer);
		int drawLines(State & state, SDL_Renderer * renderer);
		int drawPoint(State & state, SDL_Renderer * renderer);
		int drawPoints(State & state, SDL_Renderer * renderer);

		int drawRect(State & state, SDL_Renderer * renderer);
		int drawRects(State & state, SDL_Renderer * renderer);
		int drawFillRect(State & state, SDL_Renderer * renderer);
		int drawFillRects(State & state, SDL_Renderer * renderer);
		
		int getRenderDrawColor(State & state, SDL_Renderer * renderer);
		int setRenderDrawColor(State & state, SDL_Renderer * renderer);

		int getRenderBlendMode(State & state, SDL_Renderer * renderer);
		int setRenderBlendMode(State & state, SDL_Renderer * renderer);
		int getRendererInfo(State & state, SDL_Renderer * renderer);

		int getClipRect(State & state, SDL_Renderer * renderer);
		int setClipRect(State & state, SDL_Renderer * renderer);
		int getViewport(State & state, SDL_Renderer * renderer);
		int setViewport(State & state, SDL_Renderer * renderer);

	};
}

#endif
