set(LUASDL2_SRC
    audio.cpp
    basics.cpp
    constants.cpp
    file.cpp
    gl_context.cpp
    input.cpp
	main.cpp
	platform.cpp
	power.cpp
	sdl_image.cpp
	sdl_mixer.cpp
	sdl_ttf.cpp
	threads.cpp
	timers.cpp
	utils.cpp
	video.cpp
)

set(LUASDL2_OBJECTS_SRC
	objects/audiobuffer.cpp
	objects/audiodevice.cpp
	objects/audiospec.cpp
	objects/cursor.cpp
	objects/displaymode.cpp
	objects/event.cpp
	objects/gamecontroller.cpp
	objects/gl_context.cpp
	objects/haptic.cpp
	objects/hapticeffect.cpp
	objects/iconv.cpp
	objects/joystick.cpp
	objects/mix_chunk.cpp
	objects/mix_music.cpp
	objects/pixelformat.cpp
	objects/rect.cpp
	objects/renderer.cpp
	objects/surface.cpp
	objects/texture.cpp
	objects/thread.cpp
	objects/timer.cpp
	objects/ttf_font.cpp
	objects/window.cpp
)

set(LUASDL2_H
	common.hpp
	utils.hpp
)

set(LUASDL2_OBJECTS_H
	objects/audiobuffer.hpp
	objects/audiodevice.hpp
	objects/audiospec.hpp
	objects/cursor.hpp
	objects/displaymode.hpp
	objects/event.hpp
	objects/gamecontroller.hpp
	objects/gl_context.hpp
	objects/haptic.hpp
	objects/hapticeffect.hpp
	objects/iconv.hpp
	objects/joystick.hpp
	objects/mix_chunk.hpp
	objects/mix_music.hpp
	objects/pixelformat.hpp
	objects/rect.hpp
	objects/renderer.hpp
	objects/surface.hpp
	objects/texture.hpp
	objects/thread.hpp
	objects/timer.hpp
	objects/ttf_font.hpp
	objects/window.hpp
)

set(LUASDL2_SOURCES
	${LUASDL2_SRC}
	${LUASDL2_H}
	${LUASDL2_OBJECTS_SRC}
	${LUASDL2_OBJECTS_H}
)

source_group(objects FILES ${LUASDL2_OBJECTS_SRC} ${LUASDL2_OBJECTS_HDR})

include_directories(./)

set(LUASDL2_VERSION_SCRIPT luasdl2.version)

IF(UNIX)
    IF(CMAKE_COMPILER_IS_GNUCC)
         SET(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_CXX_COMPILE_OPTIONS_VISIBILITY}hidden -Wl,--version-script=${LUASDL2_VERSION_SCRIPT}")
    ENDIF(CMAKE_COMPILER_IS_GNUCC)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-declarations")
ENDIF(UNIX)

add_library(LUASDL2 SHARED
	${LUASDL2_SOURCES}
)

set_property(TARGET LUASDL2 PROPERTY CXX_STANDARD 11)
set_property(TARGET LUASDL2 PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries (LUASDL2
	${LUASDL2_LIBRARIES}
	${LUA_LIBRARIES}
)

set_target_properties(LUASDL2
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	PREFIX ""
	OUTPUT_NAME "LuaSDL2"
)

