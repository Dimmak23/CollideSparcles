#include "Wheel.hpp"

#include <chrono>
#include <iostream>

Wheel::Wheel(SDL_Renderer* parent, unsigned int width, unsigned int height)
{
	// catch renderer
	_parent = parent;

	// implement parsed size for wheel
	_rectangle.set(40, 40, width, height);
	_wheelRadius = width / 2;

	// assign center of the wheel
	_wheelCenter = _rectangle.getCenterPoint();

	// Create a lighter surface from the '<?>.png'
	SDL_Surface* originalSurface = nullptr;
	originalSurface = IMG_Load(WUtils::_wheelPath.c_str());

	if (originalSurface == nullptr)
	{
		std::cout << "Original 'Wheel'' surface could not be created! SDL Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		// Create cropped image
		SDL_Surface* croppedSurface = SDL_CreateRGBSurface(	   //
			0,												   //
			570, 603,										   // resulted size
			originalSurface->format->BitsPerPixel,			   //
			originalSurface->format->Rmask,					   //
			originalSurface->format->Gmask,					   //
			originalSurface->format->Bmask,					   //
			originalSurface->format->Amask					   //
		);

		// Clip original surface
		SDL_Rect croppedRectangle;
		croppedRectangle.x = 143;	 // X coordinate of the top-left corner of the cropped area
		croppedRectangle.y = 61;	 // Y coordinate of the top-left corner of the cropped area
		croppedRectangle.w = 570;	 // Width of the cropped area
		croppedRectangle.h = 603;	 // Height of the cropped area

		SDL_SetClipRect(originalSurface, &croppedRectangle);

		SDL_BlitSurface(originalSurface, &croppedRectangle, croppedSurface, NULL);

		SDL_FreeSurface(originalSurface);

		// Create a texture from the surface
		_texture = SDL_CreateTextureFromSurface(_parent, croppedSurface);
		SDL_FreeSurface(croppedSurface);
	}

	//! INITIAL MOVEMENT

	// set to move by one pixel
	this->setThick(4);

	// set to move right
	_delta.set(_thick, 0);
}

Wheel::~Wheel()
{
	//
	SDL_DestroyTexture(_texture);
	//
	_parent = nullptr;
}

void Wheel::setTextureAlphaMod()
{
	// std::cout << "change alpha mode: " << SDL_SetTextureAlphaMod(_texture, _opacity) << std::endl;
	// Returns 0 on success or a negative error code on failure; call SDL_GetError() for more information.
	SDL_SetTextureAlphaMod(_texture, _opacity);
}

void Wheel::changeOpacity() { _opacity = static_cast<unsigned char>(_opacity + _sign); }

void Wheel::implementMovement()
{
	//
	// std::cout << "adjuct, thick = " << (int)_thick											//
	// 		  << ", {" << _rectangle.X() << ", " << _rectangle.Y() << "}." << std::endl;	//

	_rectangle += _delta;
}

void Wheel::CRectangle::set(const int& x, const int& y, const int& w, const int& h)
{
	_rect.x = x;
	_rect.y = y;
	_rect.w = w;
	_rect.h = h;
}

void Wheel::CRectangle::setX(const int& value) { _rect.x = value; }

void Wheel::CRectangle::setY(const int& value) { _rect.y = value; }

SDL_Point Wheel::CRectangle::getCenterPoint() const
{
	SDL_Point temp;
	temp.x = _rect.x + _rect.w / 2;
	temp.y = _rect.y + _rect.w / 2;	   //! image umbalanced and fixed here
	return temp;
}

int Wheel::CRectangle::X() const { return _rect.x; }

int Wheel::CRectangle::Y() const { return _rect.y; }

int Wheel::CRectangle::width() const { return _rect.w; }

int Wheel::CRectangle::height() const { return _rect.h; }

Wheel::CRectangle& Wheel::CRectangle::operator+=(const Wheel::MoveDeltas& deltas)
{
	_rect.x += deltas._X;
	_rect.y += deltas._Y;
	// std::cout << "position: {" << _rect.x << ", " << _rect.y << "}" << std::endl;
	return *this;
}

int Wheel::rightSide() const { return _rectangle._rect.x + _rectangle._rect.w; }

int Wheel::downSide() const { return _rectangle._rect.y + _rectangle._rect.h; }

int Wheel::leftSide() const { return _rectangle._rect.x; }

int Wheel::upSide() const { return _rectangle._rect.y; }

const char& Wheel::getThick() const { return _thick; }

float Wheel::collideRadius() const { return (float)_wheelRadius; }

SDL_Point Wheel::collisionCenter() const { return _rectangle.getCenterPoint(); }

void Wheel::clampOpacity()
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

void Wheel::changeRotation(const double& value) { _angle += value; }

void Wheel::clampRotation()
{
	if (_angle > 360.0) _angle = 0.0;
}

void Wheel::setThick(const char& value)
{
	//
	_thick = value;
	std::cout << "setted thick: " << (int)_thick << std::endl;
}

int Wheel::draw()
{
	_wheelCenter = SDL_Point{ _rectangle.width() / 2, _rectangle.width() / 2 };
	// Returns 0 on success or a negative error code on failure; call SDL_GetError() for more information.
	return SDL_RenderCopyEx(_parent,					   //
							_texture,					   //
							nullptr, &_rectangle._rect,	   //
							_angle,						   //
							&_wheelCenter,				   //
							SDL_FLIP_NONE				   //
	);
}

void Wheel::debug_data()
{
	//
	// const auto now = std::chrono::system_clock::now();
	// const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
	// std::cout << "The system clock is currently at " << std::ctime(&t_c);

	std::cout << "thick: " << (int)_thick << std::endl;
	_delta.debug_data();
}

void Wheel::setMoveDelta(const Direction& flow)
{
	switch (flow)
	{
		case RIGHT:
			_delta.set(_thick, 0);
			break;
		case DOWN:
			_delta.set(0, _thick);
			break;
		case LEFT:
			_delta.set(-_thick, 0);
			break;
		case UP:
			_delta.set(0, -_thick);
			break;
		default:
			break;
	}
	std::cout << "setted ";
	_delta.debug_data();
}

void Wheel::bounce(const int& coordinate, const Direction& flow)
{
	switch (flow)
	{
		case RIGHT:
			_rectangle.setX(coordinate - _rectangle.width());
			break;
		case DOWN:
			_rectangle.setY(coordinate - _rectangle.height());
			break;
		case LEFT:
			_rectangle.setX(coordinate);
			break;
		case UP:
			_rectangle.setY(coordinate);
			break;
		default:
			break;
	}
}

void Wheel::adjustPosition(const int& addX, const int& addY)
{
	// std::cout << "adjuct, thick = " << (int)_thick											//
	// 		  << ", {" << _rectangle.X() << ", " << _rectangle.Y() << "}." << std::endl;	//
	_rectangle.setX(_rectangle.X() + _thick * addX);
	_rectangle.setY(_rectangle.Y() + _thick * addY);
}

void Wheel::MoveDeltas::debug_data() const
{
	//
	std::cout << "Wheel delta {" << (int)_X << ", " << (int)_Y << "}" << std::endl;
}
