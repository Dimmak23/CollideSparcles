#pragma once

#include <string>

namespace WUtils
{
	static std::string _backgroundPath{ "assets/images/carbon-background.png" };
	static std::string _wheelPath{ "assets/images/light-no-back.png" };
	static std::string _FPSfont{ "assets/fonts/cheese.ttf" };

	struct Size
	{
		unsigned int _width;
		unsigned int _height;
	};

	static Size _minArena{ 320, 240 };
	static Size _wheel{ 100, 88 };
}	 // namespace WUtils
