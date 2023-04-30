#pragma once

#ifdef _WIN32

#include <SDL.h>
#include <SDL_image.h>

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include "Wheel.hpp"
#include "WheelUtils.hpp"

class Arena
{
public:
	Arena(SDL_Renderer* parent, unsigned int width, unsigned int height);
	~Arena();

	int rightSide() const;
	int downSide() const;
	int leftSide() const;
	int upSide() const;

	void adjustBorder(const int& value, Wheel* wheel);

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

inline int Arena::rightSide() const { return _rectangle.x + _rectangle.w; }

inline int Arena::downSide() const { return _rectangle.y + _rectangle.h; }

inline int Arena::leftSide() const { return _rectangle.x; }

inline int Arena::upSide() const { return _rectangle.y; }

inline void Arena::adjustBorder(const int& value, Wheel* wheel)
{
	if (																				   //
		((_rectangle.w > _rectangleMin.w && _rectangle.h > _rectangleMin.h) && _shrink)	   //
		||																				   //
		(_rectangle.w >= _rectangleMax.w)												   //
		||																				   //
		(_rectangle.h >= _rectangleMax.h)												   //
	)
	{
		_rectangle.x += value;
		_rectangle.y += value;
		_rectangle.w -= 2 * value;
		_rectangle.h -= 2 * value;
		_shrink = true;
		wheel->setThick(1);
	}
	else if (																				//
		(_rectangle.w <= _rectangleMin.w)													//
		||																					//
		(_rectangle.h <= _rectangleMin.h)													//
		||																					//
		((_rectangle.w < _rectangleMax.w && _rectangle.h < _rectangleMax.h) && !_shrink)	//
	)
	{
		_rectangle.x -= value;
		_rectangle.y -= value;
		_rectangle.w += 2 * value;
		_rectangle.h += 2 * value;
		_shrink = false;
		wheel->setThick(-1);
	}
}

inline int Arena::draw()
{
	SDL_SetRenderDrawColor(	   //
		_parent,			   //
		_color->_red,		   //
		_color->_green,		   //
		_color->_blue,		   //
		SDL_ALPHA_OPAQUE	   //
	);

	return SDL_RenderDrawRect(_parent,		 //
							  &_rectangle	 //
	);
}
