#pragma once

#ifdef _WIN32

//
#include <SDL.h>
// #include <SDL_image.h>

#else

#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>

#endif

#include "WheelUtils.hpp"
// #include "WheelUtils.hpp"

class Arena
{
public:
	Arena(SDL_Renderer* parent, unsigned int width, unsigned int height);
	~Arena();

	unsigned int rightSide() const;
	unsigned int downSide() const;
	unsigned int leftSide() const;
	unsigned int upSide() const;

	// returns 'true' - when arena size bigger from max envelope,
	// 'false' - when smaller then min envelope
	bool moveWheelCW(const int& value);

	bool isShrinking() const;

	int draw();

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
		Color(unsigned char red, unsigned char green, unsigned char blue) : _red(red), _green(green), _blue(blue) {}
		unsigned char _red{};
		unsigned char _green{};
		unsigned char _blue{};
	};

	Color* _color;

	bool _shrink{ true };
};
