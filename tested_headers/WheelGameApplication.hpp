#pragma once

#ifdef _WIN32

#include <SDL.h>
#include <SDL_image.h>

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include "Arena.hpp"
#include "BackgroundTexture.hpp"
#include "Wheel.hpp"

class WheelGameApplication
{
	public:
		WheelGameApplication(int argc, const char* argv[]);
		~WheelGameApplication();
		void initializeSDL();
		void gamePlay();

	private:
		// let's deprecate copying application
		WheelGameApplication(const WheelGameApplication&) = delete;
		WheelGameApplication operator=(const WheelGameApplication&) = delete;

		unsigned int _appXPos{ 10 };
		unsigned int _appYPos{ 10 };
		unsigned int _appWidth{ 640 };
		unsigned int _appHeight{ 480 };

		SDL_Window* _gWindow{ nullptr };
		SDL_Renderer* _gRenderer{ nullptr };

		SDL_Rect _gRect;

		BackgroundTexture* _background{ nullptr };
		Arena* _arena{ nullptr };
		Wheel* _wheel{ nullptr };

		// keeping track on the status of the creation
		bool _callingStatus{ false };

		// check maybe user whant to exit
		bool _running{ true };
};

inline WheelGameApplication::WheelGameApplication(int argc, const char* argv[])
{
	// take optional arguments with window size

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
	_background = new BackgroundTexture(_gRenderer, _appWidth, _appHeight);

	// build arena lines with initial sizes
	_arena = new Arena(_gRenderer, _appWidth, _appHeight);

	// build wheel with initial size
	_wheel = new Wheel(_gRenderer, Utils::_wheel._width, Utils::_wheel._height);
}

inline WheelGameApplication::~WheelGameApplication()
{
	// destroy resources
	SDL_DestroyRenderer(_gRenderer);
	SDL_DestroyWindow(_gWindow);

	//
	SDL_Quit();
}

inline void WheelGameApplication::initializeSDL()
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
}

inline void WheelGameApplication::gamePlay()
{
	// Event handling
	SDL_Event eventIns;

	// start game loop
	while (_running)
	{
		// clear background from the last frame
		SDL_RenderClear(_gRenderer);

		// draw background

		// draw arena

		// set wheel texture alpha mod
		_wheel->setTextureAlphaMod();
		// change wheel opacity value
		_wheel->changeOpacity();
		// clamp wheel opacity

		// change wheel position
		// clamp wheel position

		// change wheel rotation angle
		// clamp wheel rotation angle

		// draw wheel

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
