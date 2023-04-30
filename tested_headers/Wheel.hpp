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

enum Direction
{
	RIGHT = 0,
	DOWN,
	LEFT,
	UP
};

class Wheel
{
public:
	Wheel(SDL_Renderer* parent, unsigned int width, unsigned int height);
	~Wheel();

	void setTextureAlphaMod();
	void changeOpacity();
	void implementMovement();
	// void setWheelCoordinates(const MoveCoordinates& coor);
	void setMoveDelta(const Direction& flow);
	void bounce(const int& coordinate, const Direction& flow);
	int rightSide() const;
	int downSide() const;
	int leftSide() const;
	int upSide() const;
	void clampOpacity();
	void changeRotation(const double& value);
	void clampRotation();
	void setThick(const char& value);

	int draw();

private:
	// let's deprecate copying background object
	Wheel(const Wheel&) = delete;
	Wheel operator=(const Wheel&) = delete;

	SDL_Renderer* _parent{ nullptr };
	SDL_Texture* _texture{ nullptr };

	struct MoveDeltas;

	struct CRectangle
	{
		void set(const int& x, const int& y, const int& w, const int& h);
		// CRectangle& operator+(const MoveDeltas& deltas);
		SDL_Point getCenterPoint() const;
		CRectangle& operator+=(const Wheel::MoveDeltas& deltas);
		SDL_Rect _rect;
	};

	struct MoveDeltas
	{
		void set(const char& X, const char& Y)
		{
			_X = X;
			_Y = Y;
		}
		void set(const MoveDeltas& rightOperand) {}

		friend struct Wheel::CRectangle;
		friend class Wheel;

	private:
		char _X{};
		char _Y{};
	};

	// We need destination rectangle
	// SDL_Rect _rectangle;
	CRectangle _rectangle;

	// Wheel center point
	SDL_Point _wheelCenter;

	// position
	MoveDeltas _delta;
	// rotation
	double _angle{ 0.0 };
	// appearence
	unsigned char _opacity{ 255 };
	int _sign{ -1 };

	// move thick
	char _thick{};
};

inline Wheel::Wheel(SDL_Renderer* parent, unsigned int width, unsigned int height)
{
	// catch renderer
	_parent = parent;

	// implement parsed size for wheel
	_rectangle.set(10, 10, width, height);

	// assign center of the wheel
	_wheelCenter = _rectangle.getCenterPoint();

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

	// set to move right
	_delta.set(1, 0);
	// set to move by one pixel
	this->setThick(1);
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
	// std::cout << "change alpha mode: " << SDL_SetTextureAlphaMod(_texture, _opacity) << std::endl;
	SDL_SetTextureAlphaMod(_texture, _opacity);
}

inline void Wheel::changeOpacity() { _opacity = static_cast<unsigned char>(_opacity + _sign); }

inline void Wheel::implementMovement() { _rectangle += _delta; }

inline void Wheel::CRectangle::set(const int& x, const int& y, const int& w, const int& h)
{
	_rect.x = x;
	_rect.y = y;
	_rect.w = w;
	_rect.h = h;
}

inline SDL_Point Wheel::CRectangle::getCenterPoint() const
{
	SDL_Point temp;
	temp.x = _rect.w / 2;
	temp.y = _rect.h / 2;
	return temp;
}

inline Wheel::CRectangle& Wheel::CRectangle::operator+=(const Wheel::MoveDeltas& deltas)
{
	_rect.x += deltas._X;
	_rect.y += deltas._Y;
	// std::cout << "position: {" << _rect.x << ", " << _rect.y << "}" << std::endl;
	return *this;
}

inline int Wheel::rightSide() const { return _rectangle._rect.x + _rectangle._rect.w; }

inline int Wheel::downSide() const { return _rectangle._rect.y + _rectangle._rect.h; }

inline int Wheel::leftSide() const { return _rectangle._rect.x; }

inline int Wheel::upSide() const { return _rectangle._rect.y; }

inline void Wheel::clampOpacity()
{
	if (_opacity < 2)
	{
		_sign *= -1;
		_opacity = 1;
	}
	else if (_opacity > 254)
	{
		_sign *= -1;
		_opacity = 255;
	}
}

inline void Wheel::changeRotation(const double& value) { _angle += value; }

inline void Wheel::clampRotation()
{
	if (_angle > 360.0) _angle = 0.0;
}

inline void Wheel::setThick(const char& value) { _thick = value; }

inline int Wheel::draw()
{
	return SDL_RenderCopyEx(_parent,					   //
							_texture,					   //
							nullptr, &_rectangle._rect,	   //
							_angle,						   //
							&_wheelCenter,				   //
							SDL_FLIP_NONE				   //
	);
}

inline void Wheel::setMoveDelta(const Direction& flow)
{
	switch (flow)
	{
		case RIGHT:
			_delta._X = _thick;
			_delta._Y = 0;
			break;
		case DOWN:
			_delta._X = 0;
			_delta._Y = _thick;
			break;
		case LEFT:
			_delta._X = -_thick;
			_delta._Y = 0;
			break;
		case UP:
			_delta._X = 0;
			_delta._Y = -_thick;
			break;
		default:
			break;
	}
}

inline void Wheel::bounce(const int& coordinate, const Direction& flow)
{
	switch (flow)
	{
		case RIGHT:
			_rectangle._rect.x = coordinate - _rectangle._rect.w;
			break;
		case DOWN:
			_rectangle._rect.y = coordinate - _rectangle._rect.h;
			break;
		case LEFT:
			_rectangle._rect.x = coordinate;
			break;
		case UP:
			_rectangle._rect.y = coordinate;
			break;
		default:
			break;
	}
}
