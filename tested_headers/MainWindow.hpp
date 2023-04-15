#pragma once

#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>

class MainWindow
{
	public:
		MainWindow(const int& width, const int& height) : _width(width), _height(height)
		{
			creationStatus = initializeGraphics();
			creationStatus = loadBackground();
		}
		~MainWindow();

		void renderScreen();
		void renderBackground();
		bool getCreationStatus() const { return creationStatus; }

	private:
		int _width;
		int _height;
		bool creationStatus{ false };

		SDL_Window* _window{ nullptr };	   //?
		// SDL_Renderer* _renderer{ nullptr };		//?
		SDL_Surface* _screen{ nullptr };		//?
		SDL_Surface* _background{ nullptr };	//?
		// SDL_Texture* _imageTexture{ nullptr };	  //?
		SDL_Rect _destinationRect;	  //?

		bool initializeGraphics();
		bool loadBackground();
		SDL_Surface* loadSurface(const char* path);
};

inline bool MainWindow::initializeGraphics()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return false;
	}

	_window = SDL_CreateWindow("Testing bmp parse...",	   //
							   SDL_WINDOWPOS_UNDEFINED,	   //
							   SDL_WINDOWPOS_UNDEFINED,	   //
							   _width, _height,			   //
							   SDL_WINDOW_SHOWN			   //
	);

	if (_window == nullptr)
	{
		return false;
	}

	// Create a renderer for the window
	// _renderer = SDL_CreateRenderer(_window, -1, 0);

	_screen = SDL_GetWindowSurface(_window);

	return true;
}

bool MainWindow::loadBackground()
{
	// Load stretching surface
	_background = loadSurface("assets/background.bmp");

	if (_background == nullptr)
	{
		return false;
	}

	// Create texture from image
	// _imageTexture = SDL_CreateTextureFromSurface(_renderer, _background);

	// Set the size of the destination rectangle
	_destinationRect.x = 0;
	_destinationRect.y = 0;
	_destinationRect.w = _width;	 // desired width
	_destinationRect.h = _height;	 // desired height

	SDL_BlitScaled(_background, nullptr, _screen, &_destinationRect);

	// Update the surface
	SDL_UpdateWindowSurface(_window);

	return true;
}

inline SDL_Surface* MainWindow::loadSurface(const char* path)
{
	// The final optimized image
	SDL_Surface* optimizedSurface = nullptr;

	// Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path);
	if (loadedSurface == nullptr)
	{
		std::cout << "Unable to load image " << path << "! SDL Error: " << SDL_GetError();
	}
	else
	{
		// Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, _screen->format, 0);
		if (optimizedSurface == nullptr)
		{
			std::cout << "Unable to optimize image " << path << "! SDL Error: " << SDL_GetError();
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

inline void MainWindow::renderScreen()
{
	// SDL_BlitSurface(_background, nullptr, _screen, nullptr);
	// SDL_RenderPresent(_renderer);

	SDL_UpdateWindowSurface(_window);
}
inline void MainWindow::renderBackground()
{
	// Render the texture with the desired size
	// SDL_RenderCopy(_renderer, _imageTexture, nullptr, &_destinationRect);
	// SDL_RenderPresent(_renderer);
}

MainWindow::~MainWindow()
{
	// SDL_DestroyTexture(_imageTexture);

	// Free loaded image
	SDL_FreeSurface(_background);
	_background = nullptr;

	// SDL_DestroyRenderer(_renderer);

	// Destroy window
	SDL_DestroyWindow(_window);
	_window = nullptr;
}
