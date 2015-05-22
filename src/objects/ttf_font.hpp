#ifndef LUA_SDL_OBJECTS_FONT_H
#define LUA_SDL_OBJECTS_FONT_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_TTF_Font : public LObject<Lua_SDL_TTF_Font, TTF_Font  *> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_TTF_Font, TTF_Font *, "Font") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "glyphProvided", isGlyphProvided);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "glyphMetrics", getGlyphMetrics);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "sizeText", getTextSize);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "sizeTextUTF8", getTextSizeUTF8);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "sizeTextUNICODE", getTextSizeUNICODE);

			//Solid
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "renderSolid", renderSolid);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "renderSolidUTF8", renderSolidUTF8);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "renderSolidUNICODE", renderSolidUNICODE);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "renderSolidGlyph", renderSolidGlyph);
			
			//Shaded
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "renderShaded", renderShaded);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "renderShadedUTF8", renderShadedUTF8);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "renderShadedUNICODE", renderShadedUNICODE);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "renderShadedGlyph", renderShadedGlyph);

			//Blended
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "renderBlended", renderBlended);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "renderBlendedUTF8", renderBlendedUTF8);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "renderBlendedUNICODE", renderBlendedUNICODE);
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_TTF_Font, "renderBlendedGlyph", renderBlendedGlyph);

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_TTF_Font, TTF_Font *, "style", getFontStyle, setFontStyle);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_TTF_Font, TTF_Font *, "outline", getFontOutline, setFontOutline);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_TTF_Font, TTF_Font *, "hinting", getFontHinting, setFontHinting);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_TTF_Font, TTF_Font *, "kerning", getFontKerning, setFontKerning);	

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_TTF_Font, TTF_Font *, "height", getFontHeight, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_TTF_Font, TTF_Font *, "ascent", getFontAscent, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_TTF_Font, TTF_Font *, "descent", getFontDescent, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_TTF_Font, TTF_Font *, "lineSkip", getFontLineSkip, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_TTF_Font, TTF_Font *, "faces", getFontFaces, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_TTF_Font, TTF_Font *, "fixedWidth", getFontFixedWidth, null_method);	

			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_TTF_Font, TTF_Font *, "familyName", getFontFamilyName, null_method);	
			LOBJECT_ADD_PROPERTY(LuaSDL::Lua_SDL_TTF_Font, TTF_Font *, "styleName", getFontStyleName, null_method);	
		}

		void destructor(lutok::state & s, TTF_Font * font){
			TTF_CloseFont(font);
		}

		int LOBJECT_METHOD(isGlyphProvided, TTF_Font * font){
			if (state.is_number(1)){
				Uint16 glyph = static_cast<Uint16>(state.to_integer(1));
				int result = TTF_GlyphIsProvided(font, glyph);
				state.push_integer(result);
				return 1;
			}
			return 0;
		}
		int LOBJECT_METHOD(getGlyphMetrics, TTF_Font * font){
			if (state.is_number(1)){
				Uint16 glyph = static_cast<Uint16>(state.to_integer(1));
				int minx = 0;
				int maxx = 0;
				int miny = 0;
				int maxy = 0;
				int advance = 0;

				int result = TTF_GlyphMetrics(font, glyph, &minx, &maxx, &miny, &maxy, &advance);
				if (result == 0){
					state.push_integer(minx);
					state.push_integer(maxx);
					state.push_integer(miny);
					state.push_integer(maxy);
					state.push_integer(advance);
					return 5;
				}else{
					state.push_boolean(false);
					return 1;
				}
			}
			return 0;
		}
		int LOBJECT_METHOD(getTextSize, TTF_Font * font){
			if (state.is_string(1)){
				int w = 0;
				int h = 0;

				int result = TTF_SizeText(font, state.to_string(1).c_str(), &w, &h);
				if (result == 0){
					state.push_integer(w);
					state.push_integer(h);
					return 2;
				}else{
					state.push_boolean(false);
					return 1;
				}
			}
			return 0;
		}
		int LOBJECT_METHOD(getTextSizeUTF8, TTF_Font * font){
			if (state.is_string(1)){
				int w = 0;
				int h = 0;

				int result = TTF_SizeUTF8(font, state.to_string(1).c_str(), &w, &h);
				if (result == 0){
					state.push_integer(w);
					state.push_integer(h);
					return 2;
				}else{
					state.push_boolean(false);
					return 1;
				}
			}
			return 0;
		}
		int LOBJECT_METHOD(getTextSizeUNICODE, TTF_Font * font){
			if (state.is_string(1)){
				int w = 0;
				int h = 0;

				int result = TTF_SizeUNICODE(font, reinterpret_cast<const Uint16*>(state.to_string(1).c_str()), &w, &h);
				if (result == 0){
					state.push_integer(w);
					state.push_integer(h);
					return 2;
				}else{
					state.push_boolean(false);
					return 1;
				}
			}
			return 0;
		}

		int LOBJECT_METHOD(renderSolid, TTF_Font * font);
		int LOBJECT_METHOD(renderSolidUTF8, TTF_Font * font);
		int LOBJECT_METHOD(renderSolidUNICODE, TTF_Font * font);
		int LOBJECT_METHOD(renderSolidGlyph, TTF_Font * font);
		int LOBJECT_METHOD(renderShaded, TTF_Font * font);
		int LOBJECT_METHOD(renderShadedUTF8, TTF_Font * font);
		int LOBJECT_METHOD(renderShadedUNICODE, TTF_Font * font);
		int LOBJECT_METHOD(renderShadedGlyph, TTF_Font * font);
		int LOBJECT_METHOD(renderBlended, TTF_Font * font);
		int LOBJECT_METHOD(renderBlendedUTF8, TTF_Font * font);
		int LOBJECT_METHOD(renderBlendedUNICODE, TTF_Font * font);
		int LOBJECT_METHOD(renderBlendedGlyph, TTF_Font * font);

		int LOBJECT_METHOD(getFontStyle, TTF_Font * font){
			int result = TTF_GetFontStyle(font);
			state.push_integer(result);
			return 1;
		}
		int LOBJECT_METHOD(setFontStyle, TTF_Font * font){
			int style = TTF_STYLE_NORMAL;
			if (state.is_number(1)){
				style = state.to_integer(1);
			}
			TTF_SetFontStyle(font, style);
			return 0;
		}
		int LOBJECT_METHOD(getFontOutline, TTF_Font * font){
			int result = TTF_GetFontOutline(font);
			state.push_integer(result);
			return 1;
		}
		int LOBJECT_METHOD(setFontOutline, TTF_Font * font){
			int style = 0;
			if (state.is_number(1)){
				style = state.to_integer(1);
			}
			TTF_SetFontOutline(font, style);
			return 0;
		}
		int LOBJECT_METHOD(getFontHinting, TTF_Font * font){
			int result = TTF_GetFontHinting(font);
			state.push_integer(result);
			return 1;
		}
		int LOBJECT_METHOD(setFontHinting, TTF_Font * font){
			int style = TTF_HINTING_NORMAL;
			if (state.is_number(1)){
				style = state.to_integer(1);
			}
			TTF_SetFontHinting(font, style);
			return 0;
		}
		int LOBJECT_METHOD(getFontKerning, TTF_Font * font){
			int result = TTF_GetFontKerning(font);
			state.push_integer(result);
			return 1;
		}
		int LOBJECT_METHOD(setFontKerning, TTF_Font * font){
			int style = 1;
			if (state.is_number(1)){
				style = state.to_integer(1);
			}
			TTF_SetFontKerning(font, style);
			return 0;
		}

		int LOBJECT_METHOD(getFontHeight, TTF_Font * font){
			int result = TTF_FontHeight(font);
			state.push_integer(result);
			return 1;
		}
		int LOBJECT_METHOD(getFontAscent, TTF_Font * font){
			int result = TTF_FontAscent(font);
			state.push_integer(result);
			return 1;
		}
		int LOBJECT_METHOD(getFontDescent, TTF_Font * font){
			int result = TTF_FontDescent(font);
			state.push_integer(result);
			return 1;
		}
		int LOBJECT_METHOD(getFontLineSkip, TTF_Font * font){
			int result = TTF_FontLineSkip(font);
			state.push_integer(result);
			return 1;
		}
		int LOBJECT_METHOD(getFontFaces, TTF_Font * font){
			int result = TTF_FontFaces(font);
			state.push_integer(result);
			return 1;
		}
		int LOBJECT_METHOD(getFontFixedWidth, TTF_Font * font){
			int result = TTF_FontFaceIsFixedWidth(font);
			state.push_boolean(result > 0);
			return 1;
		}
		int LOBJECT_METHOD(getFontFamilyName, TTF_Font * font){
			char * name = TTF_FontFaceFamilyName(font);
			if (name){
				state.push_string(name);
			}else{
				state.push_literal("");
			}
			return 1;
		}
		int LOBJECT_METHOD(getFontStyleName, TTF_Font * font){
			char * name = TTF_FontFaceStyleName(font);
			if (name){
				state.push_string(name);
			}else{
				state.push_literal("");
			}
			return 1;
		}

	};
}

#endif
