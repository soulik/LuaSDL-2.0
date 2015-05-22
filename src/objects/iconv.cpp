#include "objects/iconv.hpp"
#include <lua.hpp>

static int lua_iconv_open(State & state){
	LuaSDL::Lua_SDL_Iconv & ic = LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Iconv);
	std::string to_code = "UTF-8";
	std::string from_code = "UTF-8";

	if (stack->is<LUA_TSTRING>(1)){
		to_code = stack->to<const std::string>(1);
	}

	if (stack->is<LUA_TSTRING>(2)){
		from_code = stack->to<const std::string>(2);
	}

	SDL_iconv_t iconv = SDL_iconv_open(to_code.c_str(), from_code.c_str());
	if (iconv){
		ic.push(iconv);
	}else{
		stack->push<bool>(false);
	}
	return 1;
}

static int lua_iconv(State & state){
	std::string to_code = "UTF-8";
	std::string from_code = "UTF-8";
	if (stack->is<LUA_TSTRING>(1)){
		std::string input = stack->to<const std::string>(1);
		size_t inbytesleft = SDL_strlen(input.c_str())+1;

		if (stack->is<LUA_TSTRING>(2)){
			to_code = stack->to<const std::string>(1);
		}

		if (stack->is<LUA_TSTRING>(3)){
			from_code = stack->to<const std::string>(2);
		}

		char * output = SDL_iconv_string(to_code.c_str(), from_code.c_str(), input.c_str(), inbytesleft);
		if (output){
			stack->push<const std::string>(output);
			SDL_free(output);
		}else{
			state.push_literal("");
		}
		return 1;
	}
	return 0;
}

void LuaSDL::init_iconv(State & state, Module & module){
	LOBJECT_INSTANCE(LuaSDL::Lua_SDL_Iconv);
	module["iconvOpen"] = lua_iconv_open;
	module["iconv"] = lua_iconv;
}
