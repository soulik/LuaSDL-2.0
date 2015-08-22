#ifndef LUA_SDL_OBJECTS_FONT_H
#define LUA_SDL_OBJECTS_FONT_H

#include "common.hpp"

namespace LuaSDL {

	class TTFFont : public Object<TTF_Font> {
	public:
		explicit TTFFont(State * state) : Object<TTF_Font>(state) {
			LUTOK_METHOD("glyphProvided", &TTFFont::isGlyphProvided);
			LUTOK_METHOD("glyphMetrics", &TTFFont::getGlyphMetrics);
			LUTOK_METHOD("sizeText", &TTFFont::getTextSize);
			LUTOK_METHOD("sizeTextUTF8", &TTFFont::getTextSizeUTF8);
			LUTOK_METHOD("sizeTextUNICODE", &TTFFont::getTextSizeUNICODE);

			//Solid
			LUTOK_METHOD("renderSolid", &TTFFont::renderSolid);
			LUTOK_METHOD("renderSolidUTF8", &TTFFont::renderSolidUTF8);
			LUTOK_METHOD("renderSolidUNICODE", &TTFFont::renderSolidUNICODE);
			LUTOK_METHOD("renderSolidGlyph", &TTFFont::renderSolidGlyph);
			
			//Shaded
			LUTOK_METHOD("renderShaded", &TTFFont::renderShaded);
			LUTOK_METHOD("renderShadedUTF8", &TTFFont::renderShadedUTF8);
			LUTOK_METHOD("renderShadedUNICODE", &TTFFont::renderShadedUNICODE);
			LUTOK_METHOD("renderShadedGlyph", &TTFFont::renderShadedGlyph);

			//Blended
			LUTOK_METHOD("renderBlended", &TTFFont::renderBlended);
			LUTOK_METHOD("renderBlendedUTF8", &TTFFont::renderBlendedUTF8);
			LUTOK_METHOD("renderBlendedUNICODE", &TTFFont::renderBlendedUNICODE);
			LUTOK_METHOD("renderBlendedGlyph", &TTFFont::renderBlendedGlyph);

			LUTOK_PROPERTY("style", &TTFFont::getFontStyle, &TTFFont::setFontStyle);	
			LUTOK_PROPERTY("outline", &TTFFont::getFontOutline, &TTFFont::setFontOutline);	
			LUTOK_PROPERTY("hinting", &TTFFont::getFontHinting, &TTFFont::setFontHinting);	
			LUTOK_PROPERTY("kerning", &TTFFont::getFontKerning, &TTFFont::setFontKerning);	

			LUTOK_PROPERTY("height", &TTFFont::getFontHeight, &TTFFont::nullMethod);	
			LUTOK_PROPERTY("ascent", &TTFFont::getFontAscent, &TTFFont::nullMethod);	
			LUTOK_PROPERTY("descent", &TTFFont::getFontDescent, &TTFFont::nullMethod);	
			LUTOK_PROPERTY("lineSkip", &TTFFont::getFontLineSkip, &TTFFont::nullMethod);	
			LUTOK_PROPERTY("faces", &TTFFont::getFontFaces, &TTFFont::nullMethod);	
			LUTOK_PROPERTY("fixedWidth", &TTFFont::getFontFixedWidth, &TTFFont::nullMethod);	

			LUTOK_PROPERTY("familyName", &TTFFont::getFontFamilyName, &TTFFont::nullMethod);	
			LUTOK_PROPERTY("styleName", &TTFFont::getFontStyleName, &TTFFont::nullMethod);	
		}

		TTF_Font * constructor(State & state, bool & managed);

		void destructor(State & state, TTF_Font * font){
			TTF_CloseFont(font);
		}

		int isGlyphProvided(State & state, TTF_Font * font);
		int getGlyphMetrics(State & state, TTF_Font * font);
		int getTextSize(State & state, TTF_Font * font);
		int getTextSizeUTF8(State & state, TTF_Font * font);
		int getTextSizeUNICODE(State & state, TTF_Font * font);

		int renderSolid(State & state, TTF_Font * font);
		int renderSolidUTF8(State & state, TTF_Font * font);
		int renderSolidUNICODE(State & state, TTF_Font * font);
		int renderSolidGlyph(State & state, TTF_Font * font);
		int renderShaded(State & state, TTF_Font * font);
		int renderShadedUTF8(State & state, TTF_Font * font);
		int renderShadedUNICODE(State & state, TTF_Font * font);
		int renderShadedGlyph(State & state, TTF_Font * font);
		int renderBlended(State & state, TTF_Font * font);
		int renderBlendedUTF8(State & state, TTF_Font * font);
		int renderBlendedUNICODE(State & state, TTF_Font * font);
		int renderBlendedGlyph(State & state, TTF_Font * font);

		int getFontStyle(State & state, TTF_Font * font);
		int setFontStyle(State & state, TTF_Font * font);
		int getFontOutline(State & state, TTF_Font * font);
		int setFontOutline(State & state, TTF_Font * font);
		int getFontHinting(State & state, TTF_Font * font);
		int setFontHinting(State & state, TTF_Font * font);
		int getFontKerning(State & state, TTF_Font * font);
		int setFontKerning(State & state, TTF_Font * font);

		int getFontHeight(State & state, TTF_Font * font);
		int getFontAscent(State & state, TTF_Font * font);
		int getFontDescent(State & state, TTF_Font * font);
		int getFontLineSkip(State & state, TTF_Font * font);
		int getFontFaces(State & state, TTF_Font * font);
		int getFontFixedWidth(State & state, TTF_Font * font);
		int getFontFamilyName(State & state, TTF_Font * font);
		int getFontStyleName(State & state, TTF_Font * font);

	};
}

#endif
