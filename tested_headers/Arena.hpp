#pragma once

#ifdef _WIN32

#include <SDL.h>
#include <SDL_image.h>

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include "WheelUtils.hpp"

class Arena
{
	public:
		Arena(SDL_Renderer* parent, unsigned int width, unsigned int height);
		~Arena();

	private:
		// let's deprecate copying background object
		Arena(const Arena&) = delete;
		Arena operator=(const Arena&) = delete;

		SDL_Renderer* _parent{ nullptr };

		// We need destination rectangle
		SDL_Rect _rectangle;
		SDL_Rect _rectangleMax;
		SDL_Rect _rectangleMin;

		struct Color
		{
			public:
				Color(unsigned char red, unsigned char green, unsigned char blue)
					: _red(red), _green(green), _blue(blue)
				{}

			private:
				unsigned char _red{};
				unsigned char _green{};
				unsigned char _blue{};
		};

		Color* _color;
};

inline Arena::Arena(SDL_Renderer* parent, unsigned int width, unsigned int height)
{
	// catch renderer
	_parent = parent;

	// implement parsed size for background
	_rectangle.x = 10;
	_rectangle.y = 10;
	_rectangle.w = width - 20;
	_rectangle.h = height - 20;

	// we will used it as max
	_rectangleMax = _rectangle;

	// set minimum rectangle
	_rectangleMin.w = Utils::_minArena._width;
	_rectangleMin.h = Utils::_minArena._height;
	_rectangleMin.x = (width - Utils::_minArena._width) / 2;
	_rectangleMin.y = (height - Utils::_minArena._height) / 2;

	// setting the color
	_color = new Color(34, 124, 200);
}
