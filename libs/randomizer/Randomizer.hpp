#pragma once

struct RectangleArea
{
	unsigned int upLeftX, upLeftY, downRightX, downRightY;
};

struct Point
{
	unsigned int _X, _Y;
};

class Randomizer
{
public:
	Randomizer() = default;
	~Randomizer() = default;

	Point randomPoint(RectangleArea&& area);

private:
	unsigned int randomNumber(unsigned int& left, unsigned int& right);
};
