#include "Background.hpp"

#include <iostream>

Background::Background(SDL_Renderer* parent, unsigned int width, unsigned int height)
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

	tempSource = IMG_Load(WUtils::_backgroundPath.c_str());
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

Background::~Background()
{
	//
	SDL_DestroyTexture(_texture);
	//
	_parent = nullptr;
}

int Background::draw() { return SDL_RenderCopy(_parent, _texture, &_rectangle, nullptr); }
