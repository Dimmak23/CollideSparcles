#include "Bubble.hpp"

#include <iostream>

Bubble::Bubble(SDL_Renderer* parent, unsigned int radius)
{
	// catch renderer
	_parent = parent;

	// implement parsed size for bubble
	_rectangle.set(0, 0, radius, radius);

	// assign center of the bubble
	_bubbleCenter = _rectangle.getCenterPoint();

	// Create a lighter surface from the '<?>.png'
	SDL_Surface* tempSurface = nullptr;
	tempSurface = IMG_Load(WUtils::_bubblePath.c_str());

	if (tempSurface == nullptr)
	{
		std::cout << "'Bubble'' surface could not be created! SDL Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		// Create a texture from the surface
		_texture = SDL_CreateTextureFromSurface(_parent, tempSurface);
		SDL_FreeSurface(tempSurface);
	}

	// set to move by one pixel
	this->setThick(1);

	// set to move right
	_delta.set(_thick, 0);
}

Bubble::~Bubble()
{
	//
	SDL_DestroyTexture(_texture);
	//
	_parent = nullptr;
}

void Bubble::setThick(const char& value) { _thick = value; }

void Bubble::setTextureAlphaMod() { SDL_SetTextureAlphaMod(_texture, _opacity); }

int Bubble::draw()
{
	// Returns 0 on success or a negative error code on failure; call SDL_GetError() for more information.
	return SDL_RenderCopyEx(		   //
		_parent,					   //
		_texture,					   //
		nullptr, &_rectangle._rect,	   //
		_angle,						   //
		&_bubbleCenter,				   //
		SDL_FLIP_NONE				   //
	);
}

void Bubble::implementMovement() { _rectangle += _delta; }

Bubble::CRectangle& Bubble::CRectangle::operator+=(const Bubble::MoveDeltas& deltas)
{
	_rect.x += deltas._X;
	_rect.y += deltas._Y;
	// std::cout << "position: {" << _rect.x << ", " << _rect.y << "}" << std::endl;
	return *this;
}

void Bubble::CRectangle::set(const int& x, const int& y, const int& w, const int& h)
{
	_rect.x = x;
	_rect.y = y;
	_rect.w = w;
	_rect.h = h;
}

SDL_Point Bubble::CRectangle::getCenterPoint() const
{
	SDL_Point temp;
	temp.x = _rect.w / 2;
	temp.y = _rect.h / 2;
	return temp;
}
