#include "objects/iconv.hpp"
#include <lua.hpp>

namespace LuaSDL {

	int Iconv::convert(State & state, SDL_iconv_t * iconv){
		Stack * stack = state.stack;

		if (stack->is<LUA_TSTRING>(1)){
			const std::string input = stack->toLString(1);
			const char * inbuf = input.c_str();
			size_t inbytesleft = input.length() + 1;
			size_t stringsize = inbytesleft > 4 ? inbytesleft : 4;;
			size_t outbytesleft = stringsize;

			char * string = static_cast<char*>(SDL_malloc(stringsize));
			char *outbuf = string;

			if (string){
				size_t retCode = 0;

				SDL_memset(outbuf, 0, 4);
				while (inbytesleft > 0) {
					retCode = SDL_iconv(*iconv, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
					switch (retCode) {
					case SDL_ICONV_E2BIG:
					{
						char *oldstring = string;
						stringsize *= 2;
						string = static_cast<char*>(SDL_realloc(string, stringsize));
						if (!string) {
							stack->push<const std::string &>("");
							return 1;
						}
						outbuf = string + (outbuf - oldstring);
						outbytesleft = stringsize - (outbuf - string);
						SDL_memset(outbuf, 0, 4);
					}
					break;
					case SDL_ICONV_EILSEQ:
						/* Try skipping some input data - not perfect, but... */
						++inbuf;
						--inbytesleft;
						break;
					case SDL_ICONV_EINVAL:
					case SDL_ICONV_ERROR:
						/* We can't continue... */
						inbytesleft = 0;
						break;
					}
				}
				stack->pushLString(string, stringsize);
				SDL_free(string);
				return 1;
			}
			stack->push<const std::string &>("");
			return 1;
		}
		return 0;
	}

	SDL_iconv_t * Iconv::constructor(State & state, bool & managed){
		Stack * stack = state.stack;
		Iconv * interfaceIconv = state.getInterface<Iconv>("LuaSDL_Iconv");
		std::string to_code = "UTF-8";
		std::string from_code = "UTF-8";

		if (stack->is<LUA_TSTRING>(1)){
			to_code = stack->toLString(1);
		}

		if (stack->is<LUA_TSTRING>(2)){
			from_code = stack->toLString(2);
		}

		SDL_iconv_t _iconv = SDL_iconv_open(to_code.c_str(), from_code.c_str());
		SDL_iconv_t * iconv = new SDL_iconv_t;
		*iconv = _iconv;

		return iconv;
	}

	static int lua_iconv(State & state){
		Stack * stack = state.stack;

		std::string to_code = "UTF-8";
		std::string from_code = "UTF-8";
		if (stack->is<LUA_TSTRING>(1)){
			const std::string input = stack->toLString(1);
			size_t inbytesleft = input.length() + 1;

			if (stack->is<LUA_TSTRING>(2)){
				to_code = stack->toLString(2);
			}

			if (stack->is<LUA_TSTRING>(3)){
				from_code = stack->toLString(3);
			}

			char * output = SDL_iconv_string(to_code.c_str(), from_code.c_str(), input.c_str(), inbytesleft);
			if (output){
				stack->pushLString(output, inbytesleft);
				SDL_free(output);
			}
			else{
				stack->push<const std::string &>("");
			}
			return 1;
		}
		return 0;
	}

	void initIconv(State * state, Module & module){
		INIT_OBJECT(Iconv);
		//module["iconvOpen"] = lua_iconv_open;
		module["iconv"] = lua_iconv;
	}

};
