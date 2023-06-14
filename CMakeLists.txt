# While FetchContent only requires CMake 3.11, selecting C++20 through
# CMAKE_CXX_STANDARD requires 3.12 and the convenience function
# `FetchContent_MakeAvailable` was introduced in CMake 3.14
cmake_minimum_required(VERSION 3.14.0)
project(SparklesGame VERSION 0.0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# target reder_test don't have any for now
# add_library(
	# searchBroken
    # STATIC
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
    GIT_TAG release-2.26.5
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

# Actual usage will be kept for every target in the separate file
# 'targets' - all targets here

# Let's keep features that we will freq. re-compile and add there something
# also explicitly telling that some features needs testing
set(INCLUDES "${CMAKE_SOURCE_DIR}/tested_headers")
# include_directories(${INCLUDES}) # don't include like this

# Starting point for all libraries, every single of them will be added
# explicitly with modificator (PRIVATE, PUBLIC, INTERFACE)
set(LIBRARIES "${CMAKE_SOURCE_DIR}/libs")
set(LIB_ARENA "${LIBRARIES}/arena")
set(LIB_BACK "${LIBRARIES}/background")
set(LIB_WHEEL "${LIBRARIES}/wheel")
set(LIB_APPLICATION "${LIBRARIES}/application")
set(UTILS "${LIBRARIES}/utilities")

# Create separate module for the arena projectile
add_library(
	arena
	STATIC
	${LIB_ARENA}/Arena.cpp
)
target_include_directories(
	arena
	PRIVATE ${LIB_ARENA}
	PRIVATE ${UTILS}
)
target_link_libraries(
	arena
	PRIVATE SDL2::SDL2
	PRIVATE SDL2_image::SDL2_image
)

# Create separate module for the background projectile
add_library(
	background
	STATIC
	${LIB_BACK}/Background.cpp
)
target_include_directories(
	background
	PRIVATE ${LIB_BACK}
	PRIVATE ${UTILS}
)
target_link_libraries(
	background
	PRIVATE SDL2::SDL2
	PRIVATE SDL2_image::SDL2_image
)

# Create separate module for the wheel projectile
add_library(
	wheel
	STATIC
	${LIB_WHEEL}/Wheel.cpp
)
target_include_directories(
	wheel
	PRIVATE ${LIB_WHEEL}
	PRIVATE ${UTILS}
)
target_link_libraries(
	wheel
	PRIVATE SDL2::SDL2
	PRIVATE SDL2_image::SDL2_image
)

# Create separate module for the game application
add_library(
	application
	STATIC
	${LIB_APPLICATION}/WheelGameApplication.cpp
)
target_include_directories(
	application
	PUBLIC ${LIB_APPLICATION}
	PUBLIC ${LIB_ARENA}
	PUBLIC ${LIB_WHEEL}
	PUBLIC ${UTILS}
	PUBLIC ${LIB_BACK}
)
target_link_libraries(
	application
	PRIVATE SDL2::SDL2
	PRIVATE SDL2_image::SDL2_image
	PRIVATE arena
	PRIVATE background
	PRIVATE wheel
)

# create executable
add_executable(
	sparkle
	targets/sparkle.cpp
	# ${INCLUDES}/header_01.cpp
	# ${INCLUDES}/header_02.cpp
	# ${INCLUDES}/header_03.cpp
)
#
# target_include_directories(
# 	sparkle
# 	PRIVATE ${LIB_APPLICATION}
# )
# linking all necessary libraries
target_link_libraries(
	sparkle
	PRIVATE SDL2::SDL2
	PRIVATE SDL2_image::SDL2_image
	PRIVATE application
)
		
# Specify where target binary will be saved
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
# if(CMAKE_BUILD_TYPE MATCHES "Debug")
	
	set_target_properties(
		arena
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle"
		LIBRARY_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle/static_libs" 	# Static libraries
	)
	set_target_properties(
		background
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle"
		LIBRARY_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle/static_libs" 	# Static libraries
	)
	set_target_properties(
		wheel
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle"
		LIBRARY_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle/static_libs" 	# Static libraries
	)
	set_target_properties(
		application
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle"
		LIBRARY_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle/static_libs" 	# Static libraries
	)
	set_target_properties(
		sparkle
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle"
		LIBRARY_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/DEBUG/sparkle/static_libs" 	# Static libraries
	)
	
	# add_custom_command(
	# 	TARGET sparkle POST_BUILD
	# 	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	# 		"$<TARGET_FILE_DIR:SDL2::SDL2>/SDL2d.dll"
	# 		$<TARGET_FILE_DIR:sparkle>/"SDL2d.dll"
	# )
	# add_custom_command(
	# 	TARGET sparkle POST_BUILD
	# 	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	# 		"$<TARGET_FILE_DIR:SDL2_image::SDL2_image>/SDL2_imaged.dll"
	# 		$<TARGET_FILE_DIR:sparkle>/"SDL2_imaged.dll"
	# )

	if(NOT EXISTS ../executables/DEBUG/sparkle/assets/)
		add_custom_command(
			TARGET sparkle POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/assets
			$<TARGET_FILE_DIR:sparkle>/assets
		)
	endif()
else()

	set_target_properties(
		arena
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle"
		LIBRARY_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle/static_libs" 	# Static libraries
	)
	set_target_properties(
		background
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle"
		LIBRARY_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle/static_libs" 	# Static libraries
	)
	set_target_properties(
		wheel
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle"
		LIBRARY_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle/static_libs" 	# Static libraries
	)
	set_target_properties(
		application
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle"
		LIBRARY_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle/static_libs" 	# Static libraries
	)
	set_target_properties(
		sparkle
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle"
		LIBRARY_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle"				# Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "../executables/RELEASE/sparkle/static_libs" 	# Static libraries
	)

	# add_custom_command(
	# 	TARGET sparkle POST_BUILD
	# 	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	# 		"$<TARGET_FILE_DIR:SDL2::SDL2>/SDL2.dll"
	# 		$<TARGET_FILE_DIR:sparkle>/"SDL2.dll"
	# )
	# add_custom_command(
	# 	TARGET sparkle POST_BUILD
	# 	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	# 		"$<TARGET_FILE_DIR:SDL2_image::SDL2_image>/SDL2_image.dll"
	# 		$<TARGET_FILE_DIR:sparkle>/"SDL2_image.dll"
	# )

	if(NOT EXISTS ../executables/RELEASE/sparkle/assets/)
			add_custom_command(
				TARGET sparkle POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/assets
				$<TARGET_FILE_DIR:sparkle>/assets
			)
	endif()
endif()

# if (MSVC)
# 	target_compile_options(
# 		sparkle
# 		PRIVATE
# 		/W3
# 	)
# elseif(WINDOWS)
# 	target_compile_options(
# 		sparkle
# 		PRIVATE
# 		-Wall
# 		-Wextra
# 		-Wpedantic
# 		-Wconversion
# 	)
# else()
# target_compile_options(
# 	sparkle
# 	PRIVATE
# 	-Wall
# 	-Wextra
# 	-Wpedantic
# 	-Wconversion
# )
# endif()
