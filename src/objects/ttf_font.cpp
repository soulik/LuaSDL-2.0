#include "objects/surface.hpp"
#include "objects/ttf_font.hpp"
#include <lua.hpp>
namespace LuaSDL {

	void fillColor(State & state, int index, SDL_Color & color){
		Stack * stack = state.stack;
		int clen = stack->objLen(index);
		if (clen >= 3){
			stack->rawGet(1, index);
			color.r = static_cast<Uint8>(stack->to<int>());
			stack->rawGet(2, index);
			color.g = static_cast<Uint8>(stack->to<int>());
			stack->rawGet(3, index);
			color.b = static_cast<Uint8>(stack->to<int>());
			if (clen>3){
				stack->rawGet(4, index);
				color.a = static_cast<Uint8>(stack->to<int>());
				stack->pop(4);
			}else{
				stack->pop(3);
			}
		}else{
			color.r = 0;
			color.g = 0;
			color.b = 0;
			color.a = 255;
		}
	}

	int TTFFont::isGlyphProvided(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			Uint16 glyph = static_cast<Uint16>(stack->to<int>(1));
			int result = TTF_GlyphIsProvided(font, glyph);
			stack->push<int>(result);
			return 1;
		}
		return 0;
	}
	int TTFFont::getGlyphMetrics(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TNUMBER>(1)){
			Uint16 glyph = static_cast<Uint16>(stack->to<int>(1));
			int minx = 0;
			int maxx = 0;
			int miny = 0;
			int maxy = 0;
			int advance = 0;

			int result = TTF_GlyphMetrics(font, glyph, &minx, &maxx, &miny, &maxy, &advance);
			if (result == 0){
				stack->push<int>(minx);
				stack->push<int>(maxx);
				stack->push<int>(miny);
				stack->push<int>(maxy);
				stack->push<int>(advance);
				return 5;
			}
			else{
				stack->push<bool>(false);
				return 1;
			}
		}
		return 0;
	}
	int TTFFont::getTextSize(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			int w = 0;
			int h = 0;
			const std::string text = stack->to<const std::string>(1);
			int result = TTF_SizeText(font, text.c_str(), &w, &h);
			if (result == 0){
				stack->push<int>(w);
				stack->push<int>(h);
				return 2;
			}
			else{
				stack->push<bool>(false);
				return 1;
			}
		}
		return 0;
	}
	int TTFFont::getTextSizeUTF8(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			int w = 0;
			int h = 0;

			const std::string text = stack->to<const std::string>(1);
			int result = TTF_SizeUTF8(font, text.c_str(), &w, &h);
			if (result == 0){
				stack->push<int>(w);
				stack->push<int>(h);
				return 2;
			}
			else{
				stack->push<bool>(false);
				return 1;
			}
		}
		return 0;
	}
	int TTFFont::getTextSizeUNICODE(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1)){
			int w = 0;
			int h = 0;

			const std::string text = stack->to<const std::string>(1);
			int result = TTF_SizeUNICODE(font, reinterpret_cast<const Uint16*>(text.c_str()), &w, &h);
			if (result == 0){
				stack->push<int>(w);
				stack->push<int>(h);
				return 2;
			}
			else{
				stack->push<bool>(false);
				return 1;
			}
		}
		return 0;
	}
	int TTFFont::renderSolid(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TTABLE>(2)){
			SDL_Color color;
			LuaSDL::fillColor(state, 2, color);
			const std::string text = stack->to<const std::string>(1);
			SDL_Surface * surface = TTF_RenderText_Solid(font, text.c_str(), color);
			if (surface){
				interfaceSurface->push(surface, true);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}
	int TTFFont::renderSolidUTF8(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TTABLE>(2)){
			SDL_Color color;
			LuaSDL::fillColor(state, 2, color);
			const std::string text = stack->to<const std::string>(1);
			SDL_Surface * surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
			if (surface){
				interfaceSurface->push(surface, true);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}
	int TTFFont::renderSolidUNICODE(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TTABLE>(2)){
			SDL_Color color;
			LuaSDL::fillColor(state, 2, color);
			const std::string text = stack->to<const std::string>(1);
			SDL_Surface * surface = TTF_RenderUNICODE_Solid(font, reinterpret_cast<const Uint16*>(text.c_str()), color);
			if (surface){
				interfaceSurface->push(surface, true);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}
	int TTFFont::renderSolidGlyph(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TTABLE>(2)){
			SDL_Color color;
			LuaSDL::fillColor(state, 2, color);
			SDL_Surface * surface = TTF_RenderGlyph_Solid(font, static_cast<Uint16>(stack->to<int>(1)), color);
			if (surface){
				interfaceSurface->push(surface, true);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}

	int TTFFont::renderShaded(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TTABLE>(2) && stack->is<LUA_TTABLE>(3)){
			SDL_Color fg;
			SDL_Color bg;

			LuaSDL::fillColor(state, 2, fg);
			LuaSDL::fillColor(state, 3, bg);
			const std::string text = stack->to<const std::string>(1);
			SDL_Surface * surface = TTF_RenderText_Shaded(font, text.c_str(), fg, bg);
			if (surface){
				interfaceSurface->push(surface, true);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}
	int TTFFont::renderShadedUTF8(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TTABLE>(2) && stack->is<LUA_TTABLE>(3)){
			SDL_Color fg;
			SDL_Color bg;

			LuaSDL::fillColor(state, 2, fg);
			LuaSDL::fillColor(state, 3, bg);
			const std::string text = stack->to<const std::string>(1);
			SDL_Surface * surface = TTF_RenderUTF8_Shaded(font, text.c_str(), fg, bg);
			if (surface){
				interfaceSurface->push(surface, true);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}
	int TTFFont::renderShadedUNICODE(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TTABLE>(2) && stack->is<LUA_TTABLE>(3)){
			SDL_Color fg;
			SDL_Color bg;

			LuaSDL::fillColor(state, 2, fg);
			LuaSDL::fillColor(state, 3, bg);
			const std::string text = stack->to<const std::string>(1);
			SDL_Surface * surface = TTF_RenderUNICODE_Shaded(font, reinterpret_cast<const Uint16*>(text.c_str()), fg, bg);
			if (surface){
				interfaceSurface->push(surface, true);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}
	int TTFFont::renderShadedGlyph(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TTABLE>(2) && stack->is<LUA_TTABLE>(3)){
			SDL_Color fg;
			SDL_Color bg;

			LuaSDL::fillColor(state, 2, fg);
			LuaSDL::fillColor(state, 3, bg);

			SDL_Surface * surface = TTF_RenderGlyph_Shaded(font, static_cast<Uint16>(stack->to<int>(1)), fg, bg);
			if (surface){
				interfaceSurface->push(surface, true);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}

	int TTFFont::renderBlended(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TTABLE>(2)){
			SDL_Color color;
			LuaSDL::fillColor(state, 2, color);
			const std::string text = stack->to<const std::string>(1);
			SDL_Surface * surface = TTF_RenderText_Blended(font, text.c_str(), color);
			if (surface){
				interfaceSurface->push(surface, true);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}
	int TTFFont::renderBlendedUTF8(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TTABLE>(2)){
			SDL_Color color;
			LuaSDL::fillColor(state, 2, color);
			const std::string text = stack->to<const std::string>(1);
			SDL_Surface * surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
			if (surface){
				interfaceSurface->push(surface, true);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}
	int TTFFont::renderBlendedUNICODE(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TTABLE>(2)){
			SDL_Color color;
			LuaSDL::fillColor(state, 2, color);
			const std::string text = stack->to<const std::string>(1);
			SDL_Surface * surface = TTF_RenderUNICODE_Blended(font, reinterpret_cast<const Uint16*>(text.c_str()), color);
			if (surface){
				interfaceSurface->push(surface, true);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}
	int TTFFont::renderBlendedGlyph(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		Surface * interfaceSurface = state.getInterface<Surface>("LuaSDL_Surface");
		if (stack->is<LUA_TNUMBER>(1) && stack->is<LUA_TTABLE>(2)){
			SDL_Color color;
			LuaSDL::fillColor(state, 2, color);
			SDL_Surface * surface = TTF_RenderGlyph_Blended(font, static_cast<Uint16>(stack->to<int>(1)), color);
			if (surface){
				interfaceSurface->push(surface, true);
			}
			else{
				stack->push<bool>(false);
			}
			return 1;
		}
		return 0;
	}

	int TTFFont::getFontStyle(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int result = TTF_GetFontStyle(font);
		stack->push<int>(result);
		return 1;
	}
	int TTFFont::setFontStyle(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int style = TTF_STYLE_NORMAL;
		if (stack->is<LUA_TNUMBER>(1)){
			style = stack->to<int>(1);
		}
		TTF_SetFontStyle(font, style);
		return 0;
	}
	int TTFFont::getFontOutline(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int result = TTF_GetFontOutline(font);
		stack->push<int>(result);
		return 1;
	}
	int TTFFont::setFontOutline(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int style = 0;
		if (stack->is<LUA_TNUMBER>(1)){
			style = stack->to<int>(1);
		}
		TTF_SetFontOutline(font, style);
		return 0;
	}
	int TTFFont::getFontHinting(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int result = TTF_GetFontHinting(font);
		stack->push<int>(result);
		return 1;
	}
	int TTFFont::setFontHinting(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int style = TTF_HINTING_NORMAL;
		if (stack->is<LUA_TNUMBER>(1)){
			style = stack->to<int>(1);
		}
		TTF_SetFontHinting(font, style);
		return 0;
	}
	int TTFFont::getFontKerning(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int result = TTF_GetFontKerning(font);
		stack->push<int>(result);
		return 1;
	}
	int TTFFont::setFontKerning(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int style = 1;
		if (stack->is<LUA_TNUMBER>(1)){
			style = stack->to<int>(1);
		}
		TTF_SetFontKerning(font, style);
		return 0;
	}

	int TTFFont::getFontHeight(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int result = TTF_FontHeight(font);
		stack->push<int>(result);
		return 1;
	}
	int TTFFont::getFontAscent(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int result = TTF_FontAscent(font);
		stack->push<int>(result);
		return 1;
	}
	int TTFFont::getFontDescent(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int result = TTF_FontDescent(font);
		stack->push<int>(result);
		return 1;
	}
	int TTFFont::getFontLineSkip(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int result = TTF_FontLineSkip(font);
		stack->push<int>(result);
		return 1;
	}
	int TTFFont::getFontFaces(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int result = TTF_FontFaces(font);
		stack->push<int>(result);
		return 1;
	}
	int TTFFont::getFontFixedWidth(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		int result = TTF_FontFaceIsFixedWidth(font);
		stack->push<bool>(result > 0);
		return 1;
	}
	int TTFFont::getFontFamilyName(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		char * name = TTF_FontFaceFamilyName(font);
		if (name){
			stack->push<const std::string &>(name);
		}
		else{
			stack->push<const std::string &>("");
		}
		return 1;
	}
	int TTFFont::getFontStyleName(State & state, TTF_Font * font) {
		Stack * stack = state.stack;
		char * name = TTF_FontFaceStyleName(font);
		if (name){
			stack->push<const std::string &>(name);
		}
		else{
			stack->push<const std::string &>("");
		}
		return 1;
	}

	TTF_Font * TTFFont::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		if (stack->is<LUA_TSTRING>(1) && stack->is<LUA_TNUMBER>(2)){
			const std::string fileName = stack->to<const std::string>(1);
			int ptSize = stack->to<int>(2);

			TTF_Font * font = nullptr;

			if (stack->is<LUA_TNUMBER>(3)){
				font = TTF_OpenFontIndex(fileName.c_str(), ptSize, stack->to<int>(3));
			}
			else{
				font = TTF_OpenFont(fileName.c_str(), ptSize);
			}
			return font;
		}
		return nullptr;
	}

	void initTTFFont(State * state, Module & module){
		INIT_OBJECT(TTFFont);
		//module["mixerLoadMUS"] = lua_Mix_LoadMUS;
	}

}
