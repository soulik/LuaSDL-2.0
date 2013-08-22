#ifndef LUA_SDL_OBJECTS_ICONV_H
#define LUA_SDL_OBJECTS_ICONV_H

#include "common.hpp"

namespace LuaSDL {

	class Lua_SDL_Iconv : public LObject<Lua_SDL_Iconv, SDL_iconv_t> {
	public:
		LOBJECT_DEFINE_CLASS(Lua_SDL_Iconv, SDL_iconv_t, "Iconv") {
			LOBJECT_ADD_METHOD(LuaSDL::Lua_SDL_Iconv, "convert", convert);
		}

		void destructor(lutok::state & s, SDL_iconv_t iconv){
			SDL_iconv_close(iconv);
		}

		int LOBJECT_METHOD(convert, SDL_iconv_t iconv){
			if (state.is_string(1)){
				std::string input = state.to_string(1);
				const char * inbuf = input.c_str();
				size_t inbytesleft = SDL_strlen(inbuf)+1;
				size_t stringsize = inbytesleft > 4 ? inbytesleft : 4;;
				size_t outbytesleft = stringsize;

				char * string = static_cast<char*>(SDL_malloc(stringsize));
				char *outbuf = string;

				if (string){
					size_t retCode = 0;

					SDL_memset(outbuf, 0, 4);
					while (inbytesleft > 0) {
						retCode = SDL_iconv(iconv, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
						switch (retCode) {
						case SDL_ICONV_E2BIG:
							{
								char *oldstring = string;
								stringsize *= 2;
								string = static_cast<char*>(SDL_realloc(string, stringsize));
								if (!string) {
									state.push_literal("");
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
					state.push_string(string);
					SDL_free(string);
					return 1;
				}
				state.push_literal("");
				return 1;
			}
			return 0;
		}
	};
}

#endif