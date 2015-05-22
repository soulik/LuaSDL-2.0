cmake_minimum_required (VERSION 3.1.0)
project (LUASDL2)

set(CMAKE_MODULE_PATH "${LUASDL2_SOURCE_DIR}/cmake")

set(LUASDL2_LIBRARIES "")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
# set(CMAKE_BINARY_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin")

# SDL 2

set(LUASDL2_USE_INTERNAL_SDL2 ON CACHE BOOL "Build and use internal copy of libSDL2")

if(LUASDL2_USE_INTERNAL_SDL2)
	set(SDL_SHARED ON CACHE BOOL "libSDL2 shared library")
	set(SDL_STATIC OFF CACHE BOOL "libSDL2 static library")

	add_subdirectory(dependencies/libsdl2)

	set(SDL2_DYNAMIC_LIBRARY_DIRECTORIES )

	#find_library(SDL2_LIBRARY_TEMP
	#	NAMES SDL2
	#	HINTS
	#	$ENV{SDL2DIR}
	#	PATH_SUFFIXES Debug Release
	#	PATHS
	#	${SDL2_BINARY_DIR}
	#)
	
	set_target_properties(SDL2
    	PROPERTIES
	    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	)

	#set(SDL2_LIBRARY ${SDL2_LIBRARY_TEMP})
	#set(SDL2_LIBRARY ${SDL_LIBS})
	set(SDL2_LIBRARY $<TARGET_LINKER_FILE:SDL2>)
	set(SDL2_INCLUDE_DIR dependencies/libsdl2/include)

	include_directories( ${SDL2_INCLUDE_DIR})
	list(APPEND LUASDL2_LIBRARIES ${SDL2_LIBRARY})
else()
	find_package(SDL2 REQUIRED)

	include_directories( ${SDL2_INCLUDE_DIR})
	list(APPEND LUASDL2_LIBRARIES ${SDL2_LIBRARY})
endif()

# SDL_image

set(PNG_STATIC OFF CACHE BOOL "")
set(PNG_TESTS OFF CACHE BOOL "")
# set(SDL2IMAGE_INCLUDE_DIR "" CACHE PATH "libSDL2_image include directory")
# set(SDL2IMAGE_LIBRARY "" CACHE FILEPATH "libSDL2_image library")
add_subdirectory(dependencies/sdl_image)
include_directories(dependencies/sdl_image)
list(APPEND LUASDL2_LIBRARIES SDLIMAGE)

# SDL_mixer

# set(SDL2MIXER_INCLUDE_DIR "" CACHE PATH "libSDL2_mixer include directory")
# set(SDL2MIXER_LIBRARY "" CACHE FILEPATH "libSDL2_mixer library")
add_subdirectory(dependencies/sdl_mixer)
include_directories(dependencies/sdl_mixer)
list(APPEND LUASDL2_LIBRARIES SDLMIXER)

# SDL_ttf

# set(SDL2TTF_INCLUDE_DIR "" CACHE PATH "libSDL2_ttf include directory")
# set(SDL2TTF_LIBRARY "" CACHE FILEPATH "libSDL2_ttf library")
add_subdirectory(dependencies/sdl_ttf)
include_directories(dependencies/sdl_ttf)
list(APPEND LUASDL2_LIBRARIES SDLTTF)

# Include Lua 5.1

include(FindLua51)
include_directories(${LUA_INCLUDE_DIR})

include_directories(dependencies/lutok2/include)

add_subdirectory(src)
