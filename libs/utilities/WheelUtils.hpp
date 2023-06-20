#pragma once

#include <string>

enum Direction
{
	RIGHT = 0,
	DOWN,
	LEFT,
	UP,
	DOWN_RIGHT,
	DOWN_LEFT,
	UP_RIGHT,
	UP_LEFT
};

//! Probably you don't whant have them as 'STATIC'

namespace WUtils
{
	static std::string _backgroundPath{ "assets/images/carbon-background.png" };
	static std::string _wheelPath{ "assets/images/light-no-back.png" };
	static std::string _bubblePath{ "assets/images/bubble-no-back.png" };

	static std::string _FPSfont_small{ "assets/fonts/small_tech.ttf" };
	static std::string _FPSfont_pixel{ "assets/fonts/pixeled.ttf" };

	struct Size
	{
		Size(const unsigned int& x, const unsigned int& y) : _width(x), _height(y) {}
		unsigned int _width;
		unsigned int _height;
	};

	static Size _minArena{ 320, 240 };
	static Size _wheel{ 100, 106 };
	static unsigned int _bubbleRadius{ 9 };
}	 // namespace WUtils
