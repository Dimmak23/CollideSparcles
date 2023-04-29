#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

		struct Color
		{
			private:
				Color(unsigned char red, unsigned char green, unsigned char blue)
					: _red(red), _green(green), _blue(blue) unsigned char _red{};
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

	// setting the color
	_color = new Color(34, 124, 200);
}