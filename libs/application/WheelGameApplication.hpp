#pragma once

#ifdef _WIN32

#include <SDL.h>
#include <SDL_image.h>

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include "Arena.hpp"
#include "Background.hpp"
#include "Wheel.hpp"

class WheelGameApplication
{
public:
	WheelGameApplication(int argc, char* argv[]);
	~WheelGameApplication();
	void initializeSDL();
	void clampObjects(Arena* pArena, Wheel* pWheel);
	void gamePlay();

private:
	// let's deprecate copying application
	WheelGameApplication(const WheelGameApplication&) = delete;
	WheelGameApplication operator=(const WheelGameApplication&) = delete;

	unsigned int _appXPos{ 100 };
	unsigned int _appYPos{ 100 };
	unsigned int _appWidth{ 640 };
	unsigned int _appHeight{ 480 };

	SDL_Window* _gWindow{ nullptr };
	SDL_Renderer* _gRenderer{ nullptr };

	SDL_Rect _gRect;

	Background* _background{ nullptr };
	Arena* _arena{ nullptr };
	Wheel* _wheel{ nullptr };

	// keeping track on the status of the creation
	bool _callingStatus{ false };

	// check maybe user whant to exit
	bool _running{ true };

	// check if we already have shrink arena and adjust wheel position
	bool _firstTimeEnter{ true };
};
