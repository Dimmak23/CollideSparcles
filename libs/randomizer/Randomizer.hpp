#pragma once

struct RectangleArea
{
	unsigned int upLeftX, upLeftY, downRightX, downRightY;
};

class Randomizer
{
public:
	SDL_Point randomPoint(RectangleArea&& area);
};