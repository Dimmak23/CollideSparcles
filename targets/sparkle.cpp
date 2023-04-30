#ifdef _WIN32

#include <SDL.h>
#include <SDL_image.h>

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include <iostream>

#include "WheelGameApplication.hpp"

int main(int argc, char const* argv[])
{
	WheelGameApplication* application = new WheelGameApplication(argc, argv);

	application->initializeSDL();

	application->gamePlay();

	delete application;

	return 0;
}
