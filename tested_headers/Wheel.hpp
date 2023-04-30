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

class Wheel
{
	public:
		Wheel(SDL_Renderer* parent, unsigned int width, unsigned int height);
		~Wheel();

		void setTextureAlphaMod();
		void changeOpacity();

	private:
		// let's deprecate copying background object
		Wheel(const Wheel&) = delete;
		Wheel operator=(const Wheel&) = delete;

		SDL_Renderer* _parent{ nullptr };
		SDL_Texture* _texture{ nullptr };

		// We need destination rectangle
		SDL_Rect _rectangle;

		// Wheel center point
		SDL_Point _wheelCenter;

		// check if we already have shrink arena
		bool _firstTimeEnter{ true };

		// position
		short _deltaX{ 1 };
		short _deltaY{};
		// rotation
		double _angle{ 0.0 };
		// appearence
		unsigned char _opacity{ 255 };
		int _sign{ -1 };
};

inline Wheel::Wheel(SDL_Renderer* parent, unsigned int width, unsigned int height)
{
	// catch renderer
	_parent = parent;

	// implement parsed size for wheel
	_rectangle.x = 10;
	_rectangle.y = 10;
	_rectangle.w = width;
	_rectangle.h = height;

	// assign center of the wheel
	_wheelCenter.x = _rectangle.w / 2;
	_wheelCenter.y = _rectangle.h / 2;

	// Create a lighter surface from the '<?>.png'
	SDL_Surface* tempSurface = nullptr;
	tempSurface = IMG_Load(Utils::_wheelPath.c_str());

	if (tempSurface == nullptr)
	{
		std::cout << "Lighter surface could not be created! SDL Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		// SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));

		// Create a texture from the surface
		_texture = SDL_CreateTextureFromSurface(_parent, tempSurface);
		SDL_FreeSurface(tempSurface);
	}
}

inline Wheel::~Wheel()
{
	//
	SDL_DestroyTexture(_texture);
	//
	_parent = nullptr;
}

inline void Wheel::setTextureAlphaMod()
{
	std::cout << "change alpha mode: " << SDL_SetTextureAlphaMod(_texture, _opacity) << std::endl;
}

inline void Wheel::changeOpacity() { _opacity = static_cast<unsigned char>(_opacity + _sign); }
