#pragma once

#include <string>

namespace WUtils
{
	static std::string _backgroundPath{ "assets/carbon-background.png" };
	static std::string _wheelPath{ "assets/light-no-back.png" };

	struct Size
	{
		unsigned int _width;
		unsigned int _height;
	};

	static Size _minArena{ 250, 220 };
	static Size _wheel{ 100, 88 };
}	 // namespace WUtils
