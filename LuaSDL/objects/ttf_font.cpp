#include "objects/surface.hpp"
#include "objects/ttf_font.hpp"
#include <lua.hpp>
namespace LuaSDL {

	void fillColor(lutok::state & state, int index, SDL_Color & color){
		int clen = state.obj_len(index);
		if (clen >= 3){
			state.raw_geti(index,1);
			color.r = static_cast<Uint8>(state.to_integer());
			state.raw_geti(index,2);
			color.g = static_cast<Uint8>(state.to_integer());
			state.raw_geti(index,3);
			color.b = static_cast<Uint8>(state.to_integer());
			if (clen>3){
				state.raw_geti(index,4);
				color.a = static_cast<Uint8>(state.to_integer());
				state.pop(4);
			}else{
				state.pop(3);
			}
		}else{
			color.r = 0;
			color.g = 0;
			color.b = 0;
			color.a = 255;
		}
	}

}

int LuaSDL::Lua_SDL_TTF_Font::LOBJECT_METHOD(renderSolid, TTF_Font * font){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	if (state.is_string(1) && state.is_table(2)){
		SDL_Color color;
		LuaSDL::fillColor(state, 2, color);
		SDL_Surface * surface = TTF_RenderText_Solid(font, state.to_string(1).c_str(), color);
		if (surface){
			s.push(surface);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_TTF_Font::LOBJECT_METHOD(renderSolidUTF8, TTF_Font * font){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	if (state.is_string(1) && state.is_table(2)){
		SDL_Color color;
		LuaSDL::fillColor(state, 2, color);
		SDL_Surface * surface = TTF_RenderUTF8_Solid(font, state.to_string(1).c_str(), color);
		if (surface){
			s.push(surface);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_TTF_Font::LOBJECT_METHOD(renderSolidUNICODE, TTF_Font * font){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	if (state.is_string(1) && state.is_table(2)){
		SDL_Color color;
		LuaSDL::fillColor(state, 2, color);
		SDL_Surface * surface = TTF_RenderUNICODE_Solid(font, reinterpret_cast<const Uint16*>(state.to_string(1).c_str()), color);
		if (surface){
			s.push(surface);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_TTF_Font::LOBJECT_METHOD(renderSolidGlyph, TTF_Font * font){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	if (state.is_number(1) && state.is_table(2)){
		SDL_Color color;
		LuaSDL::fillColor(state, 2, color);
		SDL_Surface * surface = TTF_RenderGlyph_Solid(font, static_cast<Uint16>(state.to_integer(1)), color);
		if (surface){
			s.push(surface);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	return 0;
}

int LuaSDL::Lua_SDL_TTF_Font::LOBJECT_METHOD(renderShaded, TTF_Font * font){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	if (state.is_string(1) && state.is_table(2) && state.is_table(3)){
		SDL_Color fg;
		SDL_Color bg;

		LuaSDL::fillColor(state, 2, fg);
		LuaSDL::fillColor(state, 3, bg);
		SDL_Surface * surface = TTF_RenderText_Shaded(font, state.to_string(1).c_str(), fg, bg);
		if (surface){
			s.push(surface);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_TTF_Font::LOBJECT_METHOD(renderShadedUTF8, TTF_Font * font){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	if (state.is_string(1) && state.is_table(2) && state.is_table(3)){
		SDL_Color fg;
		SDL_Color bg;

		LuaSDL::fillColor(state, 2, fg);
		LuaSDL::fillColor(state, 3, bg);

		SDL_Surface * surface = TTF_RenderUTF8_Shaded(font, state.to_string(1).c_str(), fg, bg);
		if (surface){
			s.push(surface);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_TTF_Font::LOBJECT_METHOD(renderShadedUNICODE, TTF_Font * font){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	if (state.is_string(1) && state.is_table(2) && state.is_table(3)){
		SDL_Color fg;
		SDL_Color bg;

		LuaSDL::fillColor(state, 2, fg);
		LuaSDL::fillColor(state, 3, bg);
		SDL_Surface * surface = TTF_RenderUNICODE_Shaded(font, reinterpret_cast<const Uint16*>(state.to_string(1).c_str()),  fg, bg);
		if (surface){
			s.push(surface);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_TTF_Font::LOBJECT_METHOD(renderShadedGlyph, TTF_Font * font){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	if (state.is_number(1) && state.is_table(2) && state.is_table(3)){
		SDL_Color fg;
		SDL_Color bg;

		LuaSDL::fillColor(state, 2, fg);
		LuaSDL::fillColor(state, 3, bg);

		SDL_Surface * surface = TTF_RenderGlyph_Shaded(font, static_cast<Uint16>(state.to_integer(1)),  fg, bg);
		if (surface){
			s.push(surface);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	return 0;
}

int LuaSDL::Lua_SDL_TTF_Font::LOBJECT_METHOD(renderBlended, TTF_Font * font){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	if (state.is_string(1) && state.is_table(2)){
		SDL_Color color;
		LuaSDL::fillColor(state, 2, color);
		SDL_Surface * surface = TTF_RenderText_Blended(font, state.to_string(1).c_str(), color);
		if (surface){
			s.push(surface);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_TTF_Font::LOBJECT_METHOD(renderBlendedUTF8, TTF_Font * font){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	if (state.is_string(1) && state.is_table(2)){
		SDL_Color color;
		LuaSDL::fillColor(state, 2, color);
		SDL_Surface * surface = TTF_RenderUTF8_Blended(font, state.to_string(1).c_str(), color);
		if (surface){
			s.push(surface);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_TTF_Font::LOBJECT_METHOD(renderBlendedUNICODE, TTF_Font * font){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	if (state.is_string(1) && state.is_table(2)){
		SDL_Color color;
		LuaSDL::fillColor(state, 2, color);
		SDL_Surface * surface = TTF_RenderUNICODE_Blended(font, reinterpret_cast<const Uint16*>(state.to_string(1).c_str()), color);
		if (surface){
			s.push(surface);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	return 0;
}
int LuaSDL::Lua_SDL_TTF_Font::LOBJECT_METHOD(renderBlendedGlyph, TTF_Font * font){
	LuaSDL::Lua_SDL_Surface & s = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Surface);
	if (state.is_number(1) && state.is_table(2)){
		SDL_Color color;
		LuaSDL::fillColor(state, 2, color);
		SDL_Surface * surface = TTF_RenderGlyph_Blended(font, static_cast<Uint16>(state.to_integer(1)), color);
		if (surface){
			s.push(surface);
		}else{
			state.push_boolean(false);
		}
		return 1;
	}
	return 0;
}

void LuaSDL::init_ttf_font(lutok::state & state, moduleDef & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_TTF_Font);
	//module["mixerLoadMUS"] = lua_Mix_LoadMUS;
}
