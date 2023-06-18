#include "Bubble.hpp"

#include <iostream>

Bubble::Bubble(SDL_Renderer* parent, unsigned int radius, WUtils::Size&& initialPosition)
{
	// catch renderer
	_parent = parent;

	// implement parsed size for bubble
	_rectangle.set(initialPosition._width, initialPosition._height, 2 * radius, 2 * radius);

	//
	_bubbleRadius = radius;

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

	//! INITIAL MOVEMENT

	// set to move by one pixel
	this->setThick(8);

	// set to move right
	_delta.set(_thick, _thick);

	//
	std::cout << "Bubble have been constructed\n";
}

Bubble::~Bubble()
{
	//
	SDL_DestroyTexture(_texture);
	//
	_parent = nullptr;
	//
	std::cout << "Bubble have been destroyed\n";
}

void Bubble::setThick(const char& value) { _thick = value; }

void Bubble::setTextureAlphaMod() { SDL_SetTextureAlphaMod(_texture, _opacity); }

int Bubble::draw()
{
	_bubbleCenter = _rectangle.getCenterPoint();
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

void Bubble::implementMovement()
{
	_rectangle += _delta;
	// std::cout << "Setted deltaX = " << (int)_X << ", deltaY = " << (int)_Y << '\n';
}

void Bubble::bounce(const int& coordinate, const Direction& flow)
{
	switch (flow)
	{
		case RIGHT:
			_rectangle.setX(coordinate - _rectangle.width());
			_delta.set(-_delta.getX(), _delta.getY());
			break;
		case DOWN:
			_rectangle.setY(coordinate - _rectangle.height());
			_delta.set(_delta.getX(), -_delta.getY());
			break;
		case LEFT:
			_rectangle.setX(coordinate);
			_delta.set(-_delta.getX(), _delta.getY());
			break;
		case UP:
			_rectangle.setY(coordinate);
			_delta.set(_delta.getX(), -_delta.getY());
			break;
		default:
			break;
	}
}

void Bubble::bounce(const SDL_Point& coordinate, const Direction& flow)
{
	//
	switch (flow)
	{
		case DOWN_RIGHT:
			_delta.set(-_delta.getX(), -_delta.getY());
			break;
		case DOWN_LEFT:
			_delta.set(-_delta.getX(), -_delta.getY());
			break;
		case UP_RIGHT:
			_delta.set(-_delta.getX(), -_delta.getY());
			break;
		case UP_LEFT:
			_delta.set(-_delta.getX(), -_delta.getY());
			break;
		default:
			break;
	}
	_rectangle.setCenterPoint(coordinate);
}

void Bubble::bounce(const SDL_Point& coordinate)
{
	//
	_delta.set(-_delta.getX(), -_delta.getY());
	//
	_rectangle.setCenterPoint(coordinate);
}

int Bubble::CRectangle::X() const { return _rect.x; }

int Bubble::CRectangle::Y() const { return _rect.y; }

int Bubble::CRectangle::width() const { return _rect.w; }

int Bubble::CRectangle::height() const { return _rect.h; }

const char& Bubble::accelerationX() const { return _delta.getX(); }

const char& Bubble::accelerationY() const { return _delta.getY(); }

float Bubble::collideRadius() const { return (float)_bubbleRadius; }

SDL_Point Bubble::collisionCenter() const { return _rectangle.getCenterPoint(); }

Bubble::CRectangle& Bubble::CRectangle::operator+=(const Bubble::MoveDeltas& deltas)
{
	_rect.x += deltas._X;
	_rect.y += deltas._Y;
	// std::cout << "bubble deltas: {" << deltas._X << ", " << deltas._Y << "}" << std::endl;
	return *this;
}

void Bubble::CRectangle::set(const int& x, const int& y, const int& w, const int& h)
{
	_rect.x = x;
	_rect.y = y;
	_rect.w = w;
	_rect.h = h;
}

void Bubble::CRectangle::setX(const int& value) { _rect.x = value; }

void Bubble::CRectangle::setY(const int& value) { _rect.y = value; }

void Bubble::CRectangle::setCenterPoint(const SDL_Point& point)
{
	//
	_rect.x = point.x - _rect.w / 2;
	_rect.y = point.y - _rect.w / 2;
}

SDL_Point Bubble::CRectangle::getCenterPoint() const
{
	SDL_Point temp;
	temp.x = _rect.x + _rect.w / 2;
	temp.y = _rect.y + _rect.w / 2;
	return temp;
}

int Bubble::rightSide() const { return _rectangle._rect.x + _rectangle._rect.w; }

int Bubble::downSide() const { return _rectangle._rect.y + _rectangle._rect.h; }

int Bubble::leftSide() const { return _rectangle._rect.x; }

int Bubble::upSide() const { return _rectangle._rect.y; }

void Bubble::MoveDeltas::set(const char& X, const char& Y)
{
	_X = X;
	_Y = Y;
	std::cout << "Bubble setted deltaX = " << (int)_X << ", deltaY = " << (int)_Y << '\n';
}

const char& Bubble::MoveDeltas::getX() const { return _X; }
const char& Bubble::MoveDeltas::getY() const { return _Y; }
