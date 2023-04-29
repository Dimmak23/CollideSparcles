#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Arena.hpp"
#include "BackgroundTexture.hpp"

class WheelGameApplication
{
	public:
		WheelGameApplication(int argc, const char* argv[]);
		~WheelGameApplication();
		void show();

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

		// keeping track on the status of the creation
		bool _callingStatus{ false };
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
	// if (_gWindow == nullptr)
	// {
	// 	std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
	// }

	// Create a renderer for the window
	_gRenderer = SDL_CreateRenderer(_gWindow, -1, SDL_RENDERER_ACCELERATED);

	// Check if renderer creation were succsessfull
	// if (_gRenderer == nullptr)
	// {
	// 	std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
	// }

	// Set 'nullptr' texture as a rendering target
	_callingStatus = SDL_SetRenderTarget(_gRenderer, nullptr);

	// build background texture according to the window size
	_background = new BackgroundTexture(_gRenderer, _appWidth, _appHeight);

	// build arena lines with initial sizes
	_arena = new Arena(_gRenderer, _appWidth, _appHeight);
}

inline WheelGameApplication::~WheelGameApplication()
{
	// destroy resources
}

inline void WheelGameApplication::show()
{
	// use parsed window size if any

	// Initialize SDL2 libraries

	// Loading SDL_Image dynamic libraries

	// initialize game objects

	// start game loop
}
