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
