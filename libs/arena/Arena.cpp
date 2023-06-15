#include "Arena.hpp"

#include <iostream>

Arena::Arena(SDL_Renderer* parent, unsigned int width, unsigned int height)
{
	// catch renderer
	_parent = parent;

	// implement parsed size for background
	_rectangle.x = 40;
	_rectangle.y = 40;
	_rectangle.w = width - 80;
	_rectangle.h = height - 80;

	// we will used it as max
	_rectangleMax = _rectangle;

	// set minimum rectangle
	_rectangleMin.w = WUtils::_minArena._width;
	_rectangleMin.h = WUtils::_minArena._height;
	_rectangleMin.x = (width - WUtils::_minArena._width) / 2;
	_rectangleMin.y = (height - WUtils::_minArena._height) / 2;

	// setting the color
	_color = new Color(34, 124, 200);
}

Arena::~Arena()
{
	_parent = nullptr;

	// deallocate heap memory
	delete _color;
}

int Arena::rightSide() const { return _rectangle.x + _rectangle.w; }

int Arena::downSide() const { return _rectangle.y + _rectangle.h; }

int Arena::leftSide() const { return _rectangle.x; }

int Arena::upSide() const { return _rectangle.y; }

bool Arena::moveWheelCW(const int& value)
{
	if (																				   //
		((_rectangle.w > _rectangleMin.w && _rectangle.h > _rectangleMin.h) && _shrink)	   //
		||																				   //
		((_rectangle.w >= _rectangleMax.w))												   //
		||																				   //
		((_rectangle.h >= _rectangleMax.h))												   //
	)
	{
		_rectangle.x += value;
		_rectangle.y += value;
		_rectangle.w -= 2 * value;
		_rectangle.h -= 2 * value;
		_shrink = true;
		std::cout << "going by clock\n";
		// wheel->setThick(1);
		return true;
	}
	else if (																				//
		((_rectangle.w <= _rectangleMin.w))													//
		||																					//
		((_rectangle.h <= _rectangleMin.h))													//
		||																					//
		((_rectangle.w < _rectangleMax.w && _rectangle.h < _rectangleMax.h) && !_shrink)	//
	)
	{
		_rectangle.x -= value;
		_rectangle.y -= value;
		_rectangle.w += 2 * value;
		_rectangle.h += 2 * value;
		_shrink = false;
		std::cout << "going against clock\n";
		// wheel->setThick(-1);
		return false;
	}
}

bool Arena::isShrinking() const { return _shrink; }

int Arena::draw()
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
