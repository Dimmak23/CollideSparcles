#include "WheelGameApplication.hpp"

#include <iostream>

WheelGameApplication::WheelGameApplication(int argc, char* argv[])
{
	// take optional arguments with window size
	// proceed optional arguments

	// update destination window rectangle
	_gRect.x = _appXPos;
	_gRect.y = _appYPos;
	_gRect.w = _appWidth;
	_gRect.h = _appHeight;

	// Create the main window
	_gWindow = SDL_CreateWindow(				   //
		"Sparkling joy...",						   //
		_gRect.x, _gRect.y, _gRect.w, _gRect.h,	   //
		SDL_WINDOW_SHOWN						   //
	);

	// Check if window creation were succsessfull
	if (_gWindow == nullptr)
	{
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
	}

	// Create a renderer for the window
	_gRenderer = SDL_CreateRenderer(_gWindow, -1, SDL_RENDERER_ACCELERATED);

	// Check if renderer creation were succsessfull
	if (_gRenderer == nullptr)
	{
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
	}

	// Set 'nullptr' texture as a rendering target
	_callingStatus = SDL_SetRenderTarget(_gRenderer, nullptr);

	// initialize game objects

	// build background texture according to the window size
	_background = new Background(_gRenderer, _appWidth, _appHeight);

	// build arena lines with initial sizes
	_arena = new Arena(_gRenderer, _appWidth, _appHeight);

	// build wheel with initial size
	_wheel = new Wheel(_gRenderer, WUtils::_wheel._width, WUtils::_wheel._height);

	// build fps screen text
	// _fpsScreen =
	// 	new TextWidget(_gRenderer, "FPS: XXX.XXX", WUtils::_FPSfont.c_str(), 14, 50, 10, SDL_Color(50, 50, 50));
}

WheelGameApplication::~WheelGameApplication()
{
	// destroy resources
	SDL_DestroyRenderer(_gRenderer);
	SDL_DestroyWindow(_gWindow);

	// deallocate heap memory
	delete _wheel;
	delete _arena;
	delete _background;

	//
	SDL_Quit();
}

void WheelGameApplication::initializeSDL()
{
	// use parsed window size if any

	// Initialize SDL2 libraries
	_callingStatus = SDL_Init(SDL_INIT_VIDEO);
	if (_callingStatus != 0)
	{
		std::cout << "Couldn't initalize SDL2 libraries...\n";
		return;
	}

	// Loading SDL_Image dynamic libraries
	_callingStatus = IMG_Init(IMG_INIT_PNG);
	if (_callingStatus == 0)
	{
		std::cout << "Couldn't load SDL_Image dynamic libraries...\n";
		return;
	}

	// // Initialize SDL_ttf library
	// _callingStatus = TTF_Init();
	// if (_callingStatus != 0)
	// {
	// 	std::cout << "Couldn't load SDL_ttf dynamic libraries...\n";
	// 	return;
	// }
}

void WheelGameApplication::clampObjects(Arena* pArena, Wheel* pWheel)
{
	if (pWheel->rightSide() > pArena->rightSide())
	{
		pWheel->bounce(pArena->rightSide(), RIGHT);
		pWheel->setMoveDelta(DOWN);
	}
	else if (pWheel->downSide() > pArena->downSide())
	{
		pWheel->bounce(pArena->downSide(), DOWN);
		pWheel->setMoveDelta(LEFT);
		_firstTimeEnter = true;
	}
	else if (pWheel->leftSide() < pArena->leftSide())
	{
		pWheel->bounce(pArena->leftSide(), LEFT);
		pWheel->setMoveDelta(UP);
	}
	else if (pWheel->upSide() < pArena->upSide())
	{
		if (_firstTimeEnter)
		{
			pWheel->adjustPosition(1, 1);

			if (pArena->moveWheelCW(20))
				pWheel->setThick(1);
			else
				pWheel->setThick(-1);

			_firstTimeEnter = false;
		}
		pWheel->bounce(pArena->upSide(), UP);
		pWheel->setMoveDelta(RIGHT);

		_wheel->debug_data();
	}
}

void WheelGameApplication::gamePlay()
{
	// Event handling
	SDL_Event eventIns;

	// start game loop
	while (_running)
	{
		// clear background from the last frame
		SDL_RenderClear(_gRenderer);

		// draw background
		_background->draw();

		// set wheel texture alpha mod
		_wheel->setTextureAlphaMod();
		// change wheel opacity value
		_wheel->changeOpacity();
		// clamp wheel opacity
		_wheel->clampOpacity();

		// change wheel position
		_wheel->implementMovement();
		// clamp wheel movement direction
		this->clampObjects(_arena, _wheel);

		// change wheel rotation angle
		_wheel->changeRotation(4.0);
		// clamp wheel rotation angle
		_wheel->clampRotation();

		// draw wheel
		_wheel->draw();

		// draw arena
		_arena->draw();

		// draw fps screen
		// _fpsScreen->draw();

		// Show everything that was rendered
		SDL_RenderPresent(_gRenderer);

		while (SDL_PollEvent(&eventIns))
		{
			switch (eventIns.type)
			{
				case SDL_QUIT:
					_running = false;
					break;
				case SDL_KEYDOWN:
					switch (eventIns.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							_running = false;
							break;
							// cases for other keypresses
					}
			}
		}

		if (_running) SDL_Delay(2);
	}
}
