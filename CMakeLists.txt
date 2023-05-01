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
# include_directories(${INCLUDES})

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

FetchContent_Declare(
	SDL2_image
	# URL "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.6.3.tar.gz" # replace x.x.x with the version you want to download
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
	# GIT_REPOSITORY git@github.com/libsdl-org/SDL_image.git
	# GIT_TAG        release-2.6.x # replace with the version you want to use
	GIT_TAG       SDL2
)

FetchContent_MakeAvailable(SDL2_image)

# create executable
add_executable(
	render_test
	targets/render.cpp
	# ${INCLUDES}/header_01.cpp
	# ${INCLUDES}/header_02.cpp
	# ${INCLUDES}/header_03.cpp
)

add_executable(
	transparent
	targets/transparent.cpp
	# ${INCLUDES}/header_01.cpp
	# ${INCLUDES}/header_02.cpp
	# ${INCLUDES}/header_03.cpp
)
	
add_executable(
	full_tr
	targets/full_tr.cpp
	# ${INCLUDES}/header_01.cpp
	# ${INCLUDES}/header_02.cpp
	# ${INCLUDES}/header_03.cpp
)

add_executable(
	back_tr
	targets/back_tr.cpp
	# ${INCLUDES}/header_01.cpp
	# ${INCLUDES}/header_02.cpp
	# ${INCLUDES}/header_03.cpp
)

add_executable(
	four_tiles
	targets/four_tiles.cpp
	# ${INCLUDES}/header_01.cpp
	# ${INCLUDES}/header_02.cpp
	# ${INCLUDES}/header_03.cpp
)

add_executable(
	sparkle
	targets/sparkle.cpp
	${INCLUDES}/Wheel.cpp
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

set_target_properties(
	transparent
	PROPERTIES
	if(DEBUG)
		RUNTIME_OUTPUT_DIRECTORY "../executables/DEBUG/transparent"
		LIBRARY_OUTPUT_DIRECTORY "../executables/DEBUG/transparent"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/DEBUG/transparent/static_libs" 	# Static libraries
	else()
		RUNTIME_OUTPUT_DIRECTORY "../executables/RELEASE/transparent"
		LIBRARY_OUTPUT_DIRECTORY "../executables/RELEASE/transparent"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/RELEASE/transparent/static_libs" 	# Static libraries
	endif()
)

set_target_properties(
	full_tr
	PROPERTIES
	if(DEBUG)
		RUNTIME_OUTPUT_DIRECTORY "../executables/DEBUG/full_tr"
		LIBRARY_OUTPUT_DIRECTORY "../executables/DEBUG/full_tr"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/DEBUG/full_tr/static_libs" 	# Static libraries
	else()
		RUNTIME_OUTPUT_DIRECTORY "../executables/RELEASE/full_tr"
		LIBRARY_OUTPUT_DIRECTORY "../executables/RELEASE/full_tr"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/RELEASE/full_tr/static_libs" 	# Static libraries
	endif()
)

set_target_properties(
	back_tr
	PROPERTIES
	if(DEBUG)
		RUNTIME_OUTPUT_DIRECTORY "../executables/DEBUG/back_tr"
		LIBRARY_OUTPUT_DIRECTORY "../executables/DEBUG/back_tr"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/DEBUG/back_tr/static_libs" 	# Static libraries
	else()
		RUNTIME_OUTPUT_DIRECTORY "../executables/RELEASE/back_tr"
		LIBRARY_OUTPUT_DIRECTORY "../executables/RELEASE/back_tr"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/RELEASE/back_tr/static_libs" 	# Static libraries
	endif()
)

set_target_properties(
	four_tiles
	PROPERTIES
	if(DEBUG)
		RUNTIME_OUTPUT_DIRECTORY "../executables/DEBUG/four_tiles"
		LIBRARY_OUTPUT_DIRECTORY "../executables/DEBUG/four_tiles"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/DEBUG/four_tiles/static_libs" 	# Static libraries
	else()
		RUNTIME_OUTPUT_DIRECTORY "../executables/RELEASE/four_tiles"
		LIBRARY_OUTPUT_DIRECTORY "../executables/RELEASE/four_tiles"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/RELEASE/four_tiles/static_libs" 	# Static libraries
	endif()
)

set_target_properties(
	sparkle
	PROPERTIES
	if(DEBUG)
		RUNTIME_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle"
		LIBRARY_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle/static_libs" 	# Static libraries
	else()
		RUNTIME_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle"
		LIBRARY_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle/static_libs" 	# Static libraries
	endif()
)

# linking all necessary lins
target_link_libraries(
	render_test
	PRIVATE SDL2::SDL2
	PRIVATE SDL2_image::SDL2_image
	# PRIVATE searchBroken
)

target_link_libraries(
	transparent
	PRIVATE SDL2::SDL2
	PRIVATE SDL2_image::SDL2_image
	# PRIVATE searchBroken
)

target_link_libraries(
	full_tr
	PRIVATE SDL2::SDL2
	PRIVATE SDL2_image::SDL2_image
	# PRIVATE searchBroken
)

target_link_libraries(
	back_tr
	PRIVATE SDL2::SDL2
	PRIVATE SDL2_image::SDL2_image
	# PRIVATE searchBroken
)

target_link_libraries(
	four_tiles
	PRIVATE SDL2::SDL2
	PRIVATE SDL2_image::SDL2_image
	# PRIVATE searchBroken
)

target_link_libraries(
	sparkle
	PRIVATE SDL2::SDL2
	PRIVATE SDL2_image::SDL2_image
	# PRIVATE searchBroken
)

target_include_directories(
	sparkle
	PUBLIC ${INCLUDES}
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
	if(NOT EXISTS ../executables/DEBUG/render_test/assets/)
		add_custom_command(
			TARGET render_test POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/assets
			$<TARGET_FILE_DIR:render_test>/assets
		)
		add_custom_command(
			TARGET transparent POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/assets
			$<TARGET_FILE_DIR:transparent>/assets
		)
		add_custom_command(
			TARGET full_tr POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/assets
			$<TARGET_FILE_DIR:full_tr>/assets
		)
		add_custom_command(
			TARGET back_tr POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/assets
			$<TARGET_FILE_DIR:back_tr>/assets
		)
		add_custom_command(
			TARGET four_tiles POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/assets
			$<TARGET_FILE_DIR:four_tiles>/assets
		)
		add_custom_command(
			TARGET sparkle POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/assets
			$<TARGET_FILE_DIR:sparkle>/assets
		)
	endif()

else()

endif()
