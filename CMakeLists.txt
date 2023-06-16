# While FetchContent only requires CMake 3.11, selecting C++20 through
# CMAKE_CXX_STANDARD requires 3.12 and the convenience function
# `FetchContent_MakeAvailable` was introduced in CMake 3.14
cmake_minimum_required(VERSION 3.14.0)
project(SparklesGame VERSION 0.0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell that on Windows OS we want to build a GUI application
if(WIN32)

	if (CMAKE_GENERATOR MATCHES "Visual Studio .*")
		# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS") # Disable console appearence
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE") # Show console with debug information
	else()
		# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
	endif()
	
	# Set the Freetype directory manually
	# Change all of these three path to the correct depending on where FreeType BUILD on your Windows OS machine
	set(Freetype_DIR "${CMAKE_SOURCE_DIR}/third_party/freetype")
	set(FREETYPE_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/third_party/freetype/include")
	# include_directories("L:/freetype-2.13.0-win64/include/freetype2")
	set(FREETYPE_LIBRARY "${CMAKE_SOURCE_DIR}/third_party/freetype/bin")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Find the Freetype package
# find_package(Freetype REQUIRED)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE) # To allow cmake print intermidiate comments
	
FetchContent_Declare(
	SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	# GIT_REPOSITORY git@github.com:libsdl-org/SDL.git
    GIT_TAG release-2.26.5
    # GIT_TAG SDL2
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
	SDL2_ttf
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
	# GIT_REPOSITORY git@github.com:libsdl-org/SDL_ttf.git
	# GIT_TAG        release-2.20.2 # replace with the version you want to use
	
	# Only this tag work when use SDL2 library, for some reason
	GIT_TAG       SDL2 # Gives you SDL2_ttf 2.21.0
)
FetchContent_MakeAvailable(SDL2_ttf)

FetchContent_Declare(
	SDL2_image
	# URL "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.6.3.tar.gz" # replace x.x.x with the version you want to download
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
	# GIT_REPOSITORY git@github.com/libsdl-org/SDL_image.git
	# GIT_TAG        release-2.6.x # replace with the version you want to use
	GIT_TAG       SDL2 # Gives you SDL2_image 2.7.0
)
FetchContent_MakeAvailable(SDL2_image)

# SDL2 library for fonts
# if(WIN32)

# set(SDL_TTF_DIR "${CMAKE_SOURCE_DIR}/third_party/SDL2_ttf-2.20.2_VC")
# set(SDL_TTF_LIBRARIES "${CMAKE_SOURCE_DIR}/third_party/SDL2_ttf-2.20.2_VC/lib/x86")
# set(SDL_TTF_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/third_party/SDL2_ttf-2.20.2_VC/include")
# find_package(SDL_ttf REQUIRED)

# else()

# endif()

# message("FOUND DIRECTORY FOR SDL2_ttf: " "${SDL2_TTF_INCLUDE_DIRS}")

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
set(LIB_APPLICATION "${LIBRARIES}/application")
set(UTILS "${LIBRARIES}/utilities")

set(LIB_TYPE "SHARED")

# include_directories(${UTILS})

# Create separate module for the arena projectile
add_library(
	arena
	${LIB_TYPE}
	${LIB_ARENA}/Arena.cpp
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

# Create separate module for the background projectile
add_library(
	background
	${LIB_TYPE}
	${LIB_BACK}/Background.cpp
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

# # Create separate module for the text widget projectile
add_library(
	textwidget
	${LIB_TYPE}
	${LIB_TWIDGET}/TextWidget.cpp
)
target_include_directories(
	textwidget
	PRIVATE ${LIB_TWIDGET}
	# PRIVATE ${SDL2_TTF_INCLUDE_DIRS}
	# PRIVATE ${FREETYPE_INCLUDE_DIRS}
)
target_link_libraries(
	textwidget
	PUBLIC SDL2::SDL2
	PUBLIC SDL2_ttf::SDL2_ttf
	# PUBLIC "${SDL_TTF_LIBRARIES}/SDL2_ttf.lib"
)

# Create separate module for the game application
add_library(
	application
	${LIB_TYPE}
	${LIB_APPLICATION}/WheelGameApplication.cpp
)
target_include_directories(
	application
	PUBLIC ${LIB_APPLICATION}
	PUBLIC ${LIB_ARENA}
	PUBLIC ${LIB_BACK}
	PUBLIC ${LIB_WHEEL}
	PUBLIC ${UTILS}
	PUBLIC ${LIB_TWIDGET}
	# PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
	# PUBLIC ${FREETYPE_INCLUDE_DIRS}
)
target_link_libraries(
	application
	PUBLIC arena
	PUBLIC background
	PUBLIC wheel
	PUBLIC textwidget
)

# create executable
add_executable(
	sparkle
	targets/sparkle.cpp
)
# linking all necessary libraries
target_link_libraries(
	sparkle
	PRIVATE application
)

# I would like to keep every target binary in it's own dir,
# also DEBUG and RELEASE dir's inside them as well
# 'executables' - all executables root

# Define a function to set common target properties
function(set_output_properties TARGET BUILD_TYPE) # BUILD_TYPE == DEBUG || RELEASE
    set_target_properties(
        ${TARGET}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "../executables/${BUILD_TYPE}/sparkle"				# Binary
        LIBRARY_OUTPUT_DIRECTORY "../executables/${BUILD_TYPE}/sparkle"				# Dynamic libraries
        ARCHIVE_OUTPUT_DIRECTORY "../executables/${BUILD_TYPE}/sparkle/static_libs" # Static libraries
    )
	if(NOT EXISTS ../executables/${BUILD_TYPE}/sparkle/assets/)
		add_custom_command(
			TARGET sparkle POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/assets
			$<TARGET_FILE_DIR:sparkle>/assets
		)
	endif()
endfunction()

# Specify where target binary will be saved
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")

	set_output_properties(arena "DEBUG")
	set_output_properties(background "DEBUG")
	set_output_properties(wheel "DEBUG")
	set_output_properties(textwidget "DEBUG")
	set_output_properties(application "DEBUG")
	set_output_properties(sparkle "DEBUG")
	
	if(WIN32)

		add_custom_command(
			TARGET sparkle POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
				"$<TARGET_FILE_DIR:SDL2::SDL2>/SDL2d.dll"
				$<TARGET_FILE_DIR:sparkle>/"SDL2d.dll"
		)
		add_custom_command(
			TARGET sparkle POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
				"$<TARGET_FILE_DIR:SDL2_image::SDL2_image>/SDL2_imaged.dll"
				$<TARGET_FILE_DIR:sparkle>/"SDL2_imaged.dll"
		)
		add_custom_command(
			TARGET sparkle POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
				"$<TARGET_FILE_DIR:SDL2_ttf::SDL2_ttf>/SDL2_ttfd.dll"
				$<TARGET_FILE_DIR:sparkle>/"SDL2_ttfd.dll"
		)

	endif()

else()

	set_output_properties(arena "RELEASE")
	set_output_properties(background "RELEASE")
	set_output_properties(wheel "RELEASE")
	set_output_properties(textwidget "RELEASE")
	set_output_properties(application "RELEASE")
	set_output_properties(sparkle "RELEASE")

	if(WIN32)

		add_custom_command(
			TARGET sparkle POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
				"$<TARGET_FILE_DIR:SDL2::SDL2>/SDL2.dll"
				$<TARGET_FILE_DIR:sparkle>/"SDL2.dll"
		)
		add_custom_command(
			TARGET sparkle POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
				"$<TARGET_FILE_DIR:SDL2_image::SDL2_image>/SDL2_image.dll"
				$<TARGET_FILE_DIR:sparkle>/"SDL2_image.dll"
		)
		add_custom_command(
			TARGET sparkle POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
				"$<TARGET_FILE_DIR:SDL2_ttf::SDL2_ttf>/SDL2_ttf.dll"
				$<TARGET_FILE_DIR:sparkle>/"SDL2_ttf.dll"
		)

	endif()

endif()

if (CMAKE_GENERATOR MATCHES "Visual Studio .*")
	target_compile_options(
		sparkle
		PRIVATE
		/W3
		/_CRT_SECURE_NO_WARNINGS
	)
else()
	target_compile_options(
		sparkle
		PRIVATE
		-Wall
		-Wextra
		-Wpedantic
		-Wconversion
	)
endif()
