#pragma once

#ifdef _WIN32

#include <SDL.h>
#include <SDL_image.h>

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include "WheelUtils.hpp"

// enum Direction
// {
// 	RIGHT = 0,
// 	DOWN,
// 	LEFT,
// 	UP
// };

class Bubble
{
public:
	Bubble(SDL_Renderer* parent, unsigned int radius);
	~Bubble();

	void setThick(const char& value);
	void implementMovement();

	// graphics
	void setTextureAlphaMod();
	int draw();

private:
	// let's deprecate copying background object
	Bubble(const Bubble&) = delete;
	Bubble operator=(const Bubble&) = delete;

	SDL_Renderer* _parent{ nullptr };
	SDL_Texture* _texture{ nullptr };

	struct MoveDeltas;

	struct CRectangle
	{
		// makes our live easier
		CRectangle& operator+=(const Bubble::MoveDeltas& deltas);

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
		friend struct Bubble::CRectangle;

	private:
		char _X{};
		char _Y{};
	};

	// We need destination rectangle
	CRectangle _rectangle;
	// Bubble center point
	SDL_Point _bubbleCenter;
	// position
	MoveDeltas _delta;
	// rotation
	double _angle{ 0.0 };
	// appearence
	unsigned char _opacity{ 255 };
	// opacity change sign
	int _sign{ -1 };
	// move thick
	char _thick{};
};
