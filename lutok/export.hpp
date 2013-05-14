#if !defined(LUA_API)
	#if defined(LUA_BUILD_AS_DLL)
		#if defined(LUA_LIB)
			#define LUA_API		__declspec(dllexport)
		#else
			#define LUA_API		__declspec(dllimport)
		#endif
	#else
		#define LUA_API		extern
	#endif
	#define LUALIB_API	LUA_API
#endif
