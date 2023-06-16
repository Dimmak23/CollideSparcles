#pragma once

#ifdef _WIN32

#include <SDL.h>
#include <SDL_image.h>

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

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

	// setters
	void changeOpacity();
	void clampOpacity();

	void implementMovement();
	void setMoveDelta(const Direction& flow);
	void bounce(const int& coordinate, const Direction& flow);
	void adjustPosition(const int& addX, const int& addY);

	void changeRotation(const double& value);
	void clampRotation();

	void setThick(const char& value);

	// getters
	int rightSide() const;
	int downSide() const;
	int leftSide() const;
	int upSide() const;

	// graphics
	void setTextureAlphaMod();
	int draw();

	// debugging
	void debug_data();

private:
	// let's deprecate copying background object
	Wheel(const Wheel&) = delete;
	Wheel operator=(const Wheel&) = delete;

	SDL_Renderer* _parent{ nullptr };
	SDL_Texture* _texture{ nullptr };

	struct MoveDeltas;

	struct CRectangle
	{
		// makes our live easier
		CRectangle& operator+=(const Wheel::MoveDeltas& deltas);

		// setters
		void set(const int& x, const int& y, const int& w, const int& h);
		void setX(const int& value);
		void setY(const int& value);

		// getters
		SDL_Point getCenterPoint() const;
		int X() const;
		int Y() const;
		int width() const;
		int height() const;

		// capsule
		SDL_Rect _rect;
	};

	struct MoveDeltas
	{
		void set(const char& X, const char& Y)
		{
			_X = X;
			_Y = Y;
		}
		void debug_data() const;
		friend struct Wheel::CRectangle;

	private:
		char _X{};
		char _Y{};
	};

	// We need destination rectangle
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
