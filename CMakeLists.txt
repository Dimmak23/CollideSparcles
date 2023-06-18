# While FetchContent only requires CMake 3.11, selecting C++20 through
# CMAKE_CXX_STANDARD requires 3.12 and the convenience function
# `FetchContent_MakeAvailable` was introduced in CMake 3.14
cmake_minimum_required(VERSION 3.14.0)
project(SparclesGame VERSION 0.0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ? Why this function don't work?
# function(generator_flag DEBUG_FLAGS RELEASE_FLAGS)
# if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${DEBUG_FLAGS}") # Show console with debug information
# else()
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${RELEASE_FLAGS}") # Disable console appearence
# endif()
# endfunction()

if(NOT UNIX AND NOT MACOSX_BUNDLE) # ! What about Linux?
	if(CMAKE_GENERATOR MATCHES "Visual Studio .*")
		# generator_flag("/SUBSYSTEM:CONSOLE" "/SUBSYSTEM:WINDOWS")
		if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
			set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE") # Show console with debug information
		else()
			set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS") # Disable console appearence
		endif()
	else()
		# set(DFLAGS "-mconsole")
		# set(RFLAGS "-mwindows")
		# generator_flag(${DFLAGS} ${RFLAGS})
		if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
			set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole") # Show console with debug information
		else()
			set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows") # Disable console appearence
		endif()

		message("CMAKE_EXE_LINKER_FLAGS: " "${CMAKE_EXE_LINKER_FLAGS}.")
	endif()
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE) # To allow cmake print intermidiate comments

FetchContent_Declare(
	SDL2
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git # GIT_REPOSITORY git@github.com:libsdl-org/SDL.git
	GIT_TAG release-2.26.5
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
	SDL2_ttf
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git # GIT_REPOSITORY git@github.com:libsdl-org/SDL_ttf.git
	GIT_TAG SDL2 # Only this tag work when use SDL2 library, for some reason; Gives you SDL2_ttf 2.21.0
)
FetchContent_MakeAvailable(SDL2_ttf)

FetchContent_Declare(
	SDL2_image # URL "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.6.3.tar.gz" # replace x.x.x with the version you want to download
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git # GIT_REPOSITORY git@github.com/libsdl-org/SDL_image.git
	GIT_TAG SDL2 # Only this tag work when use SDL2 library, for some reason; Gives you SDL2_image 2.7.0
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
set(LIB_TWIDGET "${LIBRARIES}/textwidget")
set(LIB_BUBBLE "${LIBRARIES}/bubble")
set(LIB_APPLICATION "${LIBRARIES}/application")
set(UTILS "${LIBRARIES}/utilities")

set(LIB_TYPE "SHARED")

function(set_specific_definitions TARGET)
	# target_compile_definitions(${TARGET} PRIVATE _CRT_SECURE_NO_WARNINGS)
endfunction()

# Create separate module for the arena projectile
add_library(
	arena
	${LIB_TYPE}
	${LIB_ARENA}/Arena.cpp
	${LIB_ARENA}/Arena.hpp
)
target_include_directories(
	arena
	PRIVATE ${LIB_ARENA}
	PUBLIC ${UTILS}
)
target_link_libraries(
	arena
	PUBLIC SDL2::SDL2
	PUBLIC SDL2_image::SDL2_image
)
set_specific_definitions(
	arena
)

# Create separate module for the background projectile
add_library(
	background
	${LIB_TYPE}
	${LIB_BACK}/Background.cpp
	${LIB_BACK}/Background.hpp
)
target_include_directories(
	background
	PRIVATE ${LIB_BACK}
	PUBLIC ${UTILS}
)
target_link_libraries(
	background
	PUBLIC SDL2::SDL2
	PUBLIC SDL2_image::SDL2_image
)

# Create separate module for the wheel projectile
add_library(
	wheel
	${LIB_TYPE}
	${LIB_WHEEL}/Wheel.cpp
	${LIB_WHEEL}/Wheel.hpp
)
target_include_directories(
	wheel
	PRIVATE ${LIB_WHEEL}
	PUBLIC ${UTILS}
)
target_link_libraries(
	wheel
	PUBLIC SDL2::SDL2
	PUBLIC SDL2_image::SDL2_image
)
set_specific_definitions(
	wheel
)

# Create separate module for the text widget projectile
add_library(
	textwidget
	${LIB_TYPE}
	${LIB_TWIDGET}/TextWidget.cpp
	${LIB_TWIDGET}/TextWidget.hpp
)
target_include_directories(
	textwidget
	PRIVATE ${LIB_TWIDGET}
)
target_link_libraries(
	textwidget
	PUBLIC SDL2::SDL2
	PUBLIC SDL2_ttf::SDL2_ttf
)
set_specific_definitions(
	textwidget
)

# Create separate module for the bubble projectile
add_library(
	bubble
	${LIB_TYPE}
	${LIB_BUBBLE}/Bubble.cpp
	${LIB_BUBBLE}/Bubble.hpp
)
target_include_directories(
	bubble
	PRIVATE ${LIB_BUBBLE}
	PUBLIC ${UTILS}
)
target_link_libraries(
	bubble
	PUBLIC SDL2::SDL2
	PUBLIC SDL2_image::SDL2_image
)
set_specific_definitions(
	bubble
)

# Create separate module for the game application
add_library(
	application
	${LIB_TYPE}
	${LIB_APPLICATION}/WheelGameApplication.cpp
	${LIB_APPLICATION}/WheelGameApplication.hpp
)
target_include_directories(
	application
	PUBLIC ${LIB_APPLICATION}
	PUBLIC ${LIB_ARENA}
	PUBLIC ${LIB_BACK}
	PUBLIC ${LIB_WHEEL}
	PUBLIC ${LIB_TWIDGET}
	PUBLIC ${LIB_BUBBLE}
	PUBLIC ${UTILS}
)
target_link_libraries(
	application
	PUBLIC arena
	PUBLIC background
	PUBLIC wheel
	PUBLIC textwidget
	PUBLIC bubble
)
set_specific_definitions(
	application
)

# create executable
add_executable(
	sparcle
	targets/sparcle.cpp
)

# linking all necessary libraries
target_link_libraries(
	sparcle
	PRIVATE application
)
set_specific_definitions(
	sparcle
)

set(MAIN sparcle)

if(CMAKE_GENERATOR MATCHES "Visual Studio .*")
	target_compile_options(
		sparcle
		PRIVATE
		/W3
		/Wall
		/O1 # Creates small code.
		/GA # Optimizes for Windows applications
	)
else()
	target_compile_options(
		sparcle
		PRIVATE
		-Wall
		-Wextra
		-Wpedantic
		-Wconversion
	)
endif()

# I would like to keep every target binary in it's own dir,
# also DEBUG and RELEASE dir's inside them as well
# 'executables' - all executables root

# # Define a function to set common target properties
function(set_output_properties TARGET) # BUILD_TYPE == DEBUG || RELEASE
	set(COMMON_FOLDER "../executables/${CMAKE_BUILD_TYPE}/${MAIN}")

	set_target_properties(
		${TARGET}
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${COMMON_FOLDER}" # Binary
		LIBRARY_OUTPUT_DIRECTORY "${COMMON_FOLDER}" # Dynamic libraries
		ARCHIVE_OUTPUT_DIRECTORY "${COMMON_FOLDER}" # Static libraries
	)
endfunction()

function(set_properties_for_all)

	set_output_properties(arena)
	set_output_properties(background)
	set_output_properties(wheel)
	set_output_properties(textwidget)
	set_output_properties(bubble)
	set_output_properties(application)
	set_output_properties(sparcle)

	# Take assets with them
	if(NOT EXISTS ../executables/${CMAKE_BUILD_TYPE}/${MAIN}/assets/)
		add_custom_command(
			TARGET ${MAIN} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/assets
			$<TARGET_FILE_DIR:${MAIN}>/assets
		)
	endif()
endfunction()

# # Specify where target binary will be saved
set_properties_for_all(${CMAKE_BUILD_TYPE})

#
if(WIN32) # ! Why Linux don't need it?
	set(EXTENSION_NAME "dll")

	# Define function to copy DLL's on Windows
	function(copy_dll TARGET MODULE)
		# set(POSTFIX_DLL_NAME "")
		if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
			set(POSTFIX_DLL_NAME "d") # set to 'd' when Debug
		else()
			set(POSTFIX_DLL_NAME "")
		endif()

		add_custom_command(
			TARGET ${TARGET} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"$<TARGET_FILE_DIR:${MODULE}::${MODULE}>/${PREFIX}${MODULE}${POSTFIX_DLL_NAME}.${EXTENSION_NAME}"
			$<TARGET_FILE_DIR:${TARGET}>/"${PREFIX}${MODULE}${POSTFIX_DLL_NAME}.${EXTENSION_NAME}"
		)
	endfunction()

	copy_dll(sparcle SDL2)
	copy_dll(sparcle SDL2_image)
	copy_dll(sparcle SDL2_ttf)

endif()