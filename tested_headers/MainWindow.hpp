#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

class MainWindow
{
	public:
		MainWindow(const int& width, const int& height) : _width(width), _height(height)
		{
			creationStatus = initializeGraphics();
			creationStatus = loadBackground();
			creationStatus = loadCharacter();
		}
		~MainWindow();

		void renderScreen();
		void renderBackground();
		bool getCreationStatus() const { return creationStatus; }

	private:
		int _width;
		int _height;
		bool creationStatus{ false };

		SDL_Window* _window{ nullptr };				  //?
		SDL_Renderer* _renderer{ nullptr };			  //?
		SDL_Surface* _background{ nullptr };		  //?
		SDL_Texture* _backTexture{ nullptr };		  //?
		SDL_Rect _backRect;							  //?
		SDL_Surface* _character{ nullptr };			  //?
		SDL_Texture* _characterTexture{ nullptr };	  //?
		SDL_Rect _characterRect;					  //?
		// SDL_Surface* _screen{ nullptr };			  //?
		// SDL_Surface* _buffer{ nullptr };			  //?
		// SDL_Surface* _chmask{ nullptr };			  //?

		bool initializeGraphics();
		bool loadBackground();
		SDL_Texture* renderImageInATexture(SDL_Texture* image, Uint8 transparency, SDL_Rect* rect);
		bool loadCharacter();
		SDL_Surface* loadSurface(SDL_Surface* picture);
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
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// Create a renderer for the window
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	// Initialize PNG loading
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}

	// Get window surface
	// _screen = SDL_GetWindowSurface(_window);

	return true;
}

bool MainWindow::loadBackground()
{
	// Load stretching surface
	// _buffer = nullptr;
	// Load image at specified path
	// _buffer = SDL_LoadBMP("assets/background.bmp");
	// _background = loadSurface(_buffer);

	_background = nullptr;
	_background = SDL_LoadBMP("assets/background.bmp");
	// _background = SDL_ConvertSurface(IMG_Load("assets/background.bmp"), _screen->format, 0);

	if (_background == nullptr)
	{
		return false;
	}

	// Set the color key after loading the surface, and before the texturing
	SDL_SetColorKey(_background, SDL_TRUE, SDL_MapRGB(_background->format, 0xFF, 0, 0xFF));

	// Create texture from image
	_backTexture = SDL_CreateTextureFromSurface(_renderer, _background);
	SDL_FreeSurface(_background);

	// Set the size of the destination rectangle
	_backRect.x = _width / 2;
	_backRect.y = _height / 2;
	_backRect.w = _width / 2;	  // desired width
	_backRect.h = _height / 2;	  // desired height

	// SDL_BlitScaled(_background, nullptr, _screen, &destinationRect);

	// Update the surface
	// SDL_UpdateWindowSurface(_window);

	return true;
}

SDL_Texture* MainWindow::renderImageInATexture(SDL_Texture* image, Uint8 transparency, SDL_Rect* rect)
{
	// Create an intermediate texture
	rect->w *= 4;
	rect->h *= 4;
	SDL_Texture* texture =
		SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect->w, rect->h);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(_renderer, texture);

	// Paint it black with a given transparency value.
	SDL_SetRenderDrawColor(_renderer, (Uint8)0, (Uint8)0, (Uint8)0, (Uint8)transparency);
	SDL_RenderClear(_renderer);

	// Render the image in intermediate texture
	SDL_SetRenderTarget(_renderer, texture);
	SDL_RenderCopy(_renderer, image, nullptr, nullptr);

	// The result will be rendered in the background
	SDL_SetRenderTarget(_renderer, nullptr);
	return texture;
}

inline bool MainWindow::loadCharacter()
{
	// Load stretching surface
	// _buffer = nullptr;
	// Load image at specified path
	// _buffer = IMG_Load("assets/character.png");
	// _character = loadSurface(_buffer);

	// Set the size of the destination rectangle
	_characterRect.x = 0;
	_characterRect.y = 0;
	_characterRect.w = 90;	  // desired width
	_characterRect.h = 60;	  // desired height

	_character = nullptr;
	_character = IMG_Load("assets/character_02.png");
	_character = SDL_ConvertSurface(IMG_Load("assets/character.png"), _character->format, 0);

	if (_character == nullptr)
	{
		return false;
	}

	// Set the color key after loading the surface, and before the texturing
	SDL_SetColorKey(_character, SDL_TRUE, SDL_MapRGB(_character->format, 0, 0, 0));

	// Create texture from image
	_characterTexture = SDL_CreateTextureFromSurface(_renderer, _character);
	SDL_FreeSurface(_character);
	// _characterTexture = renderImageInATexture(_characterTexture, 128, &_characterRect);

	// SDL_BlitScaled(_character, nullptr, _screen, &destinationRect);

	// Update the surface
	// SDL_UpdateWindowSurface(_window);

	return true;
}
inline SDL_Surface* MainWindow::loadSurface(SDL_Surface* picture)
{
	// The final optimized image
	SDL_Surface* optimizedSurface = nullptr;
	if (picture == nullptr)
	{
		std::cout << "Unable to read image " << picture << "! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	// // Convert surface to screen format
	// optimizedSurface = SDL_ConvertSurface(picture, _screen->format, 0);
	// if (optimizedSurface == nullptr)
	// {
	// 	std::cout << "Unable to optimize image " << picture << "! SDL Error: " << SDL_GetError() << std::endl;
	// 	return nullptr;
	// }

	// // Get rid of old loaded surface
	// SDL_FreeSurface(picture);

	return optimizedSurface;
}

inline void MainWindow::renderScreen()
{
	// SDL_BlitSurface(_background, nullptr, _screen, nullptr);
	// SDL_RenderPresent(_renderer);

	// Clear and draw the screen
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);

	// Background
	SDL_RenderCopy(_renderer, _backTexture, nullptr, &_backRect);
	// Character
	SDL_RenderCopy(_renderer, _characterTexture, nullptr, &_characterRect);

	// Show
	SDL_RenderPresent(_renderer);

	// SDL_UpdateWindowSurface(_window);
}
inline void MainWindow::renderBackground()
{
	// Render the texture with the desired size
	// SDL_RenderCopy(_renderer, _imageTexture, nullptr, &_destinationRect);
	// SDL_RenderPresent(_renderer);
}

MainWindow::~MainWindow()
{
	SDL_DestroyTexture(_backTexture);
	_backTexture = nullptr;
	SDL_DestroyTexture(_characterTexture);
	_characterTexture = nullptr;

	// Free loaded image
	// SDL_FreeSurface(_background);
	// _background = nullptr;

	// SDL_DestroyRenderer(_renderer);
	// _renderer = nullptr;

	// Destroy window
	SDL_DestroyWindow(_window);
	_window = nullptr;
}
