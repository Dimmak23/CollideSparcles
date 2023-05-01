#pragma once

#ifdef _WIN32

#include <SDL.h>
#include <SDL_image.h>

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include <iostream>

#include "WheelUtils.hpp"

class Background
{
public:
	Background(SDL_Renderer* parent, unsigned int width, unsigned int height);
	~Background();

	int draw();

private:
	// let's deprecate copying background object
	Background(const Background&) = delete;
	Background operator=(const Background&) = delete;

	SDL_Renderer* _parent{ nullptr };
	SDL_Texture* _texture{ nullptr };

	// We need destination rectangle
	SDL_Rect _rectangle;
};

inline Background::Background(SDL_Renderer* parent, unsigned int width, unsigned int height)
{
	// catch renderer
	_parent = parent;

	// implement parsed size for background
	_rectangle.x = 0;
	_rectangle.y = 0;
	_rectangle.w = width;
	_rectangle.h = height;

	// Create a background surface from the '<?>.png'
	SDL_Surface* tempSource = nullptr;
	tempSource = IMG_Load(Utils::_backgroundPath.c_str());

	if (tempSource == nullptr)
	{
		std::cout << "Background surface could not be created! SDL Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		// Create a texture from the surface
		_texture = SDL_CreateTextureFromSurface(_parent, tempSource);
		SDL_FreeSurface(tempSource);
	}
}

inline Background::~Background()
{
	//
	SDL_DestroyTexture(_texture);
	//
	_parent = nullptr;
}

inline int Background::draw() { return SDL_RenderCopy(_parent, _texture, &_rectangle, nullptr); }