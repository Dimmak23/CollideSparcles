# While FetchContent only requires CMake 3.11, selecting C++20 through
# CMAKE_CXX_STANDARD requires 3.12 and the convenience function
# `FetchContent_MakeAvailable` was introduced in CMake 3.14
cmake_minimum_required(VERSION 3.14.0)
project(RENDERS VERSION 0.0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
	add_compile_options(/W3)
elseif(WINDOWS)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
    # additional warnings
    add_compile_options(
		-Wall
		-Wextra
		-Wpedantic
		-Wconversion
		)
else()
	add_compile_options(
		-Wall
		-Wextra
		-Wpedantic
		-Wconversion
	)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Actual usage will be kept for every target in the separate file
# 'targets' - all targets here

# Let's keep features that we will freq. re-compile and add there something
# also explicitly telling that some features needs testing
set(INCLUDES "${CMAKE_SOURCE_DIR}/tested_headers")
include_directories(${INCLUDES})

# Starting point for all libraries, every single of them will be added
# explicitly with modificator (PRIVATE, PUBLIC, INTERFACE)
set(LIBRARIES "${CMAKE_SOURCE_DIR}/libs")

# target reder_test don't have any for now
# add_library(
    # searchBroken
    # SHARED
    # ${LIBRARIES}/searchers/search_brocken.hpp
    # ${LIBRARIES}/searchers/search_brocken.cpp
# )

# I would like to keep every target binary in it's own dir,
# also DEBUG and RELEASE dir's inside them as well
# 'executables' - all executables root

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE) # To allow cmake print intermidiate comments

FetchContent_Declare(
	SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	# GIT_REPOSITORY git@github.com:libsdl-org/SDL.git
    GIT_TAG release-2.26.4
    # GIT_TAG SDL2
)

FetchContent_MakeAvailable(SDL2)

# create executable
add_executable(
	render_test
	targets/render.cpp
	# ${INCLUDES}/header_01.cpp
	# ${INCLUDES}/header_02.cpp
	# ${INCLUDES}/header_03.cpp
)

# Specify where target binary will be saved
set_target_properties(
    render_test
    PROPERTIES
	if(DEBUG)
    RUNTIME_OUTPUT_DIRECTORY "../executables/DEBUG/render_test"
    LIBRARY_OUTPUT_DIRECTORY "../executables/DEBUG/render_test"				# Dynamic libraries
    ARCHIVE_OUTPUT_DIRECTORY "../executables/DEBUG/render_test/static_libs" 	# Static libraries
	else()
    RUNTIME_OUTPUT_DIRECTORY "../executables/RELEASE/render_test"
    LIBRARY_OUTPUT_DIRECTORY "../executables/RELEASE/render_test"				# Dynamic libraries
    ARCHIVE_OUTPUT_DIRECTORY "../executables/RELEASE/render_test/static_libs" 	# Static libraries
	endif()
)

# do we need to include linked directories?
# target_include_directories(
# 	render_test
# 	PUBLIC ${INCLUDES}
# 	PUBLIC ${LIBRARIES}
# )

# linking all necessary lins
target_link_libraries(
	render_test
	PRIVATE SDL2::SDL2
	# PRIVATE searchBroken
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
	# if(NOT EXISTS ../executables/DEBUG/render_test/assets/)
		add_custom_command(
			TARGET render_test POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/assets
			$<TARGET_FILE_DIR:render_test>/assets
		)
	# endif()

else()

endif()
